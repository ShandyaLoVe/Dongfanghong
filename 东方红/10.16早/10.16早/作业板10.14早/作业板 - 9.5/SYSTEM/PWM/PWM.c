#include "PWM.h"                  // Device header

void PWM_init(void)
{			
			
		GPIO_InitTypeDef GPIO_InitStruct;
		TIM_OCInitTypeDef TIM_OCInitStruct;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
		TIM_InternalClockConfig(TIM1);



		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
		GPIO_Init(GPIOA,&GPIO_InitStruct);
		
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_TIM1);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_TIM1);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_TIM1);
		
		TIM_TimeBaseInitStruct.TIM_Prescaler = 14;
		TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStruct.TIM_Period =999;
		TIM_TimeBaseInitStruct.TIM_CounterMode =TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
		
		TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStruct.TIM_Pulse = 500;
		TIM_OC1Init(TIM1, &TIM_OCInitStruct);
		TIM_OC2Init(TIM1, &TIM_OCInitStruct);
		TIM_OC3Init(TIM1, &TIM_OCInitStruct);
		TIM_OC4Init(TIM1, &TIM_OCInitStruct);
		
		TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); //????????
		TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPE ??
		TIM_CtrlPWMOutputs(TIM1,ENABLE);
		TIM_Cmd(TIM1, ENABLE); 
		






//  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

//  TIM_OCInitTypeDef TIM_OCInitStructure;

  // ??TIM1??
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

//  // TIM1??
//  TIM_TimeBaseStructure.TIM_Period = 999; // ????,??????
//  TIM_TimeBaseStructure.TIM_Prescaler = 0;
//  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

//  // PWM????
//  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//  TIM_OCInitStructure.TIM_Pulse = 500; // ?????,??????
//  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

//  // ??TIM1???
//  TIM_CtrlPWMOutputs(TIM1, ENABLE);

//  // ??TIM1
//  TIM_Cmd(TIM1, ENABLE);



	

}
