  /* Project: Smart Switch Board Vr1
   Author:Vikas Gaikwad
   Date  :05/07/2015
   Descriptions:  This is a Smart Switch board can be communicated with Capsense Touch,IR Remote and a Bluetooth Low Energy using Smart Phone.  
                  Followed the Protocol while communicating through BLE4.0 to set and get Acknowledgement from Host microcontroller.
   Note:    1. When User connected to Module over IR Remote and Touch for every event it should update to BLE (in Smartphone App).
            2. Touch || IR Remote || BLE 
               i) Touch= Direct control (TTL)
               ii)IR Remote = check for 32-bit IR code
               iii)BLE4.0 =  Acess string to contol and Read Status of Boards   
 */


#include <TAH.h>
#include <IRLib.h>
#include <PinChangeInt.h>
#include "QTouch.h"
#include "IR.h"
#include "BLE.h"

#define  Lamp1_OFF   0x41  //A
#define  Lamp1_ON    0x61  //a
#define  Lamp2_OFF   0x42  //B
#define  Lamp2_ON    0x62  //b
#define  Lamp3_OFF   0x43  //C
#define  Lamp3_ON    0x63  //c
#define  Lamp4_OFF   0x44  //D
#define  Lamp4_ON    0x64  //d
#define  Lamp5_OFF   0x45  //E
#define  Lamp5_ON    0x65  //e
#define  master_OFF  0x46  //F
#define  master_ON   0x66  //f


TAH myTAH;
QTouch myTouch;  //objects
IR myIR;
BLE myBLE;

//Global Variables

int RECV_PIN= 11;

volatile byte touch_input=0,prev_touch_input,temp,change,new_state;
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

  myTAH.setName("BedRoom");
  myTAH.setTransmissionPower(Six);
  myTAH.setWorkRole(SLAVE);
  myTAH.setAuth(OPEN);
  myTAH.setWorkMode(REMOTE_CONTROL);
  myTAH.setiBeaconMode(ON);
  
  myTAH.exitCommandMode();

  myTouch.gpioInit();    // set all pins
  
  My_Receiver.enableIRIn(); // Start the receiver
  digitalWrite(RECV_PIN, HIGH); //use the internal pullup resistor
  myTouch.L4_OFF();
  myTouch.L5_OFF();
  
  
}  

unsigned long int irDecoder()
{
     if (My_Receiver.GetResults(&My_Decoder)) {
    //Restart the receiver so it can be capturing another code
    //while we are working on decoding this one.
    My_Receiver.resume(); 
    My_Decoder.decode();
    //My_Decoder.DumpResults();
    unsigned long int decodedValue =0;
    decodedValue = My_Decoder.value;
        
    return decodedValue; 
   }
  
}



void loop()
{  
   
     
   channel_no =  irDecoder();           //Decode Remote Signals
   touch_input = myTouch.readCapsense();  //Read capsense values
   
   
   if(myTAH.available()>0)          //phone connected and Rx commands
   {
      // When Smart Phone is connected
      
        switch_num = myTAH.read();
         
       
        
        switch(switch_num)
        {
          case(Lamp1_ON):
                      myTouch.L1_ON(); break;
          case(Lamp1_OFF):
                      myTouch.L1_OFF();break;
          case(Lamp2_ON):
                      myTouch.L2_ON(); break;
          case(Lamp2_OFF):
                      myTouch.L2_OFF();break;
          case(Lamp3_ON):
                      myTouch.L3_ON(); break;
          case(Lamp3_OFF):
                      myTouch.L3_OFF();break;
          case(Lamp4_ON):
                      myTouch.L4_ON(); break;
          case(Lamp4_OFF):
                      myTouch.L4_OFF();break;
          case(Lamp5_ON):
                      myTouch.L5_ON(); break;
          case(Lamp5_OFF):
                      myTouch.L5_OFF();break;
          case(master_ON):
                      myTouch.Master_ON();break;
          case(master_OFF):
                      myTouch.Master_OFF();break;
                      
        }
        load_output_status = myTouch.readLoadstatus();myTAH.print("v:");myTAH.print(load_output_status);  //Output Status To update into Smartphone app
        
      
   }
   else if(touch_input != prev_touch_input)
  {
    //when BLE is not connected and signals coming from IR Remote and Capsense Board
   // Serial.print("Prev Touch:");Serial.println(prev_touch_input,HEX);
   // Serial.print("Touch_input:");Serial.println(touch_input,HEX);
    
    load_output_status = myTouch.readLoadstatus();
   // Serial.print("Load_Status:");Serial.println(load_output_status,HEX);
    
    temp=touch_input;
    change = prev_touch_input ^ touch_input;    //if there is a change in state then o/p = !0 
   // Serial.print("Temp:");Serial.println(temp);
    new_state    = change & load_output_status;
    myTouch.cap_setLoad(temp);          //switch as per new_state
    
    prev_touch_input = touch_input;
    
  }
 if(channel_no !=0 && (channel_no == Master || channel_no == one || channel_no == two || channel_no == three || channel_no == four || channel_no == five || channel_no == six || channel_no == seven || channel_no == eight || channel_no == nine || channel_no == zero || channel_no == FAN || channel_no == UP || channel_no == DOWN))
  {
    myIR.ir_setLoad(channel_no);
  }

  delay(500);
} // loop
 






