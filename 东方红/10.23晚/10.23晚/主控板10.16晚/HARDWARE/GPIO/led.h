#ifndef __LED_H
#define	__LED_H
/****
	*****************************************************************************
	* @file    bsp_led.c
	* @author  ������
	* @version V1.0
	* @date    2021-7-6
	* @brief   LED����
	* @license Copyright 2021. All rights reserved. 

	*****************************************************************************
	* @note  	 	��
	* @bug
	* @todo	
	* @details 
	*
	*****************************************************************************
	*/
#include "stm32f4xx.h"

/****
	*****************************************************************************
										        CONSTANTS & MACROS
	*****************************************************************************
	* @brief  LED���ź궨��
	*/
#define LED1_PIN                  GPIO_Pin_2                 
#define LED1_GPIO_PORT            GPIOE                      
#define LED1_GPIO_CLK             RCC_AHB1Periph_GPIOE


#define LED2_PIN                  GPIO_Pin_3                
#define LED2_GPIO_PORT            GPIOE                     
#define LED2_GPIO_CLK             RCC_AHB1Periph_GPIOE


#define LED3_PIN                  GPIO_Pin_4
#define LED3_GPIO_PORT            GPIOE
#define LED3_GPIO_CLK             RCC_AHB1Periph_GPIOE

//#define LED4_PIN                  GPIO_Pin_10
//#define LED4_GPIO_PORT            GPIOC
//#define LED4_GPIO_CLK             RCC_AHB1Periph_GPIOC
/****
	*****************************************************************************
										        CONSTANTS & MACROS
	*****************************************************************************
	* @brief  ֱ�Ӳ����Ĵ����ķ�������IO 
	*/

#define	digitalHi(p,i)			 			{p->BSRRL=i;}									//����Ϊ�ߵ�ƽ
#define digitalLo(p,i)			 			{p->BSRRH=i;}									//����͵�ƽ
#define digitalToggle(p,i)	 	 			{p->ODR ^=i;}									//�����ת״̬

/****
	*****************************************************************************
										        CONSTANTS & MACROS
	*****************************************************************************
	* @brief   �������IO�ĺ�
	*/

#define LED1_TOGGLE			digitalToggle(LED1_GPIO_PORT,LED1_PIN)		//��˸
#define LED1_ON			 		digitalHi(LED1_GPIO_PORT,LED1_PIN)
#define LED1_OFF				digitalLo(LED1_GPIO_PORT,LED1_PIN)

#define LED2_TOGGLE			digitalToggle(LED2_GPIO_PORT,LED2_PIN)
#define LED2_ON			  	digitalHi(LED2_GPIO_PORT,LED2_PIN)
#define LED2_OFF				digitalLo(LED2_GPIO_PORT,LED2_PIN)

#define LED3_TOGGLE			digitalToggle(LED3_GPIO_PORT,LED3_PIN)
#define LED3_ON			  	digitalHi(LED3_GPIO_PORT,LED3_PIN)
#define LED3_OFF				digitalLo(LED3_GPIO_PORT,LED3_PIN) 

#define LED4_TOGGLE			digitalToggle(LED4_GPIO_PORT,LED4_PIN)
#define LED4_ON			  	digitalHi(LED4_GPIO_PORT,LED4_PIN)
#define LED4_OFF				digitalLo(LED4_GPIO_PORT,LED4_PIN) 


void LED_Init(void);
void tx_init(void);
void rx_init(void);

/****
	*****************************************************************************
										        CONSTANTS & MACROS
	*****************************************************************************
	* @brief  
	*/
#define BEEP_PIN                  GPIO_Pin_7                
#define BEEP_GPIO_PORT            GPIOD                     
#define BEEP_GPIO_CLK             RCC_AHB1Periph_GPIOD

/****
	*****************************************************************************
										        CONSTANTS & MACROS
	*****************************************************************************
	* @brief  ֱ�Ӳ����Ĵ����ķ���
	*/
#define	digitalHi(p,i)				{p->BSRRL=i;}		//����Ϊ�ߵ�ƽ
#define digitalLo(p,i)			 	{p->BSRRH=i;}		//����͵�ƽ
#define digitalToggle(p,i)	 		{p->ODR ^=i;}		//�����ת״̬

/****
	*****************************************************************************
										        CONSTANTS & MACROS
	*****************************************************************************
	* @brief  ������״̬
	*/
#define BEEP_TOGGLE			digitalToggle(BEEP_GPIO_PORT,BEEP_PIN)
#define BEEP_ON			  	digitalHi(BEEP_GPIO_PORT,BEEP_PIN)
#define BEEP_OFF			digitalLo(BEEP_GPIO_PORT,BEEP_PIN)


void BEEP_Init(void);
void BIBI(void);
#endif /* __LED_H */
