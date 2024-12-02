#include "stm32f4xx.h"
#include "steer.h"

int Total_Degree=0;

void TIM4_Steer_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);//PD12-PD15,TIM4
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 
  GPIO_Init(GPIOD,&GPIO_InitStructure); 
	
	TIM_TimeBaseStructure.TIM_Period=19999;
  TIM_TimeBaseStructure.TIM_Prescaler=83;
  TIM_TimeBaseStructure.TIM_ClockDivision=0;
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //PWM 调制模式 1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性低
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); 
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); 
	
  TIM_ARRPreloadConfig(TIM4,ENABLE);
	
	TIM4->CCR1 = 0;
	TIM4->CCR2 = 0;
	TIM4->CCR3 = 0;
	TIM4->CCR4 = 0;
	
  TIM_Cmd(TIM4, ENABLE);
}

void Steer1_degree(float degree)
{
	if(degree<0)degree=0;
	if(degree>270)degree=270;
	
	degree=degree*7.5+500;
	TIM4->CCR1 = (int)degree;
}

void Steer2_degree(float degree)
{
	if(degree<0)degree=0;
	if(degree>270)degree=270;
	
	degree=degree*7.5+500;
	TIM4->CCR2 = (int)degree;
}

void Steer3_degree(float degree)
{
	if(degree<0)degree=0;
	if(degree>270)degree=270;
	
	degree=degree*7.5+500;
	TIM4->CCR3 = (int)degree;
}

void Steer4_degree(float degree)
{
	if(degree<0)degree=0;
	if(degree>270)degree=270;
	
	degree=degree*7.5+500;
	TIM4->CCR4 = (int)degree;
}

//void Steer_Control_F_AB(float Goal_Degree,float Correct_Degree)
//{
//	Steer1_degree(Goal_Degree+5);
//	Steer2_degree(180-Goal_Degree+2);
//	Steer3_degree(180-Goal_Degree+Correct_Degree+5);
//	Steer4_degree(Goal_Degree+Correct_Degree+3);
//}

//void Steer_Control_F_CD(float Goal_Degree,float Correct_Degree)
//{
//	Steer1_degree(Goal_Degree+Correct_Degree+5);
//	Steer2_degree(180-Goal_Degree+Correct_Degree+2);
//	Steer3_degree(180-Goal_Degree+5);
//	Steer4_degree(Goal_Degree+3);
//}

void Steer_Control_F_ABCD(float Goal_Degree,float Correct_Degree,float Yaw_Degree)//进垄方向
{
	Steer1_degree(Goal_Degree+Yaw_Degree+Correct_Degree-35);
	Steer2_degree(Goal_Degree+Yaw_Degree+Correct_Degree+45);
	Steer3_degree(Goal_Degree+Correct_Degree+30);
	Steer4_degree(Goal_Degree+Correct_Degree-35);
}

void Steer_Control_B_ABCD(float Goal_Degree,float Correct_Degree,float Yaw_Degree)//换垄方向
{
	Steer1_degree(Goal_Degree+Correct_Degree-35);
	Steer2_degree(Goal_Degree+Correct_Degree+45);
	Steer3_degree(Goal_Degree+Yaw_Degree+Correct_Degree+30);
	Steer4_degree(Goal_Degree+Yaw_Degree+Correct_Degree-35);
}


void Steer_Control_B(float Goal_Degree,float Correct_Degree)//跨垄方向
{
	Steer1_degree(Goal_Degree+Correct_Degree+105);
	Steer2_degree(Goal_Degree+Correct_Degree+8);
	Steer3_degree(Goal_Degree+Correct_Degree-5);
	Steer4_degree(Goal_Degree+Correct_Degree+105);
}


void TIM8_Servo_PWM_Init(u32 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef 	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef	TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM8);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr-1;
	TIM_TimeBaseStructure.TIM_Prescaler = psc-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
	
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);
	TIM_CtrlPWMOutputs(TIM8,ENABLE); 
	
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM8, ENABLE);
	TIM_Cmd(TIM8, ENABLE);
	
	TIM_CtrlPWMOutputs(TIM8,ENABLE);			//高级定时器(TIM1、TIM8)独有
}
