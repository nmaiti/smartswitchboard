#ifndef  IR_h
#define  IR_h

#include <Arduino.h>
#include <TAH.h>
#include "QTouch.h"


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

class IR
{
  
  public:
  
  int i=0;
  IR();        //constructor
  //unsigned int readIRSignal(unsigned long int decodedvalue);
  void ir_setLoad(unsigned long int number);
  
  private:
  
  //unsigned long int curr_decodedvalue;
  //unsigned long int prev_decodedvalue;
  unsigned long int curr_number=0;
  unsigned long int prev_number=0;
  
};

#endif
  
  
  
