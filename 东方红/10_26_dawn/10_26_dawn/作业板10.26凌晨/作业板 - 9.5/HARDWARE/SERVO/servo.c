#include "servo.h"                  // Device header
void servo_init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;
		TIM_OCInitTypeDef TIM_OCInitStruct;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);



		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
		GPIO_Init(GPIOD,&GPIO_InitStruct);
		
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);

		
		TIM_TimeBaseInitStruct.TIM_Prescaler = 83;
		TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStruct.TIM_Period =20000-1;
		TIM_TimeBaseInitStruct.TIM_CounterMode =TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
		
		TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStruct.TIM_Pulse = 500;
		TIM_OC1Init(TIM4, &TIM_OCInitStruct);
		TIM_OC2Init(TIM4, &TIM_OCInitStruct);

  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPEÊ¹ÄÜ
		TIM_Cmd(TIM4, ENABLE); 
		
}
void sevo1_angle(float x)
{
	TIM_SetCompare1(TIM4,x*2000/270.0+500);
	TIM_SetCompare2(TIM4,x*2000/270.0+500);
}

