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
#include <TAH.h>
#include <EEPROM.h>
#include <Wire.h>   // Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include "QTouch.h"
#include "BLE.h"

//#include "RTClib.h"



//RTC_DS1307 rtc;
TAH myTAH;          // Object Variables
QTouch myTouch;  
BLE getStatus;

//char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


//Global Variables

int Pin_Type;    //  Stores Pin Type  
int Pin_No;      //  Stores Pin Number
int Pin_Value;   //  Stores Pin Value 

/// RF Modules Output pins as Input to MCU PB0 - PB3

#define RFD0  14    //D14
#define RFD1  16    //D16(RFD2)
#define RFD2  17    //D17(RFD3)
#define RFD3  15    //D15(RFD1)

/// Using PinChange Interrupt0

volatile byte touch_input=0,prev_touch_input=0,temp,change,new_state;
volatile byte load_output_status=0,output_TouchStatus=0;
volatile byte Curr_RFStatus=0,prevRFStatus=0;

int switch_num=0;



void setup()
{
  Serial.begin(9600);
  myTAH.begin(9600);

  myTAH.enterCommandMode();

  myTAH.setName("HBT_Test");
  myTAH.setTransmissionPower(Six);
  myTAH.setWorkRole(SLAVE);
  myTAH.setAuth(OPEN);
  myTAH.setWorkMode(REMOTE_CONTROL);
  myTAH.setiBeaconMode(On);
  
  myTAH.exitCommandMode();

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
/// Pin Change Interrupt 
/// define the pins

pinMode(RFD0,INPUT);
pinMode(RFD1,INPUT);
pinMode(RFD2,INPUT);
pinMode(RFD3,INPUT);

//DDRB = 0b11110000 ;   // PB0 - PB3 RF Input Pins

sei();      //Enable Global Interrupt

}  

void loop()
{  
        
   touch_input = myTouch.readCapsense() & 0x7F;  //Read capsense values
   
   //Serial.println(touch_input,HEX);
   
   if(myTAH.available()>0)                //phone connected and Rx commands
   {
      Pin_Type = myTAH.parseInt();
      Pin_No = myTAH.parseInt();
      Pin_Value = myTAH.parseInt();

      Serial.print(Pin_Type);
      Serial.print(",");
      Serial.print(Pin_No);
      Serial.print(","); 
      Serial.println(Pin_Value);
      Serial.print("I am Here");
     // myTouch.LightControl(Pin_No,Pin_Value);
    if(myTAH.read() =='H')                      // detects endline character "H"
    {
        Serial.print("I am in if.read()");
        //if Pin Type is 0 means Digital Output      
       switch(Pin_Type)
       {
          case(0):
                  if((Pin_No == Level1 || Pin_No == Level2 || Pin_No == Level3 || Pin_No == Level4) && (Pin_Value == 1))    // Any one Level is selected and Value set to HIGH 
                  { Serial.print("In Case 0");
                    if(Pin_No == Level1 && Pin_Value ==1){ Serial.print("Level 1");myTouch.FAN_ON();}       //  Level 1 ON 
                    if(Pin_No == Level2 && Pin_Value ==1){ Serial.print("Level 2");myTouch.Level2_ON();}    //  Level 2 ON
                    if(Pin_No == Level3 && Pin_Value ==1) {Serial.print("Level 3");myTouch.Level3_ON();}    //  Level 3 ON
                    if(Pin_No == Level4 && Pin_Value ==1) {Serial.print("Level 4");myTouch.Level4_ON();}    //  Level 4 ON
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
    load_output_status = myTouch.readLoadstatus();myTAH.print("B:"); 
    //delay(1000);
    myTAH.print(load_output_status);  //Output Status To update into Smartphone app to display current status of lights
    //getStatus.updateStatus(load_output_status); 
        
      
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

    output_TouchStatus = myTouch.readLoadstatus();myTAH.print("T:"); 
    myTAH.print(output_TouchStatus);  //Output Status0 To update into Smartphone app to display current status of lights
    
  }
 
/// RF Modules Inputs Conditions

Curr_RFStatus = PINB & 0x0F;      //Read RF Status

if( Curr_RFStatus ) // Detecting State change
{
  switch(Curr_RFStatus)
  {
    case(0x01) :
                 PORTC = (PORTC ^ 0x40) ;   //PC6 Load1
                 break;
                
    case(0x02) : PORTB = (PORTB ^ 0x40);break;  //PB6 Load2
    case(0x03) : PORTB = (PORTB ^ 0x20);break;  // PB5 Load3  
    case(0x04) : PORTB = (PORTB ^ 0x10);break;  //PB4 Socket Load 4
  }
  
}
 
  delay(500);    //Update Rate
  wdt_enable(WDTO_4S);
} // loop






