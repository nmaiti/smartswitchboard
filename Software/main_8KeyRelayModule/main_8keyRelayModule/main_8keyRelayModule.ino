
/* Project: Smart Switch Board Vr1
   Author:Vikas Gaikwad
   Date  :03/02/2016
   Descriptions:  This is a Smart Switch board can be communicated with Capsense Touch Switch Board,RF Remote and a Bluetooth Low Energy [BTL4.0] using Smart Phone.  
                  Followed the Protocol while communicating through BLE4.0 to set and get Acknowledgement from Host microcontroller.
   Note:    1. After every change in state status gets sync on Smartphone (in Smartphone App).
            2. Capacitive Touch and RF Remote and BLE4.0 Enabled. 
               i) Capacitive Touch = Direct control (TTL)
               ii)RF434 MHz Transmitter and receiver communication
               iii)BLE4.0 =  Acess string to contol and Read Status of Switch Boards   
 */

#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <HBT.h>
//#include <EEPROM.h>
//#include <Wire.h>   // Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include "QTouch.h"
//#include "BLE.h"
//#include "RTClib.h"


//RTC_DS1307 rtc;
HBT myHBT;          // Object Variables
QTouch myTouch;  
//BLE getStatus;


//Global Variables

int Pin_Type;    //  Stores Pin Type  
int Pin_No;      //  Stores Pin Number
int Pin_Value;   //  Stores Pin Value 

/// Using PinChange Interrupt0

volatile byte touch_input=0,prev_touch_input=0,temp,change,new_state;
volatile byte load_output_status=0,output_TouchStatus=0;
volatile byte Curr_RFStatus=0,prevRFStatus=0;
bool fon = false,foff= false,up_in = false,mstr_on =false;
volatile uint8_t level = 0;
int switch_num=0;

//void(*resetFunc)(void) = 0;   //declare reset function at address 0
//resetFunc();  //call reset

void setup()
{
  Serial.begin(9600);
  myHBT.begin(9600);

  myHBT.enterCommandMode();

  myHBT.setName("HALL");
  myHBT.setTransmissionPower(Six);
  myHBT.setWorkRole(SLAVE);
  myHBT.setAuth(OPEN);
  myHBT.setWorkMode(REMOTE_CONTROL);
  myHBT.setiBeaconMode(On);
  
  myHBT.exitCommandMode();

  myTouch.gpioInit();    // set all pins
/*
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    //rtc.adjust(DateTime(2016, 2, 12, 17, 25, 0));
  }
  */  

//sei();      //Enable Global Interrupt
}  

void loop()
{  
   // Note: please add Pull down resistor on RF inputs pins ***************************************
   
  // Curr_RFStatus = myTouch.readRF() & 0x0F;      //Read RF Status     
   touch_input = myTouch.readCapsense() & 0x7F;  //Read capsense values
   
   //Serial.println(touch_input,HEX);
   
   if(myHBT.available()>0)                //phone connected and Rx commands
   {
      Pin_Type = myHBT.parseInt();
      Pin_No = myHBT.parseInt();
      Pin_Value = myHBT.parseInt();

      //Serial.print(Pin_Type);
      //Serial.print(",");
      //Serial.print(Pin_No);
      //Serial.print(","); 
      //Serial.println(Pin_Value);
      //Serial.print("I am Here");
     // myTouch.LightControl(Pin_No,Pin_Value);
        if(myHBT.read() =='H')                      // detects endline character "H"
        {
            //Serial.print("I am in if.read()");
            //if Pin Type is 0 means Digital Output      
           switch(Pin_Type)
           {
              case(0):
                      if((Pin_No == Level1 || Pin_No == Level2 || Pin_No == Level3 || Pin_No == Level4) && (Pin_Value == 1))    // Any one Level is selected and Value set to HIGH 
                      { //Serial.print("In Case 0");
                        if(Pin_No == Level1 && Pin_Value ==1){ /*Serial.print("Level 1");*/myTouch.FAN_ON();}       //  Level 1 ON 
                        if(Pin_No == Level2 && Pin_Value ==1){ /*Serial.print("Level 2");*/myTouch.Level2_ON();}    //  Level 2 ON
                        if(Pin_No == Level3 && Pin_Value ==1) {/*Serial.print("Level 3");*/myTouch.Level3_ON();}    //  Level 3 ON
                        if(Pin_No == Level4 && Pin_Value ==1) {/*Serial.print("Level 4");*/myTouch.Level4_ON();}    //  Level 4 ON
                      }
                      
                      else
                        digitalWrite(Pin_No,Pin_Value); break;                // Relay ON/OFF
                        
              case(222):myTouch.FAN_OFF();              // FAN OFF
                        //Serial.print("FAN OFF"); 
                        break;
                   
              case(111):
                      myTouch.Master_ON(); 
                     //Serial.println("Master ON"); 
                      break;
              case(999):
                      myTouch.Master_OFF();
                      //Serial.println("Master OFF"); 
                      break; 
              
            }     
     
        }   
    load_output_status = myTouch.readLoadstatus();myHBT.print("B:"); 
    //delay(1000);
    myHBT.print(load_output_status);  //Output Status To update into Smartphone app to display current status of lights
    //getStatus.updateStatus(load_output_status); 
   //resetFunc();      //cal reset 
   //Serial.println("Device Reset");
        
      
   }
   if(touch_input ^ prev_touch_input )
  {
      //when BLE is not connected and signals coming from IR Remote and Capsense Board
      //Serial.print("Prev Touch:");Serial.println(prev_touch_input,HEX);
      //Serial.print("Touch_input:");Serial.println(touch_input,HEX);
      
      load_output_status = myTouch.readLoadstatus();      // Output status of Loads
     // Serial.print("Load_Status:");Serial.println(load_output_status,HEX);
      
      temp=touch_input;       // current status byte 
      change = prev_touch_input ^ touch_input;    //if there is a change in state then o/p = !0 
     // Serial.print("Temp:");Serial.println(temp);
      new_state    = change & load_output_status;
      myTouch.cap_setLoad(temp);          //switch as per new_state
      
      prev_touch_input = touch_input;
  
      output_TouchStatus = myTouch.readLoadstatus();myHBT.print("T:"); 
      myHBT.print(output_TouchStatus);  //Output Status0 To update into Smartphone app to display current status of lights
    
  }
 
/// RF Modules Inputs Conditions


if( Curr_RFStatus  ) // Detecting State change
{
  delay(500);       // Debounce delay
  myHBT.print("R:");myHBT.println(Curr_RFStatus);
  switch(Curr_RFStatus)
  {
    case(0x04) :    //4
                 myHBT.println("Lamp1");
                 PORTC ^= _BV(PC6) ;   //PC6 Load 1
                 break;
                
    case(0x02) : PORTB ^=  _BV(PB6);break;  //PB6 Load 2   //////2
    case(0x06) : PORTB ^=  _BV(PB5);break;  // PB5 Load 3  /////6
    case(0x01) : PORTB ^=  _BV(PB4);break;  //PB4 Socket Load 4  ////// 1
    case(0x09) :  // FAN ON default level to Level 1  ///////////9
               
                //PORTB |= (1<<PB7);    //Level1 ON
                //PORTD &= (0<<PD4);    //Level 2 OFF
                //PORTD &= (0<<PD6);    //Level 3 OFF
                //PORTD &= (0<<PD7); 
                
                if(level >= 4)
                {
                  level = 0; 
                  PORTD &= ~ _BV(PD7);    //Load 4 OFF
                  PORTB |= _BV(PB7);    //Load 1 ON
                }
                else if(level == 0)
                { 
                   level = level +1;              
                   PORTB |= _BV(PB7);    //Load 1 ON
                   fon = true;
                   up_in = true;
                }
                break;

    case(0x0D) : // Level DOWN   ////13
                myHBT.println("Down");
                if((fon == true && up_in == true) && (level > 0 && level <= 4))
                {
                  
                  //int portArry[]= {0,6, 6, 5, 4};
                  int portArry[]= {0,7, 4, 6, 7};     //levels bits

                  PORTD &= ~ _BV(portArry[level]);  // OFF present load
                  PORTD |= _BV(portArry[level - 1]);    //Load 2 ON
                  if(level == 1)
                  {
                    PORTB |= _BV(PB7);      //level 1 ON
                  }
                    
                  level = level - 1;
                }
                                
                break;
    case(0x0E) : //Level UP /////////14
                                
                if(fon == true && level <=3)
                {
                  //int portArry[]= {0, 6, 6, 5, 4};
                  int portArry[]= {0,7, 4, 6, 7};     //levels bits

                  PORTB &= ~ _BV(PB7);    //Load 1 OFF
                  PORTD &= ~ _BV(portArry[level]);  // OFF preivous load
                  PORTD |= _BV(portArry[level + 1]);    //Load 2 ON
                  //PORTB |= (1<<PB5);    //Load 3 ON
                  //PORTB |= (1<<PB4);    //Load 4 ON
                  level= level + 1;
                  up_in = true;
                }
                
              break;
            
    
    case(0x0B) : // FAN OFF  //////////11

              PORTB &= ~ _BV(PB7);    //Level1 OFF
              PORTD &= ~ _BV(PD4);    //Level 2 OFF
              PORTD &= ~ _BV(PD6);    //Level 3 OFF
              PORTD &= ~ _BV(PD7);    //Level 4 OFF
  
              
              foff = true;
              fon = false;
              up_in = false;
              level = 0;
              break;
                                
    case(0x0F) :    //Master ON/OFF 
                 if(mstr_on == false)
                 {
                   PORTC |= _BV(PC6);
                   PORTB |= _BV(PB6);
                   PORTB |= _BV(PB5);
                   PORTB |= _BV(PB4);
                   PORTB |= _BV(PB7);    //Level1 ON
                   mstr_on = true;
                 }
                 else if(mstr_on == true)
                 { 
                   PORTC &= ~ _BV(PC6);
                   PORTB &= ~ _BV(PB6);
                   PORTB &= ~ _BV(PB5);
                   PORTB &= ~ _BV(PB4);

                   PORTB &= ~ _BV(PB7);    //Level1 OFF
                   mstr_on =false;  
                 }
                 break;  //Master ON/OFF
  }
  
}
 
  delay(500);    //Update Rate
  wdt_enable(WDTO_4S);
} // loop






