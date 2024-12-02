#ifndef __LIGHT_H
#define	__LIGHT_H
#include "stm32f4xx.h"

void Light_Init(void);

#define	state_light GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)
#define	state_light2 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)



#endif
