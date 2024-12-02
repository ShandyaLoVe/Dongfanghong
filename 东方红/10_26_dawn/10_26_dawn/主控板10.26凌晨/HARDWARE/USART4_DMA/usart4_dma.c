/****
	*****************************************************************************
	* @file    uartx_dma.c
	* @author  ������
	* @version V1.0
	* @date    2021-7-7
	* @brief   ����DMA�ĳ�ʼ������λ����Ӧ��
	* @license Copyright 2021. All rights reserved. 

	*****************************************************************************
	* @note		����DMA�ĳ�ʼ�� ��λ����Ӧ�� �жϱ�־λ��Ҫ�����޸� û�н��к궨��
				����4�ĳ�ʼ�� 
				UART4_RX---PC11
				UART4_TX---PC10
	* @bug
	* @todo	
	* @details 
	*
	*****************************************************************************
	*/
#include "usart4_dma.h"
#include "sys.h"
#include "string.h"
#include "stdio.h"
/****
	*****************************************************************************
										        CONSTANTS & MACROS
	*****************************************************************************
	* @brief  ������ DMA�� GPIO��
	*/
#define USARTx                          	UART4
#define USARTx_CLK                      	RCC_APB1Periph_UART4
#define USARTx_CLK_INIT                 	RCC_APB1PeriphClockCmd
#define USARTx_IRQn                     	UART4_IRQn
#define USARTx_IRQHandler               	UART4_IRQHandler

#define USARTx_TX_PIN                   	GPIO_Pin_10         
#define USARTx_TX_GPIO_PORT             	GPIOC                    
#define USARTx_TX_GPIO_CLK              	RCC_AHB1Periph_GPIOC
#define USARTx_TX_SOURCE                	GPIO_PinSource10
#define USARTx_TX_AF                    	GPIO_AF_UART4

#define USARTx_RX_PIN                   	GPIO_Pin_11     
#define USARTx_RX_GPIO_PORT             	GPIOC                 
#define USARTx_RX_GPIO_CLK              	RCC_AHB1Periph_GPIOC
#define USARTx_RX_SOURCE                	GPIO_PinSource11
#define USARTx_RX_AF                    	GPIO_AF_UART4

#define USARTx_DMA                      	DMA1
#define USARTx_DMAx_CLK                 	RCC_AHB1Periph_DMA1
#define DMACLEAR                        	DMA1->HIFCR = DMA_Stream4_IT_MASK;				//TX	



#define USART_RX_DMA_Stream 							DMA1_Stream2
#define USART_RX_DMA_Channel   						DMA_Channel_4									
#define USART_RX_DMA_PeripheralBaseAddr 	(uint32_t) (&(USARTx->DR))

#define USART_TX_DMA_Stream 							DMA1_Stream4
#define USART_TX_DMA_Channel   						DMA_Channel_4
#define USART_TX_DMA_IRQn									DMA1_Stream4_IRQn
#define USART_TX_DMA_IRQHandler						DMA1_Stream4_IRQHandler
#define USART_TX_DMA_PeripheralBaseAddr 	(uint32_t) (&(USARTx->DR))

u8 rec_data_u4[U4_DATA_LEN];      													//�������ݵ�ַ
u8 send_data_u4[U4_DATA_LEN];     													//�������ݵ�ַ

/****
	* @brief  ���ڵĳ�ʼ��
	* @param  ��
	* @note   ��
	* @retval ��
	* @bug
    * @todo	
	*/
void UART4_Init(int Baud)
{
	NVIC_InitTypeDef NVIC_InitStructure;											//�����жϽṹ��
 	GPIO_InitTypeDef GPIO_InitStructure;											//����IO��ʼ���ṹ��
	USART_InitTypeDef USART_InitStructure;										//���崮�ڽṹ��
	DMA_InitTypeDef DMA_InitStructure;												//����DMA�ṹ��
  USARTx_CLK_INIT(USARTx_CLK, ENABLE);								//�򿪴��ڶ�Ӧ������ʱ��

	//**********************���� ���� DMA ���ã�DMA1_Stream6��**************************
	
  RCC_AHB1PeriphClockCmd(USARTx_DMAx_CLK, ENABLE);					//����DMAʱ��

	NVIC_InitStructure.NVIC_IRQChannel = USART_TX_DMA_IRQn; 	//DMA�����ж�����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	DMA_DeInit(USART_TX_DMA_Stream );																						//DMAͨ������
	DMA_InitStructure.DMA_Channel = USART_TX_DMA_Channel;
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART_TX_DMA_PeripheralBaseAddr;	//�����ַ
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)send_data_u4;							//�ڴ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;											//dma���䷽��
	DMA_InitStructure.DMA_BufferSize = U4_DATA_LEN;															//����DMA�ڴ���ʱ�������ĳ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;						//����DMA���������ģʽ��һ������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;											//����DMA���ڴ����ģʽ

	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;			//���������ֳ�
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;					//�ڴ������ֳ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;																//����DMA�Ĵ���ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;													//����DMA�����ȼ���
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;    									//ָ�����FIFOģʽ��ֱ��ģʽ������ָ������ �� ��ʹ��FIFOģʽ
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;  					//ָ����FIFO��ֵˮƽ
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; 								//ָ����Burstת�������ڴ洫��
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 				//ָ����Burstת��������Χת�� */

	DMA_Init(USART_TX_DMA_Stream , &DMA_InitStructure);													//����DMA1��ͨ��
	
	DMA_ITConfig(USART_TX_DMA_Stream ,DMA_IT_TC,ENABLE);												//ʹ���ж�

  USART_DMACmd(USARTx, USART_DMAReq_Tx, ENABLE);															//ʹ�ܴ��ڵ�DMA���ͽӿ�
	
	DMA_Cmd(USART_TX_DMA_Stream,DISABLE);																				//�ر�ͨ��

	//**********************���� ���� DMA ����**************************
  RCC_AHB1PeriphClockCmd(USARTx_DMAx_CLK, ENABLE);														//DMAͨ������
	
	DMA_DeInit(USART_RX_DMA_Stream);																						//DMAͨ������
	DMA_InitStructure.DMA_Channel = USART_TX_DMA_Channel;
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART_TX_DMA_PeripheralBaseAddr;	//�����ַ
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rec_data_u4;							//�ڴ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;											//dma���䷽��
	DMA_InitStructure.DMA_BufferSize = U4_DATA_LEN;															//����DMA�ڴ���ʱ�������ĳ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;						//����DMA���������ģʽ��һ������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;											//����DMA���ڴ����ģʽ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;			//���������ֳ�
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;							//�ڴ������ֳ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;															//����DMA�Ĵ���ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;											//����DMA�����ȼ���
	
	DMA_Init(USART_RX_DMA_Stream, &DMA_InitStructure);													//����DMA1��ͨ��
	
	DMA_Cmd(USART_RX_DMA_Stream,ENABLE);																				//ʹ��ͨ��

	USART_DMACmd(USARTx,USART_DMAReq_Rx,ENABLE);																//ʹ�ܴ��ڵ�DMA����

  USART_InitStructure.USART_WordLength = USART_WordLength_8b;									//��ʼ�����ڲ���
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStructure.USART_BaudRate = Baud;
  USART_Init(USARTx,&USART_InitStructure);																		//��ʼ������

  NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;               						//ͨ������Ϊ�����ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       						//�ж�ռ�ȵȼ�
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;              						//�ж���Ӧ���ȼ�
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 						//���ж�
  NVIC_Init(&NVIC_InitStructure);

	USART_DMACmd(USARTx,USART_DMAReq_Tx,ENABLE);																//����DMA��ʽ����
	USART_DMACmd(USARTx,USART_DMAReq_Rx,ENABLE);																//����DMA��ʽ����

	
	USART_ITConfig(USARTx,USART_IT_TC,DISABLE);																	//�ж�����
	USART_ITConfig(USARTx,USART_IT_RXNE,DISABLE);
	USART_ITConfig(USARTx,USART_IT_TXE,DISABLE);
	USART_ITConfig(USARTx,USART_IT_IDLE,ENABLE);
 
  USART_Cmd(USARTx, ENABLE);																									//��������
 
	RCC_AHB1PeriphClockCmd(USARTx_TX_GPIO_CLK, ENABLE);													//����IO��ʱ��
	GPIO_PinAFConfig(USARTx_TX_GPIO_PORT,USARTx_TX_SOURCE,USARTx_TX_AF);
	GPIO_PinAFConfig(USARTx_RX_GPIO_PORT,USARTx_RX_SOURCE,USARTx_RX_AF);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	 															//�ܽ�ģʽ:�����
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	    												//����:����ģʽ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	 															//������������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;													//IO���ٶ�
	GPIO_InitStructure.GPIO_Pin = USARTx_TX_PIN;  															//�ܽ�ָ��
	GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStructure);												//��ʼ��

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;																//�ܽ�ģʽ:�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	 													//������������
	GPIO_InitStructure.GPIO_Pin = USARTx_RX_PIN;    														//�ܽ�ָ��
	GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStructure);      									//��ʼ��
}

/****
	* @brief  ���ڷ���
	* @param  ��
	* @note   DMA_FLAG_TCIF4 û�н��к궨�� ��Ҫ���иĶ� ����������������ͬ  TX
	* @retval ��
	* @bug
  * @todo	
	*/
void UART4_DMATransfer(uint32_t *BufferSRC, uint32_t BufferSize)							//UASRT DMA��������
{
	DMA_ClearFlag(USART_TX_DMA_Stream,DMA_FLAG_TCIF4);
	USART_TX_DMA_Stream->NDTR = BufferSize;    																	//����BUFFER��С
	USART_TX_DMA_Stream->M0AR = (uint32_t)BufferSRC;   													//���õ�ַ
	USART_TX_DMA_Stream->CR |= DMA_SxCR_EN;																			//��DMA,��ʼ����
}



/****
	* @brief  ���ڽ����ж�
	* @param  ��
	* @note   Uart2_Rec_Len ���иĶ� ���ڼ����Ǽ�
	* @retval ��
	* @bug
  * @todo	
	*/
void UART4_IRQHandler(void)
{

	int t;
	if(USART_GetITStatus(USARTx, USART_IT_IDLE) != RESET)  											//�����ж�
	{
		t= USART_ReceiveData(USARTx);																							//��ȡ���� ע�⣺������Ҫ�������ܹ�����жϱ�־λ��
		//Usart1_Rec_Len = U1_DATA_LEN - USART_RX_DMA_Stream->NDTR;
		//***********֡���ݴ�����************//
		
		//*************************************//
		DMA1_S2_Reset();                                       										//�ָ�DMAָ�룬�ȴ���һ�εĽ���
  }
	else if(USART_GetITStatus(USARTx, USART_IT_TC) != RESET)
	{
		USART_ClearITPendingBit(USARTx, USART_IT_TC);
		USART_TX_DMA_Stream->CR &= (uint32_t)(~DMA_SxCR_EN);   										//�ر�DMA,�������
	}
}

/****
	* @brief  ���ڷ����ж�
	* @param  ��
	* @note   DMA_IT_TCIF6 ���иĶ� �������Ǽ�
	* @retval ��
	* @bug
  * @todo	
	*/
void USART_TX_DMA_IRQHandler(void)
{
    if(DMA_GetITStatus(USART_TX_DMA_Stream,DMA_IT_TCIF4) != RESET)
    {        
      DMA_ClearFlag(USART_TX_DMA_Stream,DMA_IT_TCIF4);												// �����־λ       
      DMA_Cmd(USART_TX_DMA_Stream,DISABLE);																		//�ر�DMA       
      USART_ITConfig(USARTx,USART_IT_TC,ENABLE);      												//�򿪷�������ж�,ȷ�����һ���ֽڷ��ͳɹ� 
    }
}

/****
	* @brief  DMA���ú���
	* @param  ��
	* @note   ��־λ ���иĶ� �������Ǽ�
	* @retval ��
	* @bug
  * @todo	
	*/

void DMA1_S2_Reset(void)
{ 
	DMA_ClearFlag(USART_RX_DMA_Stream,DMA_IT_TCIF2|DMA_FLAG_HTIF2|DMA_FLAG_TEIF2|DMA_FLAG_DMEIF2|DMA_FLAG_FEIF2);  
	DMA_Cmd(USART_RX_DMA_Stream,DISABLE); 																			//�ر�USART2 TX DMA1 ��ָʾ��ͨ��
	USART_RX_DMA_Stream->NDTR = U4_DATA_LEN;            
	DMA_Cmd(USART_RX_DMA_Stream,ENABLE); 																				//ʹ��USART2 TX DMA1 ��ָʾ��ͨ�� 
}

/****
	* @brief  ��λ������ V7�汾 
	* @param  ��
	* @note   ��
	* @retval ��
	* @bug
  * @todo	
	*/
void VOFA4_send(char *send,float data1,float data2)
{
    sprintf(send,"%f,%f\n",data1,data2);//ת��Ϊchar
    UART4_DMATransfer((u32*)send,strlen(send));
}
