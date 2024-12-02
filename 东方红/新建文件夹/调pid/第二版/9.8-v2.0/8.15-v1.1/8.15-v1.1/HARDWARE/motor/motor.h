#ifndef __MOTOR_H
#define __MOTOR_H
#include "stm32f4xx.h"

#include "encoder.h"

#define PWMA TIM1->CCR1
#define PWMB TIM1->CCR2
#define PWMC TIM1->CCR3
#define PWMD TIM1->CCR4

#define AIN1 PEout(8)
#define AIN2 PEout(9)
#define BIN1 PAout(12)
#define BIN2 PCout(12)
#define CIN1 PBout(11)
#define CIN2 PBout(10)
#define DIN1 PDout(10)
#define DIN2 PDout(11)

extern int PWM_speedA,PWM_speedB,PWM_speedC,PWM_speedD;
void Motor_Init(void);
void TIM1_Motor_PWM_Init(u16 arr, u16 psc);
void Motor_TB_Set(int speedA,int speedB,int speedC, int speedD);
int  myabs(int x);				//¾ø¶ÔÖµº¯Êý
#endif

