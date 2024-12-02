#ifndef __TIMER_H
#define __TIMER_H

#include "sys.h"
void Timer_Init(void);
void System_TIM7_Init(void);

extern u8 time_5ms;
extern u8 time_7ms;
extern u8 time_10ms;
extern u8 time_20ms;
extern u8 time_50ms;
extern u8 time_100ms;


extern unsigned int n;

#endif
