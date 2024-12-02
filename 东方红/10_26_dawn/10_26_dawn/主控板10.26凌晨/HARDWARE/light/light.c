#include "light.h"


void Light_Init(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;		
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOE, ENABLE); 

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_5|GPIO_Pin_6;			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;			
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 		
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

