#include "laser.h"
void laser_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(GPIOD,&GPIO_InitStruct);
}

void laser_close()
{
	GPIO_WriteBit(GPIOD,GPIO_Pin_7,Bit_RESET);
}
void laser_open()
{
	GPIO_WriteBit(GPIOD,GPIO_Pin_7,Bit_SET);
}
