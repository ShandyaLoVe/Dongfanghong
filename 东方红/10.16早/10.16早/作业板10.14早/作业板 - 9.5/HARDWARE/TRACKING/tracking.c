#include "tracking.h"

void tracking_init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOB时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
}

uint8_t tracking_read()
{
	uint8_t ret = 0;
	uint8_t i;

	for (i = 0; i < 8; ++i) 
	{
		
		GPIO_ResetBits(GPIOB, GPIO_Pin_1);
		delay_us(5); 

		ret |= GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) << i;
		GPIO_SetBits(GPIOB,GPIO_Pin_1);

		delay_us(5);
		
	}
	
	
	return ret;
}

int Get_err(int Va)
{ 
	int L,R,i;
	L=8;
		for(i=0 ; i<7 ; i++)
		{
		  if(((Va & 1 << (i+1)) >> (i+1)) - ((Va & 1 << i) >> i) == 1)
			{
			   L=i+1;
				break;		
			}			
		}
	
		R=1;
		
		
		for(i=6 ; i>=0 ; i--)
		{
		  if(((Va & 1 << (i+1)) >> (i+1)) - ((Va & 1<<i) >> i) == -1)
			{ 
			   R=i+2;
				break;		//00001000
			}		
		   
		}
		
		
		
    return L+R-9;
}

//int car_err;
//		int L_PWM,R_PWM;
//		int Gro_z ;  /z角速度
//		car_err=int Get_err(xunji);    //放入循迹测量值，读出偏差值
//		L_PWM= car_err*kp + Gro_z*kd  + car_speed;
//		R_PWM=car_err*-kp + Gro_z*-kd + car_speed;	
