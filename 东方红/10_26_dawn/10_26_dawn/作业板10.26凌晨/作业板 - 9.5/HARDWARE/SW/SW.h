#ifndef __SW_H
#define	__SW_H

#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"

#define	KEY_Port	GPIOC

#define KEY1_Pin	GPIO_Pin_10
#define KEY2_Pin	GPIO_Pin_11


#define KEY1 		GPIO_ReadInputDataBit(KEY_Port,KEY1_Pin) 
#define KEY2 		GPIO_ReadInputDataBit(KEY_Port,KEY2_Pin)	


#define KEY1_PRES 	1
#define KEY2_PRES	  2


//Ïà¹Øº¯Êý
void key_init(void);
u8   key_scan(u8 mode);



#endif /* __KEY_H */

