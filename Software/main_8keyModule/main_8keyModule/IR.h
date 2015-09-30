#ifndef  IR_h
#define  IR_h

#include <Arduino.h>
#include <TAH.h>
#include "QTouch.h"

#define  FAN    0x1FE58A7
#define  UP     0x1FE609F
#define  DOWN   0x1FEA05F
#define  Master 0x1FE48B7
#define  zero   0x1FEE01F
#define  one    0x1FE50AF
#define  two    0x1FED827
#define  three  0x1FEF807
#define  four   0x1FE30CF
#define  five   0x1FEB04F
#define  six    0x1FE708F
#define  seven  0x1FE00FF
#define  eight  0x1FEF00F
#define  nine   0x1FE9867

//Fan Speed Levels 
#define Level_1  1
#define Level_2  2
#define Level_3  3
#define Level_4  4




class IR
{
  
  public:
  
  int i;
  IR();        //constructor
  //unsigned int readIRSignal(unsigned long int decodedvalue);
  void ir_setLoad(unsigned long int number);
  void FanSpeedControl(byte level);

  
  private:
  
  //unsigned long int curr_decodedvalue;
  //unsigned long int prev_decodedvalue;
  unsigned long int curr_number;
  unsigned long int prev_number;
  
};

#endif
  
  
  
