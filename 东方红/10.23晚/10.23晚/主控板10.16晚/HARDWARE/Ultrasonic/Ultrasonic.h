#ifndef __ULTRA_H
#define __ULTRA_H

#include "stm32f4xx.h"

#define filter_nub	10
#define Limit(x, min, max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )//�޷�
#define CAP_Overflow 	0XFFFFFFFF
/* ���ź궨�� */
/* Left1�궨�� PE15:trig1  PA0:echo1	TIM5 */
#define Left1_trig_PIN                   	GPIO_Pin_12                
#define Left1_trig_GPIO_PORT             	GPIOE                      
#define Left1_trig_GPIO_CLK              	RCC_AHB1Periph_GPIOE	

#define Left2_trig_PIN                   	GPIO_Pin_13                
#define Left2_trig_GPIO_PORT             	GPIOE                      
#define Left2_trig_GPIO_CLK             	RCC_AHB1Periph_GPIOE

#define Right1_trig_PIN                  	GPIO_Pin_14                 
#define Right1_trig_GPIO_PORT            	GPIOE                    
#define Right1_trig_GPIO_CLK             	RCC_AHB1Periph_GPIOE	

#define Right2_trig_PIN                  	GPIO_Pin_15               
#define Right2_trig_GPIO_PORT            	GPIOE                     
#define Right2_trig_GPIO_CLK             	RCC_AHB1Periph_GPIOE	

#define Front1_trig_PIN                   	GPIO_Pin_4               
#define Front1_trig_GPIO_PORT             	GPIOC                   
#define Front1_trig_GPIO_CLK              	RCC_AHB1Periph_GPIOC

#define Front2_trig_PIN                    	GPIO_Pin_5             
#define Front2_trig_GPIO_PORT              	GPIOC                    
#define Front2_trig_GPIO_CLK               	RCC_AHB1Periph_GPIOC

/******************************************************************************/
#define Left1_echo_PIN                   	GPIO_Pin_6                
#define Left1_echo_GPIO_PORT             	GPIOA                      
#define Left1_echo_GPIO_CLK              	RCC_AHB1Periph_GPIOA
#define Left1_echo_GPIO_PinSource		    GPIO_PinSource6

#define Left2_echo_PIN                   	GPIO_Pin_7        
#define Left2_echo_GPIO_PORT             	GPIOA                     
#define Left2_echo_GPIO_CLK              	RCC_AHB1Periph_GPIOA
#define Left2_echo_GPIO_PinSource			GPIO_PinSource7

#define Right1_echo_PIN                  	GPIO_Pin_8                
#define Right1_echo_GPIO_PORT            	GPIOC                     
#define Right1_echo_GPIO_CLK             	RCC_AHB1Periph_GPIOC
#define Right1_echo_GPIO_PinSource		    GPIO_PinSource8

#define Right2_echo_PIN                  	GPIO_Pin_9                
#define Right2_echo_GPIO_PORT            	GPIOC                  
#define Right2_echo_GPIO_CLK             	RCC_AHB1Periph_GPIOC
#define Right2_echo_GPIO_PinSource			GPIO_PinSource9

#define Front1_echo_PIN                  	GPIO_Pin_5               
#define Front1_echo_GPIO_PORT            	GPIOE                  
#define Front1_echo_GPIO_CLK             	RCC_AHB1Periph_GPIOE
#define Front1_echo_GPIO_PinSource			GPIO_PinSource5

#define Front2_echo_PIN                  	GPIO_Pin_6                 
#define Front2_echo_GPIO_PORT            	GPIOE                    
#define Front2_echo_GPIO_CLK             	RCC_AHB1Periph_GPIOE
#define Front2_echo_GPIO_PinSource			GPIO_PinSource6

#define 		TRIG_L1 		{PEout(12)=0;Delay_ULTRA(40);PEout(12)=1;}
#define 		TRIG_L2 		{PEout(13)=0;Delay_ULTRA(40);PEout(13)=1;}
#define 		TRIG_R1 		{PEout(14)=0;Delay_ULTRA(40);PEout(14)=1;}
#define 		TRIG_R2 		{PEout(15)=0;Delay_ULTRA(40);PEout(15)=1;}
#define 		TRIG_F1 		{PCout(4)=0;Delay_ULTRA(40);PCout(4)=1;}
#define 		TRIG_F2 		{PCout(5)=0;Delay_ULTRA(40);PCout(5)=1;}

#define 	TRIG_1	TRIG_L1 		
#define 	TRIG_2	TRIG_L2 		
#define 	TRIG_3	TRIG_R1 		
#define 	TRIG_4	TRIG_R2 		
#define 	TRIG_5	TRIG_F1 		
#define 	TRIG_6	TRIG_F2 		

#define	Ultra_F_L UL_DIS_F.L1
#define	Ultra_B_L UL_DIS_F.L2
#define	Ultra_M_L UL_DIS_F.F1
#define	Ultra_M_R UL_DIS_F.F2
#define	Ultra_F_R UL_DIS_F.R1
#define	Ultra_B_R UL_DIS_F.R2

typedef struct
{
	u8  CAPTURE_STA;                 //ͨ�����벶���־������λ�������־����6λ�������־		
	u16 CAPTURE_UPVAL;               //ͨ����������
	u16 CAPTURE_DOWNVAL;             //ͨ���½�����
	u32	CAPTURE_VAL;	     					 //ͨ�����벶��ֵ
	
	float DIS; 											 //����������ֵ
	float Last_DIS;
	float max;
	float min;
	u8  CAPTURE_SELECT;                        
} Ultra_cap_t;



typedef struct
{
	unsigned char 	Complete;
	unsigned char   Count;
	float   				Cache;	        //�����м仺��ֵ
	float 		 			Last_Data;	    //��һ�β���ֵ
	float  					Data_His[15];		//������ʷֵ
}UltrasonicFilter_Struct;

//�˲�֮��������ֵ
typedef struct 
{
	u16   L1;
	u16   L2;
	u16   R1;
	u16   R2;
	u16   F1;
	u16   F2;
}UltrasonicDis;


extern Ultra_cap_t ultra_L1;
extern Ultra_cap_t ultra_L2;
extern Ultra_cap_t ultra_R1;
extern Ultra_cap_t ultra_R2;
extern Ultra_cap_t ultra_F1;
extern Ultra_cap_t ultra_F2;


extern UltrasonicDis UL_DIS_F;


void Ultrasonic_Init(void);
void Ultra_TIM3_Init(u32 arr, u16 psc);
void Ultra_TIM9_Init(u16 arr, u16 psc);
void Delay_ULTRA(unsigned char n);
void Ultrasonic_Get_Distance(void);
void Ultrasonic_Filter(UltrasonicFilter_Struct *filterStruct,float newDatas,unsigned char FilterNum,u16 *Out);
																				//�����������˲�������ǿ�;�ֵ�˲���
#endif

