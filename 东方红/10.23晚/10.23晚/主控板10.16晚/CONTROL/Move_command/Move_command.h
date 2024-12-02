#ifndef __MOVE_COMMAND_H
#define __MOVE_COMMAND_H

#include "stm32f4xx.h"
#include "main_data.h"
#include "delay.h"
#include "System_operation.h"

#include "key.h"
#include "led.h"

#include "Ultrasonic.h"
#include "motor.h"
#include "mike.h"
#include "steer.h"
#include "encoder.h"
#include "PID.h"
#include "pid_small.h"

#include "usart1_dma.h"
#include "usart2_dma.h"

#include "usart4_dma.h"


#include "Test.h"
#include "light.h"
#include "oled.h"




float my_abs(float x);
void Get_init_flag(void);
void Get_flag(void);
void start_1(int vx,int vy);
void start_2(int vx,int vy);
void start_3(int vx,int vy);
void first_1(int vx,int vy);
void first_2(int vx,int vy);
void first_3(int vx,int vy);

void tran_1(int vx,int vy);
void tran_2(int vx,int vy);
void tran_3(int vx,int vy);
void tran_4(int vx,int vy);
void tran_5(int vx,int vy);
void back(int vx,int vy);
void back_2(int vx,int vy);

void second_1(int vx,int vy);
void second_2(int vx,int vy);
void second_3(int vx,int vy);

void third_1(int vx,int vy);
void third_2(int vx,int vy);
void third_3(int vx,int vy);

void fourth_1(int vx,int vy);
void fourth_2(int vx,int vy);
void fourth_3(int vx,int vy);

void fifth_1(int vx,int vy);
void fifth_2(int vx,int vy);
void fifth_3(int vx,int vy);

void sixth_1(int vx,int vy);
void sixth_2(int vx,int vy);
void sixth_3(int vx,int vy);

void filter(int time);
void decrease_speed_1(int *vx,float k);
void decrease_speed_2(int *vx,float k);
#endif
