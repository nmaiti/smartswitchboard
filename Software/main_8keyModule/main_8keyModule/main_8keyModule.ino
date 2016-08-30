/* Project: Smart Switch Board Vr1
   Author:Vikas Gaikwad
   Date  :05/07/2015
   Descriptions:  This is a Smart Switch board can be communicated with Capsense Touch Switch Board,IR Remote and a Bluetooth Low Energy [BTL4.0] using Smart Phone.  
                  Followed the Protocol while communicating through BLE4.0 to set and get Acknowledgement from Host microcontroller.
   Note:    1. When User connected to Module over IR Remote and Touch for every event it should update to BLE (in Smartphone App).
            2. Touch || IR Remote || BLE 
               i) Touch= Direct control (TTL)
               ii)IR Remote = check for 32-bit IR code
               iii)BLE4.0 =  Acess string to contol and Read Status of Boards   
 */

#include <avr/wdt.h>
#include <TAH.h>
#include <IRLib.h>
//#include <Servo.h>
//#include <PinChangeInt.h>
#include "QTouch.h"
#include "IR.h"
#include "BLE.h"



TAH myTAH;
QTouch myTouch;  //objects
IR myIR;
BLE myBLE;

//Global Variables

int Pin_Type;    //  Stores Pin Type  
int Pin_No;      //  Stores Pin Number
int Pin_Value;   //  Stores Pin Value 

//Servo servo[12];

int RECV_PIN= 11;

volatile byte touch_input=0,prev_touch_input=0,temp,change,new_state;
volatile byte load_output_status=0;
volatile unsigned long int channel_no;
int switch_num=0;


IRrecv My_Receiver(RECV_PIN);
IRdecode My_Decoder;


void setup()
{
  Serial.begin(9600);
  myTAH.begin(9600);

  myTAH.enterCommandMode();

  myTAH.setName("Bed Room");
  myTAH.setTransmissionPower(Six);
  myTAH.setWorkRole(SLAVE);
  myTAH.setAuth(OPEN);
  myTAH.setWorkMode(REMOTE_CONTROL);
  myTAH.setiBeaconMode(On);
  
  myTAH.exitCommandMode();

  myTouch.gpioInit();    // set all pins
  
  My_Receiver.enableIRIn(); // Start the receiver
  digitalWrite(RECV_PIN, HIGH); //use the internal pullup resistor
  //PCintPort::attachInterrupt(RECV_PIN,irControl,RISING); // attach a PinChange Interrupt to our pin on the rising edge
    
}  
/*
void irControl()
{ Serial.println("******************");
    if (My_Receiver.GetResults(&My_Decoder)) {
    //Restart the receiver so it can be capturing another code
    //while we are working on decoding this one.
    My_Receiver.resume(); 
    My_Decoder.decode();
    //My_Decoder.DumpResults();
    unsigned long int decodedValue =0;
    channel_no = My_Decoder.value;
    Serial.print("Channel No:");Serial.println(channel_no,HEX);
    
    myIR.ir_setLoad(channel_no);        //set the Load
  }
}
*/


void loop()
{  
   
     
  // channel_no =  irDecoder();           //Decode Remote Signals
   touch_input = myTouch.readCapsense();  //Read capsense values
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
    if(myTAH.read() =='H')
    {
        //if Pin Type is 0 means Digital Output      
       switch(Pin_Type)
       {
          case(0):
                  if((Pin_No == Level1 || Pin_No == Level2 || Pin_No == Level3 || Pin_No == Level4) && (Pin_Value == 1)) 
                  {
                    if(Pin_No == Level1 && Pin_Value ==1){ myTouch.FAN_ON();}
                    if(Pin_No == Level2 && Pin_Value ==1){ myTouch.Level2_ON();}
                    if(Pin_No == Level3 && Pin_Value ==1) {myTouch.Level3_ON();}
                    if(Pin_No == Level4 && Pin_Value ==1) {myTouch.Level4_ON();}   
                  }
                  else
                    digitalWrite(Pin_No,Pin_Value); break;
          
          case(222):myTouch.FAN_OFF();
               
          case(1):  //PWM dimming
                //servo[Pin_No].detach();
                analogWrite(Pin_No,Pin_Value); break;
       
          case(111):
                  myTouch.Master_ON(); break;
                 // Serial.println("Master ON"); 
          case(999):
                  myTouch.Master_OFF(); break;
                  //Serial.println("Master OFF"); 
  
      }     
 
    }   
    load_output_status = myTouch.readLoadstatus();/*;myTAH.print("v:");*/myTAH.print(load_output_status);  //Output Status To update into Smartphone app
        
      
   }
    if(touch_input != prev_touch_input)
  {
    //when BLE is not connected and signals coming from IR Remote and Capsense Board
    //Serial.print("Prev Touch:");Serial.println(prev_touch_input,HEX);
    //Serial.print("Touch_input:");Serial.println(touch_input,HEX);
    
    load_output_status = myTouch.readLoadstatus();
   // Serial.print("Load_Status:");Serial.println(load_output_status,HEX);
    
    temp=touch_input;
    change = prev_touch_input ^ touch_input;    //if there is a change in state then o/p = !0 
   // Serial.print("Temp:");Serial.println(temp);
    new_state    = change & load_output_status;
    myTouch.cap_setLoad(temp);          //switch as per new_state
    
    prev_touch_input = touch_input;
    
  }
 
 if (My_Receiver.GetResults(&My_Decoder)) {
    //Restart the receiver so it can be capturing another code
    //while we are working on decoding this one.
    My_Receiver.resume(); 
    My_Decoder.decode();
    //My_Decoder.DumpResults();
    unsigned long int decodedValue =0;
    channel_no = My_Decoder.value;
    Serial.print("Channel No:");Serial.println(channel_no,HEX);
    
    myIR.ir_setLoad(channel_no);        //set the Load
  }
  
 /*if(channel_no !=0 && (channel_no == Master || channel_no == one || channel_no == two || channel_no == three || channel_no == four || channel_no == five || channel_no == six || channel_no == seven || channel_no == eight || channel_no == nine || channel_no == zero || channel_no == FAN || channel_no == UP || channel_no == DOWN))
  {
    myIR.ir_setLoad(channel_no);
  }
*/
  delay(500);    //Update Rate
wdt_enable(WDTO_4S);
//Serial.println("RESET");
} // loop
 






