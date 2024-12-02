#include "led.h"
#include "delay.h"
/****
	*****************************************************************************
	* @file    led.c
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
	
/****
	* @brief  LED��ʼ�� 
	* @param  ��
	* @note   ��ʼ����ʱ��ѵƶ�����
	* @retval ��
	* @bug
  * @todo	
	*/
void LED_Init(void)
{		
		
	GPIO_InitTypeDef GPIO_InitStructure;													    //����һ��GPIO_InitTypeDef���͵Ľṹ��
	RCC_AHB1PeriphClockCmd ( LED1_GPIO_CLK|LED2_GPIO_CLK|LED3_GPIO_CLK,ENABLE); 	//����LED��ص�GPIO����ʱ��

	GPIO_InitStructure.GPIO_Pin = LED1_PIN|LED2_PIN|LED3_PIN;									//ѡ��Ҫ���Ƶ�GPIO����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   											//��������ģʽΪ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;												//�������ŵ��������Ϊ�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;												//��������Ϊ��״̬
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 											//������������Ϊ50MHz  

	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);											    //���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO
	GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);
	GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);
}
void BEEP_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;								//����һ��GPIO_InitTypeDef���͵Ľṹ��
	RCC_AHB1PeriphClockCmd ( BEEP_GPIO_CLK, ENABLE);					//����LED��ص�GPIO����ʱ�� 
	
	GPIO_InitStructure.GPIO_Pin = BEEP_PIN;								//ѡ��Ҫ���Ƶ�GPIO����		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  						//��������ģʽΪ���ģʽ 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;						//�������ŵ��������Ϊ�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;					//��������Ϊ��	  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 					//������������Ϊ2MHz  
	
	GPIO_Init(BEEP_GPIO_PORT, &GPIO_InitStructure);						//���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO 	
}

void BIBI(void)
{
	BEEP_ON;
	delay_ms(150);
	BEEP_OFF;
	delay_ms(150);
	BEEP_ON;
	delay_ms(150);
	BEEP_OFF;
}

void tx_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;								//����һ��GPIO_InitTypeDef���͵Ľṹ��
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOC, ENABLE);					//����LED��ص�GPIO����ʱ�� 
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10| GPIO_Pin_11;		    //PC10--tx4,PC11--rx4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  						//��������ģʽΪ���ģʽ 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;						//�������ŵ��������Ϊ�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;					   //��������Ϊ����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 					//������������Ϊ2MHz  
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);						//���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO 
}

void rx_init(void)//����3
{
    GPIO_InitTypeDef GPIO_InitStructure;								//����һ��GPIO_InitTypeDef���͵Ľṹ��
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOD, ENABLE);				//����LED��ص�GPIO����ʱ�� 
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8| GPIO_Pin_9;				//8--tx3,9--rx3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  						//��������ģʽΪ���ģʽ 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;					   //��������Ϊ����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 					//������������Ϊ2MHz  
	
	GPIO_Init(GPIOD, &GPIO_InitStructure);						//���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO 
}
