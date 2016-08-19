#ifndef  QTouch_h
#define  QTouch_h

#include <Arduino.h>
#include <TAH.h>
#include "BLE.h"


// Capsence Input Pins

#define Lamp1      15    
#define Lamp2      16    
#define Lamp3      4     //A6 
#define Socket     12  
#define Fan_Control 9 
#define Up          6
#define Down        8
//Output Pins to control Triac Switching

#define Load1   10   //Dimmer1 
#define Load2   5    //Dimmer2
#define Load3   13   //Dimmer3
#define Load4   19   //A1- Socket pin
#define Level1  23   //A5 D23
#define Level2  22   //A4 D22
#define Level3  21   //A3 D21
#define Level4  20   //A2 D20



class QTouch
{
  
  public:
  
  int i;
  QTouch();        //Constructor
  void gpioInit(void);
  byte readCapsense(void);
  byte readLoadstatus(void);
  void cap_setLoad(byte loadValue);
  void L1_ON(void);
  void L2_ON(void);
  void L3_ON(void);
  void Socket_ON(void);
  void FAN_ON(void);
  void Level2_ON(void);
  void Level3_ON(void);
  void Level4_ON(void);
  void Master_ON(void);
  
  void L1_OFF(void);
  void L2_OFF(void);
  void L3_OFF(void);
  void Socket_OFF(void);
  void FAN_OFF(void);
  void Level2_OFF(void);
  void Level3_OFF(void);
  void Level4_OFF(void);
  void Master_OFF(void);
  
  
  
  private:
  
  byte curr_status, prev_status;
  
  unsigned int m_loadValue;
  unsigned int prev_loadValue;
  
  
};

#endif


