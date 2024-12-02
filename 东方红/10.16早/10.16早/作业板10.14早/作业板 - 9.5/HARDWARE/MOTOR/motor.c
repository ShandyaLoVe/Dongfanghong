#include "motor.h"
#include "sys.h"
int PWM_speedA=0,PWM_speedB=0,PWM_speedC=0,PWM_speedD=0;

/****
	* @brief  电机普通IO的初始化
	* @param  无
	* @note   
	* @retval 无
	* @bug
    * @todo	
	*/
void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_14;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_15;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
		

	
	TIM1_Motor_PWM_Init(10000,3 );
}

void TIM1_Motor_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef 	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef	TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_TIM2);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	
	
	/***********解决普通输出时的互补BUG************/
	TIM_OCInitStructure.TIM_OCNIdleState= TIM_OCNIdleState_Reset;    
	TIM_OCInitStructure.TIM_OutputNState= TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;	
	TIM_OCInitStructure.TIM_Pulse= 0;	
	

	TIM_OC3Init(TIM2, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM2, &TIM_OCInitStructure); 
	
	/************使能预装载寄存器****************/
//	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);	
//	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);   
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM2,ENABLE);                                                     //允许在定时器工作时向ARR的缓冲器中写入新值，以便在更新事件发生时载入覆盖以前的值
	
	//TIM_CtrlPWMOutputs(TIM2, ENABLE);                                                      /************************/
	TIM_Cmd(TIM2,ENABLE);
	
}
//A B C D
void Motor_TB_Set(int speedB,int speedD,int speedC, int speedA)    //在车上的标号是A(EA),C,B(EB),D，AC成为一对，BD成为一对//
{
	if(speedA>900)speedA=900;
	else if(speedA<-900)speedA=-900;
	
	if(speedB>900)speedB=900;
	else if(speedB<-900)speedB=-900;
	
	if(speedC>900)speedC=900;
	else if(speedC<-900)speedC=-900;
	
	if(speedD>900)speedD=900;
	else if(speedD<-900)speedD=-900;
	
	speedA>=0	?	((AIN1=1),(AIN2=0)) : ((AIN1=0),(AIN2=1));
	speedB>=0	?	((BIN1=1),(BIN2=0)) : ((BIN1=0),(BIN2=1));
	speedC>=0	?	((CIN1=0),(CIN2=1)) : ((CIN1=1),(CIN2=0));
	speedD>=0	?	((DIN1=0),(DIN2=1)) : ((DIN1=1),(DIN2=0));
	
	if(speedA==0) {AIN1=1;AIN2=1;}
	if(speedB==0) {BIN1=1;BIN2=1;}
	if(speedC==0) {CIN1=1;CIN2=1;}
	if(speedD==0) {DIN1=1;DIN2=1;}
	
	PWMA=myabs(speedA);
	PWMB=myabs(speedB);
	PWMC=myabs(speedC);
	PWMD=myabs(speedD);
	
}

int myabs(int x)
{
  int temp;
	if(x<0)  temp =-x;  
	else     temp = x;
	return   temp;
}
