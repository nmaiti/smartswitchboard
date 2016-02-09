#include "BLE.h"
#include "QTouch.h"
#include <TAH.h>


TAH myTahstatus;  //Tah object
QTouch capTouch;



BLE::BLE()
{
  //do notihing
}


byte BLE::getStatus(void)
{
  byte curr_data = capTouch.readCapsense();    //Read current switchboard status
  
                                                //Read all I/P pins status and update a status with return type "String"
  return curr_data;
    
}

void BLE::updateStatus(byte data)      // send to Smart phone App
{
  curr_status = data;                          // send current status to Smartphone
                                               //l11 l10 ,l21 l20 , l31 l30 ,l41 l40 ,l51 l50 m0 m1
  Serial.print("in a updateStatus");
  Serial.println(curr_data);                                                
  
  switch(curr_status)                          
  {
    case(0x00)://Master + ALL switches are OFF   D23,D22,D21,D20,D19 
               myTahstatus.print("s10,s20,s30,s40,s50,m0"); 
               break;
                           
    case(0x01):
              myTahstatus.print("s11,s20,s30,s40,s50,m0");  break;
                
    case(0x02):
              myTahstatus.print("s10,s21,s30,s40,s50,m0"); break;

    case(0x03):
              myTahstatus.print("s11,s21,s30,s40,s50,m0"); break;
    case(0x04):
              myTahstatus.print("s10,s20,s31,s40,s50,m0"); break;
    case(0x05):
              myTahstatus.print("s11,s20,s31,s40,s50,m0"); break;
    case(0x06):
              myTahstatus.print("s10,s21,s31,s40,s50,m0"); break;
     case(0x07):
              myTahstatus.print("s11,s21,s31,s40,s50,m0"); break;
     case(0x08):
              myTahstatus.print("s10,s20,s30,s41,s50,m0"); break;
     case(0x09):
              myTahstatus.print("s11,s21,s30,s41,s50,m0"); break;
     case(0x0A):
             myTahstatus.print("s10,s21,s30,s41,s50,m0"); break;
     case(0x0B):
             myTahstatus.print("s11,s21,s30,s41,s50,m0"); break;
     case(0x0C):
             myTahstatus.print("s10,s20,s31,s41,s50,m0"); break;
     case(0x0D):
             myTahstatus.print("s11,s20,s31,s41,s50,m0"); break;
     case(0x0E):
             myTahstatus.print("s10,s21,s31,s41,s50,m0"); break;
     case(0x0F):
             myTahstatus.print("s11,s21,s31,s41,s50,m0"); break;
     case(0x10):
             myTahstatus.print("s10,s20,s30,s40,s51,m0"); break;
     case(0x11):
             myTahstatus.print("s11,s20,s30,s40,s51,m0"); break;
     case(0x12):
             myTahstatus.print("s10,s21,s30,s40,s51,m0"); break;
     case(0x13):
             myTahstatus.print("s11,s21,s30,s40,s51,m0"); break;
     case(0x14):
             myTahstatus.print("s10,s20,s31,s40,s51,m0"); break;
     case(0x15):
             myTahstatus.print("s11,s20,s31,s40,s51,m0"); break;
     case(0x16):
             myTahstatus.print("s10,s21,s31,s40,s51,m0"); break;
     case(0x17):
             myTahstatus.print("s11,s21,s31,s40,s51,m0"); break;
     case(0x18):
             myTahstatus.print("s10,s20,s30,s41,s51,m0"); break;
     case(0x19):
             myTahstatus.print("s11,s20,s30,s41,s51,m0"); break;
     case(0x1A):
             myTahstatus.print("s10,s21,s30,s41,s51,m0"); break;
     case(0x1B):
             myTahstatus.print("s11,s21,s30,s41,s51,m0"); break;
     case(0x1C):
             myTahstatus.print("s10,s20,s31,s41,s51,m0"); break;
     case(0x1D):
             myTahstatus.print("s11,s20,s31,s41,s51,m0"); break;
     case(0x1E):
             myTahstatus.print("s10,s21,s31,s41,s51,m0"); break;
     case(0x1F):
             myTahstatus.print("s11,s21,s31,s41,s51,m0"); break;
     case(0x20):
             myTahstatus.print("s10,s20,s30,s40,s50,m1"); break;
          
          // from here below all coditions Master gets ON
  }    
    
}


