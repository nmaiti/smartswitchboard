/**************************************************************

*File:IR.cpp
 Author:Vikas Gaikwad
*Description: This file contains the  Methods of class IR

*Date:05-07-2015

*
****************************************************************/
#include "QTouch.h"
#include "IR.h"


QTouch touch;
volatile byte level=1;
boolean Fan_On =false;

IR::IR()
{
  //do nothing
}

/*==========================================================================================================================================

Fan Spped Control code here

============================================================================================================================================*/

void IR::FanSpeedControl(byte level)
{
  byte curr_level = level;
  
  switch(curr_level)
  {
    case(Level_1):
                  //Serial.println("FAN at Level_1");
                  touch.FAN_ON();touch.Level2_OFF();touch.Level3_OFF();touch.Level4_OFF();
                  //Only Level_1 Triac will be ON others OFF
                  break;
    case(Level_2):
                  //Serial.println("FAN at Level_2");
                  //Only Level_1 Triac will be ON others OFF
                  touch.Level2_ON();touch.Level3_OFF();touch.Level4_OFF();
                  digitalWrite(Level1,LOW);
                  break;
    case(Level_3):
                  //Serial.println("FAN at Level_3");
                 //Only Level_1 Triac will be ON others OFF
                  touch.Level3_ON();touch.Level2_OFF();touch.Level4_OFF();
                  digitalWrite(Level1,LOW);
                  break;    
    case(Level_4):
                  //Serial.println("FAN at Level_4");
                  //Only Level_1 Triac will be ON others OFF
                  touch.Level4_ON();touch.Level2_OFF();touch.Level3_OFF();
                  digitalWrite(Level1,LOW);
                  break;
  }
}

/*=========================================================================================================================

Set Output Load 
===========================================================================================================================*/

void IR::ir_setLoad(unsigned long int number)
{
  curr_number = number;
  prev_number;  
  //Serial.print("On Start Prev_Number:");Serial.println(prev_number,HEX);
  switch(curr_number)
  {
    
    case(Master):
                if(prev_number != curr_number)  // new key pressed
                {
                    //Master ON action
                    //Serial.println("Master ON");    //OFF to ON 
                    touch.Master_ON();
                }                    
                else
                  {
                    if(curr_number == Master){
                    //Serial.println("MAster OFF");    //ON to OFF
                    touch.Master_OFF();
                    //Serial.println("Reset"); 
                    curr_number = 0;
                  }
                  }
                prev_number = curr_number;               
                break;
   case(zero):
               if(prev_number != curr_number)  // new key pressed
                {
                    //Master Lamp0 ON
                    //Serial.println("Lamp0 ON");    //OFF to ON
                    
                }                    
                else
                  {
                    if(curr_number == zero){
                    //Serial.println("Lamp0 OFF");    //ON to OFF
                    //Serial.println("Reset"); 
                    curr_number = 0;
                  }
                  }
                prev_number = curr_number;          
                break;
    case(one):
              if(prev_number != curr_number)  // new key pressed
                {
                    //Lamp1 ON
                    //Serial.println("Lamp1 ON");    //OFF to ON
                    touch.L1_ON();
                }                    
                else
                  {
                    if(curr_number == one){
                    //Serial.println("Lamp1 OFF");    //ON to OFF
                    touch.L1_OFF();
                    curr_number = 0;
                  }
                  }
                prev_number = curr_number; 
                break;
   case(two):
               if(prev_number != curr_number)  // new key pressed
                {
                    //Lamp 2 ON
                    //Serial.println("Lamp2 ON");    //OFF to ON
                    touch.L2_ON();
                }                    
                else
                  {
                    if(curr_number == two){
                    //Serial.println("Lamp2 OFF");    //ON to OFF
                    touch.L2_OFF();
                    curr_number = 0;
                  }
                  }
                prev_number = curr_number;          
                break;
  case(three):
             if(prev_number != curr_number)  // new key pressed
                {
                    //Lamp 3 ON 
                    //Serial.println("Lamp3 ON");    //OFF to ON
                    touch.L3_ON();
                }                    
                else
                  {
                    if(curr_number == three){
                    //Serial.println("Lamp3 OFF");    //ON to OFF
                    touch.L3_OFF();
                    curr_number = 0;
                  }
                  }
                prev_number = curr_number;         
                break;
   case(four):
              if(prev_number != curr_number)  // new key pressed
                {
                    //Lamp4 ON
                    //Serial.println("Lamp4 ON");    //OFF to ON
                    touch.Socket_ON();
                }                    
                else
                  {
                    if(curr_number == four){
                    //Serial.println("Lamp4 OFF");    //ON to OFF
                    touch.Socket_OFF();
                    curr_number = 0;
                  }
                  }
                prev_number = curr_number;
                break;
   
    //Other conditions were never used its a 6 key Module
    //Adding Fan regulator code using IR Remote
   case(FAN):
               if(prev_number != UP && prev_number != DOWN && prev_number != curr_number)  // new key pressed
                {
                    Fan_On = true;
                    //FAN ON
                    //Serial.println("FAN ON and Level_1 Triac ON");    //OFF to ON
                    FanSpeedControl(level);    //Set to default level
                                         
                }                    
                else                                   //FAN OFF no level UP/DOWN inputs considered 
                {
                    if(Fan_On == true && curr_number == FAN){
                    //Serial.println("FAN OFF");    //ON to OFF
                    curr_number = 0;
                    level = 1;
                    Fan_On = false;
                    touch.FAN_OFF();
                  }
                }
                prev_number = curr_number;          
                break;
case(UP):
               if(Fan_On == true && prev_number != curr_number)  // new key pressed
                {
                    level++;
                    //shift to Level_2
                    FanSpeedControl(level);
                    //Serial.print("UP Level");Serial.println(level);
                }                    
                else if(Fan_On == true && curr_number == UP && level <= 3)
                 {
                    level++;
                    FanSpeedControl(level);
                    //Serial.print("UP Level");Serial.println(level);
                    //shift to level 3
                    curr_number = 0;
                  }
                               
                prev_number = curr_number;          
                break;
case(DOWN):
            if(Fan_On == true && prev_number != curr_number)
            {
              level--;
              FanSpeedControl(level);
              //Serial.print("DOWN Level:");Serial.println(level);
            }
            else if(Fan_On == true && curr_number == DOWN && level >2)
            {
              level--;
              FanSpeedControl(level);
              //Serial.print("DOWN Level:");Serial.println(level);
              curr_number = 0;
            }
            prev_number = curr_number;
            break;
    
  }
}

       


                

 
 

  

