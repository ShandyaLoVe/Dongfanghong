#include "led.h"
void led_init()
{
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
//	GPIO_InitTypeDef GPIO_InitStruct;
//	
//	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_1;
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
//	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//	
//	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;							//选择按键的引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;					//设置引脚为输入模式	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;					//设置引脚不上拉也不下拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 				//设置引脚速率为2MHz 
	
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	//GPIO_SetBits(GPIOA,8);
}
