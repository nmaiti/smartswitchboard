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


IR::IR()
{
  //do nothing
}


void IR::ir_setLoad(unsigned long int number)
{
  curr_number = number;
  prev_number;
  Serial.print("On Start Prev_Number:");Serial.println(prev_number,HEX);
  switch(curr_number)
  {
    
    case(Master):
                if(prev_number != curr_number)  // new key pressed
                {
                    //Master ON action
                    Serial.println("Master ON");    //OFF to ON
                    touch.Master_ON();
                }                    
                else
                  {
                    if(curr_number == Master){
                    Serial.println("MAster OFF");    //ON to OFF
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
                    Serial.println("Lamp0 ON");    //OFF to ON
                    
                }                    
                else
                  {
                    if(curr_number == zero){
                    Serial.println("Lamp0 OFF");    //ON to OFF
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
                    Serial.println("Lamp1 ON");    //OFF to ON
                    touch.L1_ON();
                }                    
                else
                  {
                    if(curr_number == one){
                    Serial.println("Lamp1 OFF");    //ON to OFF
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
                    Serial.println("Lamp2 ON");    //OFF to ON
                    touch.L2_ON();
                }                    
                else
                  {
                    if(curr_number == two){
                    Serial.println("Lamp2 OFF");    //ON to OFF
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
                    Serial.println("Lamp3 ON");    //OFF to ON
                    touch.L3_ON();
                }                    
                else
                  {
                    if(curr_number == three){
                    Serial.println("Lamp3 OFF");    //ON to OFF
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
                    Serial.println("Lamp4 ON");    //OFF to ON
                    touch.L4_ON();
                }                    
                else
                  {
                    if(curr_number == four){
                    Serial.println("Lamp4 OFF");    //ON to OFF
                    touch.L4_OFF();
                    curr_number = 0;
                  }
                  }
                prev_number = curr_number;
                break;
   case(five):
               if(prev_number != curr_number)  // new key pressed
                {
                    //Lamp5 ON
                    Serial.println("Lamp5 ON");    //OFF to ON
                    touch.L5_ON();
                }                    
                else
                  {
                    if(curr_number == five){
                    Serial.println("Lamp5 OFF");    //ON to OFF
                    touch.L5_OFF();
                    curr_number = 0;
                  }
                  }
                prev_number = curr_number;          
                break;
    //Other conditions were never used its a 6 key Module 
  }
}

       


                

 
 

  

