/****
	*****************************************************************************
	* @file    usartx_dma.c
	* @author  ������
	* @version V1.0
	* @date    2021-7-7
	* @brief   ����DMA�ĳ�ʼ������λ����Ӧ��
	* @license Copyright 2021. All rights reserved. 

	*****************************************************************************
	* @note		����DMA�ĳ�ʼ�� ��λ����Ӧ�� �жϱ�־λ��Ҫ�����޸� û�н��к궨��
				����1�ĳ�ʼ�� 
				USART1_RX---PC10
				USART1_TX---PC11	
	* @bug
	* @todo	
	* @details 
	*
	*****************************************************************************
	*/
#include "openmv.h"
#include "sys.h"
#include "string.h"
#include "stdio.h"
u16 work_state=0;
/****
	*****************************************************************************
										        CONSTANTS & MACROS
	*****************************************************************************
	* @brief  ������ DMA�� GPIO��
	*/
#define USARTx                          	USART1
#define USARTx_CLK                      	RCC_APB2Periph_USART1
#define USARTx_CLK_INIT                 	RCC_APB2PeriphClockCmd
#define USARTx_IRQn                     	USART1_IRQn
#define USARTx_IRQHandler               	USART1_IRQHandler

#define USARTx_TX_PIN                   	GPIO_Pin_6          
#define USARTx_TX_GPIO_PORT             	GPIOB                     
#define USARTx_TX_GPIO_CLK              	RCC_AHB1Periph_GPIOB
#define USARTx_TX_SOURCE                	GPIO_PinSource6
#define USARTx_TX_AF                    	GPIO_AF_USART1

#define USARTx_RX_PIN                   	GPIO_Pin_7       
#define USARTx_RX_GPIO_PORT             	GPIOB                   
#define USARTx_RX_GPIO_CLK              	RCC_AHB1Periph_GPIOB
#define USARTx_RX_SOURCE                	GPIO_PinSource7
#define USARTx_RX_AF                    	GPIO_AF_USART1

#define USARTx_DMA                      	DMA2
#define USARTx_DMAx_CLK                 	RCC_AHB1Periph_DMA2
#define DMACLEAR                        	DMA2->HIFCR = DMA_Stream7_IT_MASK;				//TX	



#define USART_RX_DMA_Stream 							DMA2_Stream2
#define USART_RX_DMA_Channel   						DMA_Channel_4									
#define USART_RX_DMA_PeripheralBaseAddr 	(uint32_t) (&(USARTx->DR))

#define USART_TX_DMA_Stream 							DMA2_Stream7
#define USART_TX_DMA_Channel   						DMA_Channel_4
#define USART_TX_DMA_IRQn									DMA2_Stream7_IRQn
#define USART_TX_DMA_IRQHandler						DMA2_Stream7_IRQHandler
#define USART_TX_DMA_PeripheralBaseAddr 	(uint32_t) (&(USARTx->DR))

u8 rec_data_u1[U1_DATA_LEN];      													//�������ݵ�ַ
u8 send_data_u1[U1_DATA_LEN];     													//�������ݵ�ַ
int tree_colour = 0;
/****
	* @brief  ���ڵĳ�ʼ��
	* @param  ��
	* @note   ��
	* @retval ��
	* @bug
    * @todo	
	*/
void USART1_Init(int Baud)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6,GPIO_AF_USART1);

	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl =  USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStruct);
	
	USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=  1;
	NVIC_Init(&NVIC_InitStruct);								//��ʼ��
}




/****
	* @brief  ���ڽ����ж�
	* @param  ��
	* @note   Uart1_Rec_Len ���иĶ� ���ڼ����Ǽ�
	* @retval ��
	* @bug
  * @todo	
	*/




void USART1_IRQHandler(void)                	//����1�жϷ������
{
	signed char i;
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE) !=RESET)
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		i = USART_ReceiveData(USART1);
//		OLED_Show3FNum(60,0,i,3,3,12); //��ʾ���� 
		CopeData(i);
//		OLED_Refresh_Gram();		
	}

} 

void CopeData(unsigned char ucData)
{

	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	
	ucRxBuffer[ucRxCnt++]=ucData;	
	if (ucRxBuffer[0] != 0x09) 
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<2) {return;}
	else
	{
		tree_colour = ucRxBuffer[1];
 
	}

	ucRxCnt=0;
	
}















#define BYTE0(dwTemp)       (*(char *)(&dwTemp))      
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

