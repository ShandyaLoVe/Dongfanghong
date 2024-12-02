/****
	*****************************************************************************
	* @file    bsp_key.c
	* @author  huang 
	* @version V1.0
	* @date    2020-10-13
	* @brief   ����DMA�ĳ�ʼ������λ����Ӧ��
	* @license Copyright 2020 YRCK. All rights reserved. 

	*****************************************************************************
	* @note		������ʼ����������ɨ��
				USART1_RX---PC10
				USART1_TX---PC11	
	* @bug
	* @todo	
	* @details 
	*
	*****************************************************************************
	*/
#include "key.h" 
#include "delay.h"
#include "sys.h"

/****
	*****************************************************************************
										        CONSTANTS & MACROS
	*****************************************************************************
	* @brief  �������ź궨��
	*/
#define KEY1_PIN                  GPIO_Pin_9                
#define KEY1_GPIO_PORT            GPIOB                     
#define KEY1_GPIO_CLK             RCC_AHB1Periph_GPIOB

#define KEY2_PIN                  GPIO_Pin_1                
#define KEY2_GPIO_PORT            GPIOE                     
#define KEY2_GPIO_CLK             RCC_AHB1Periph_GPIOE

#define KEY3_PIN                  GPIO_Pin_8
#define KEY3_GPIO_PORT            GPIOB
#define KEY3_GPIO_CLK             RCC_AHB1Periph_GPIOB

#define KEY4_PIN                  GPIO_Pin_0
#define KEY4_GPIO_PORT            GPIOE
#define KEY4_GPIO_CLK             RCC_AHB1Periph_GPIOE

/*******************************************************/


/**
  * @brief  ���ð����õ���I/O��
  * @param  ��
  * @retval ��
  */
	
void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK|KEY3_GPIO_CLK|KEY4_GPIO_CLK,ENABLE);//��������GPIO�ڵ�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = KEY1_PIN;							//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;					//��������Ϊ����ģʽ	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;					//�������Ų�����Ҳ������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 				//������������Ϊ2MHz 
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);   				//ʹ������Ľṹ���ʼ������
	
	GPIO_InitStructure.GPIO_Pin = KEY2_PIN;							//ѡ�񰴼�������
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);   				//ʹ������Ľṹ���ʼ������
	
	GPIO_InitStructure.GPIO_Pin = KEY3_PIN;							//ѡ�񰴼�������
	GPIO_Init(KEY3_GPIO_PORT, &GPIO_InitStructure);   				//ʹ������Ľṹ���ʼ������
	
	GPIO_InitStructure.GPIO_Pin = KEY4_PIN;							//ѡ�񰴼�������
	GPIO_Init(KEY4_GPIO_PORT, &GPIO_InitStructure);   				//ʹ������Ľṹ���ʼ������
}

/****
	* @brief	��ʼ������ɨ�躯��
	* @param	mode��0,��֧��������;1,֧��������;
	* @retval	������Ӧ�����ı��
	* @bug
	* @todo	
	*	@todo	ע��˺�������Ӧ���ȼ�,KEY1>KEY2>KEY3
	*/
u8 Key_Scan(void)
{  
	 static u8 key_up=1;
	 if(key_up&&((KEY1==0)||(KEY2==0)||(KEY3==0)||(KEY4==0)))
	 {
		 delay_ms(10);
		 key_up=0;
		 if(KEY1==0)      return KEY1_PRES;
		 else if(KEY2==0) return KEY2_PRES;
		 else if(KEY3==0) return KEY3_PRES; 
		 else if(KEY4==0) return KEY4_PRES; 
	 }
   else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)key_up=1;
	return 0;	
}



/*********************************************END OF FILE**********************/
