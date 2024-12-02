#include "stm32f4xx.h"
#include "System_operation.h"
#include "Move_Command.h"


extern u8 start_flag;


void TIM7_IRQHandler()//1ms一次中断
{
	if(TIM_GetITStatus(TIM7, TIM_IT_Update) == SET) //溢出中断
	{
		time_5ms++;
        time_7ms++;
		time_10ms++;
		time_20ms++;
		time_50ms++;
		time_100ms++;
        

	}
    
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);			//清除中断标志位
}


void System_TIM7_Init()//1ms
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);

	TIM_TimeBaseStructure.TIM_Prescaler=83;
	TIM_TimeBaseStructure.TIM_Period=999;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM7, ENABLE); //使能 TIM7
}






