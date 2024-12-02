#ifndef __KEY_H
#define	__KEY_H

#include "stm32f4xx.h"


#define KEY1 		PBin(9)   	                                                                             	//PB13
#define KEY2 		PEin(1)		                                                                         		//PG2
#define KEY3  	    PBin(8)		                                                                         	//PA12
#define KEY4		PEin(0)

#define KEY1_PRES                 1
#define KEY2_PRES                 2
#define KEY3_PRES                 3
#define KEY4_PRES                 4

extern int key;

void Key_Init(void);
u8   Key_Scan(void);



#endif /* __KEY_H */

