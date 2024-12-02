#ifndef __MOTOR_H
#define __MOTOR_H
#include "stm32f4xx.h"

#include "sys.h"

#define PWMA TIM2->CCR3
#define PWMB TIM2->CCR4
#define PWMC TIM1->CCR3
#define PWMD TIM1->CCR4

#define AIN1 PDout(1)
#define AIN2 PDout(2)
#define BIN1 PBout(8)
#define BIN2 PCout(12)
#define CIN1 PBout(10)
#define CIN2 PDout(10)
#define DIN1 PDout(11)
#define DIN2 PAout(12)

extern int PWM_speedA,PWM_speedB,PWM_speedC,PWM_speedD;
void Motor_Init(void);
void TIM1_Motor_PWM_Init(u16 arr, u16 psc);
void Motor_TB_Set(int speedA,int speedB,int speedC, int speedD);
int  myabs(int x);				//¾ø¶ÔÖµº¯Êý
#endif
