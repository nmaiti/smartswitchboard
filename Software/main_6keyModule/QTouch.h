#ifndef  QTouch_h
#define  QTouch_h

#include <Arduino.h>
#include <TAH.h>
#include "BLE.h"


// Capsence Input Pins

#define Lamp1  12
#define Lamp2  6
#define Master 8
#define Lamp3  9
#define Lamp4  10
#define Lamp5  5

//Output Pins to control Triac Switching

#define Load1  23  //A5
#define Load2  22  //A4
#define Load3  21  //A3
#define Load4  20  //A2
#define Load5  19  //A1
#define Load6  18  //A0




class QTouch
{
  
  public:
  
  int i=0;
  QTouch();        //Constructor
  void gpioInit(void);
  byte readCapsense(void);
  byte readLoadstatus(void);
  void cap_setLoad(byte loadValue);
  void L1_ON(void);
  void L2_ON(void);
  void L3_ON(void);
  void L4_ON(void);
  void L5_ON(void);
  void Master_ON(void);
  
  void L1_OFF(void);
  void L2_OFF(void);
  void L3_OFF(void);
  void L4_OFF(void);
  void L5_OFF(void);
  void Master_OFF(void);
  
  
  
  private:
  
  byte curr_status, prev_status;
  
  unsigned int m_loadValue;
  unsigned int prev_loadValue;
  
  
};

#endif


