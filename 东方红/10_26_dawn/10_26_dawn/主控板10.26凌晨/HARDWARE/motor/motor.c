#include "motor.h"
#include "sys.h"
int PWM_speedA=0,PWM_speedB=0,PWM_speedC=0,PWM_speedD=0;

/****
	* @brief  �����ͨIO�ĳ�ʼ��
	* @param  ��
	* @note   
	* @retval ��
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
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
		
	GPIO_ResetBits(GPIOE,GPIO_Pin_8);GPIO_ResetBits(GPIOE,GPIO_Pin_9);GPIO_ResetBits(GPIOE,GPIO_Pin_14);
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);
	GPIO_ResetBits(GPIOB,GPIO_Pin_10);GPIO_ResetBits(GPIOB,GPIO_Pin_11);
	GPIO_ResetBits(GPIOD,GPIO_Pin_10);GPIO_ResetBits(GPIOD,GPIO_Pin_11);
	
	TIM1_Motor_PWM_Init(1000, 14);
}

void TIM1_Motor_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef 	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef	TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_TIM1);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	
	
	/***********�����ͨ���ʱ�Ļ���BUG************/
	TIM_OCInitStructure.TIM_OCNIdleState= TIM_OCNIdleState_Reset;    
	TIM_OCInitStructure.TIM_OutputNState= TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;	
	TIM_OCInitStructure.TIM_Pulse= 0;	
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
	TIM_OC2Init(TIM1, &TIM_OCInitStructure); 
	TIM_OC3Init(TIM1, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM1, &TIM_OCInitStructure); 
	
	/************ʹ��Ԥװ�ؼĴ���****************/
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);	
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);   
	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM1,ENABLE);                                                     //�����ڶ�ʱ������ʱ��ARR�Ļ�������д����ֵ���Ա��ڸ����¼�����ʱ���븲����ǰ��ֵ
	
	TIM_CtrlPWMOutputs(TIM1, ENABLE);                                                      /************************/
	TIM_Cmd(TIM1,ENABLE);
	
}
//A B C D
void Motor_TB_Set(int speedB,int speedC,int speedD, int speedA)    //�ڳ��ϵı����A(EA),C,B(EB),D��AC��Ϊһ�ԣ�BD��Ϊһ��//
{
	if(speedA>1000)speedA=1000;
	else if(speedA<-1000)speedA=-1000;
	
	if(speedB>1000)speedB=1000;
	else if(speedB<-1000)speedB=-1000;
	
	if(speedC>1000)speedC=1000;
	else if(speedC<-1000)speedC=-1000;
	
	if(speedD>1000)speedD=1000;
	else if(speedD<-1000)speedD=-1000;
	
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
