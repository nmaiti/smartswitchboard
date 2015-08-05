/**************************************************************

*File:QTouch.cpp
 Author:Vikas Gaikwad
*Description: This file contains the  Methods of class QTouch

*Date:05-07-2015

*
****************************************************************/

#include "QTouch.h"
#include "BLE.h"
#include <TAH.h>

BLE mystatus;



QTouch::QTouch()
{
  //do nothings

}
/*========================================================================================================

	File: QTouch.cpp/

	Description: This File Contains the Methods of configuring the GPIO, INPUT and OUTPUT pinModes

	class: QTouch	

	Method: gpioInit()	

==========================================================================================================*/
void QTouch::gpioInit(void)
{
  
  unsigned int capsensepins[6] = {Lamp1,Lamp2,Master,Lamp3,Lamp4,Lamp5};
  unsigned int loadoutpins[6] = {Load1,Load2,Load3,Load4,Load5,Load6};//Load6=NC

  //Set Pinmodes of I/O pins

  for(int i=0;i<6;i++)
  {
    pinMode(capsensepins[i],INPUT);
    pinMode(loadoutpins[i],OUTPUT);
  }  
  
  //Set pinValue to LOW
  
  for(int i=0;i<6;i++)
  {
    digitalWrite(capsensepins[i],LOW);
    digitalWrite(loadoutpins[i],HIGH);
  }
    
  
}
/*========================================================================================================

	File: QTouch.cpp

	Description: This methods used to set the Respective AC Loads 

==========================================================================================================*/

void QTouch::L1_ON(void)
{
  digitalWrite(Load1,LOW);
}

void QTouch::L2_ON(void)
{
  digitalWrite(Load2,LOW);
}

void QTouch::L3_ON(void)
{
  digitalWrite(Load3,LOW);
}

void QTouch::L4_ON(void)
{
  digitalWrite(Load4,LOW);
}

void QTouch::L5_ON(void)
{
  digitalWrite(Load5,LOW);
}

void QTouch::Master_ON(void)  // Now Master is ON == Make ALL ON
{
  //curr_status = getstatus;
  /*digitalWrite(Load1,HIGH);
  digitalWrite(Load2,HIGH);
  digitalWrite(Load3,HIGH);
  digitalWrite(Load4,HIGH);  //Make them ON
  digitalWrite(Load5,HIGH);
  delay(5000);  */
  digitalWrite(Load1,LOW);
  digitalWrite(Load2,LOW);
  digitalWrite(Load3,LOW);
  digitalWrite(Load4,LOW);  //Make them OFF
  digitalWrite(Load5,LOW);
  
}
/*========================================================================================================

	File: QTouch.cpp

	Description: This methods used to Switch OFF the Respective AC Loads 

==========================================================================================================*/

void QTouch::L1_OFF(void)
{
  digitalWrite(Load1,HIGH);
}

void QTouch::L2_OFF(void)
{
  digitalWrite(Load2,HIGH);
  
}

void QTouch::L3_OFF(void)
{
  digitalWrite(Load3,HIGH);

}

void QTouch::L4_OFF(void)
{
  digitalWrite(Load4,HIGH);

}

void QTouch::L5_OFF(void)
{
  digitalWrite(Load5,HIGH);

}

void QTouch::Master_OFF(void)
{
  digitalWrite(Load1,HIGH);
  digitalWrite(Load2,HIGH);
  digitalWrite(Load3,HIGH);
  digitalWrite(Load4,HIGH);  //Make them OFF
  digitalWrite(Load5,HIGH);
  
}
/*========================================================================================================

	File: QTouch.cpp

	Description: This method use to read Capsense Switch Board Inputs contineously
	             and returns a 8-bit number(byte)

==========================================================================================================*/

byte QTouch::readCapsense()
{
  //Read the Input Port Status and returns int value
  
  boolean l1 = digitalRead(Lamp1);
  boolean l2 = digitalRead(Lamp2);
  boolean l3 = digitalRead(Lamp3);
  boolean l4 = digitalRead(Lamp4);
  boolean l5 = digitalRead(Lamp5);
  boolean l6 = digitalRead(Master);
  
  byte no[8] = {l1,l2,l3,l4,l5,l6};
  byte val=0;
  
  for(int i=0;i<=7;i++)
  {
    val|= (no[i]<< i);    //convert bits to byte
  }
      
  //Serial.print(val);
   
  return val;
  
}

/*========================================================================================================

	File: QTouch.cpp

	Description: This method used to set the Load as per present Capsense Inputs 

==========================================================================================================*/


void QTouch::cap_setLoad(byte loadValue)
{
  m_loadValue = loadValue;
  prev_loadValue = m_loadValue;
  
  switch(m_loadValue)
  {
    case(0x00)://Master + ALL switches are OFF   D23,D22,D21,D20,D19 
             /*Master_OFF();*/L5_OFF();L4_OFF();L3_OFF();L2_OFF();L1_OFF(); break;
              
    case(0x01):
             /*Master_OFF();*/L5_OFF();L4_OFF();L3_OFF();L2_OFF();L1_ON(); break;
  
    case(0x02):
             /*Master_OFF();*/L5_OFF();L4_OFF();L3_OFF();L2_ON();L1_OFF();  break;

    case(0x03):
             /*Master_OFF();*/L5_OFF();L4_OFF();L3_OFF();L2_ON();L1_ON();  break;

    case(0x04):
             Master_OFF();L5_OFF();L4_OFF();L3_ON();L2_OFF();L1_OFF();  break;
     
    case(0x05):
             /*Master_OFF();*/L5_OFF();L4_OFF();L3_ON();L2_OFF();L1_ON();  break;
 
     case(0x06):
             /*Master_OFF();*/L5_OFF();L4_OFF();L3_ON();L2_ON();L1_OFF();  break;

     case(0x07):
             /*Master_OFF();*/L5_OFF();L4_OFF();L3_ON();L2_ON();L1_ON();  break;
    
     case(0x08):
             /*Master_OFF();*/L5_OFF();L4_ON();L3_OFF();L2_OFF();L1_OFF();  break;

     case(0x09):
             /*Master_OFF();*/L5_OFF();L4_ON();L3_OFF();L2_OFF();L1_ON();  break;

     case(0x0A):
             /*Master_OFF();*/L5_OFF();L4_ON();L3_OFF();L2_ON();L1_OFF();  break;

     case(0x0B):
             /*Master_OFF();*/L5_OFF();L4_ON();L3_OFF();L2_ON();L1_ON();  break;

     case(0x0C):
             /*Master_OFF();*/L5_OFF();L4_ON();L3_ON();L2_OFF();L1_OFF();  break;

     case(0x0D):
             /*Master_OFF();*/L5_OFF();L4_ON();L3_ON();L2_OFF();L1_ON();  break;
    
     case(0x0E):
             /*Master_OFF();*/L5_OFF();L4_ON();L3_ON();L2_ON();L1_OFF();  break;

     case(0x0F):
             /*Master_OFF();*/L5_OFF();L4_ON();L3_ON();L2_ON();L1_ON();  break;

     case(0x10):
             /*Master_OFF();*/L5_ON();L4_OFF();L3_OFF();L2_OFF();L1_OFF();  break;
  
     case(0x11):
             /*Master_OFF();*/L5_ON();L4_OFF();L3_OFF();L2_OFF();L1_ON();  break;

     case(0x12):
             /*Master_OFF();*/L5_ON();L4_OFF();L3_OFF();L2_ON();L1_OFF();  break;

     case(0x13):
             /*Master_OFF();*/L5_ON();L4_OFF();L3_OFF();L2_ON();L1_ON();  break;

     case(0x14):
             /*Master_OFF();*/L5_ON();L4_OFF();L3_ON();L2_OFF();L1_OFF();  break;

     case(0x15):
             /*Master_OFF();*/L5_ON();L4_OFF();L3_ON();L2_OFF();L1_ON();  break;

     case(0x16):
            /*Master_OFF();*/L5_ON();L4_OFF();L3_ON();L2_ON();L1_OFF();  break;

     case(0x17):
            /*Master_OFF();*/L5_ON();L4_OFF();L3_ON();L2_ON();L1_ON();  break;

     case(0x18):
            /*Master_OFF();*/L5_ON();L4_ON();L3_OFF();L2_OFF();L1_OFF();  break;

     case(0x19):
            /*Master_OFF();*/L5_ON();L4_ON();L3_OFF();L2_OFF();L1_ON();  break;

     case(0x1A):
            /*Master_OFF();*/L5_ON();L4_ON();L3_OFF();L2_ON();L1_OFF();  break;

     case(0x1B):
            /*Master_OFF();*/L5_ON();L4_ON();L3_OFF();L2_ON();L1_ON();  break;

     case(0x1C):
            /*Master_OFF();*/L5_ON();L4_ON();L3_ON();L2_OFF();L1_OFF();  break;
           
     case(0x1D):
            /*Master_OFF();*/L5_ON();L4_ON();L3_ON();L2_OFF();L1_ON();  break;

     case(0x1E):
            /*Master_OFF();*/L5_ON();L4_ON();L3_ON();L2_ON();L1_OFF();  break;

     case(0x1F):
            /*Master_OFF();*/L5_ON();L4_ON();L3_ON();L2_ON();L1_ON();  break;

     case(0x20):// master i/p ON
                  Master_OFF();/*L5_OFF();L4_OFF();L3_OFF();L2_OFF();L1_OFF();*/  break;
               
          // from here in all coditions Master gets ON
     
    }
          
}

byte QTouch::readLoadstatus(void)
{
  //read output pins status
  
  boolean s1 = digitalRead(Load1);
  boolean s2 = digitalRead(Load2);
  boolean s3 = digitalRead(Load3);
  boolean s4 = digitalRead(Load4);
  boolean s5 = digitalRead(Load5);
 
  
  byte no[8] = {s1,s2,s3,s4,s5};
  byte val=0;
  
  for(int i=0;i<=7;i++)
  {
    val|= (no[i]<< i);    //convert bits to byte
  }
      
  //Serial.print(val);
  return val;
}
