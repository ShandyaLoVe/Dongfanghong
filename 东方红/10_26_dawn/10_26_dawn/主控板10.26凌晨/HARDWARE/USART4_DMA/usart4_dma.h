#ifndef __USART4_DMA_H
#define __USART4_DMA_H	 
#include "sys.h"
/****
	*****************************************************************************
	* @file    usartx_dma.c
	* @author  ������
	* @version V1.0
	* @date    2021-7-7
	* @brief   ����DMA����
	* @license Copyright 2021. All rights reserved. 

	*****************************************************************************
	* @note  	 ����_DMA
	* @bug
	* @todo	
	* @details 
	*
	*****************************************************************************
	*/
/****
	*****************************************************************************
										        CONSTANTS & MACROS
	*****************************************************************************
	* @brief  ���ݳ��Ⱥͽ��շ��͵�����
	*/
#define U4_DATA_LEN  								15

extern u8 rec_data_u4[U4_DATA_LEN];   										// ��������
extern u8 send_data_u4[U4_DATA_LEN];   										// ��������
/*
*******************************************************************************
*                            FUNCTION PROTOTYPES
*                                ���ں���
*******************************************************************************
*/
extern void UART4_Init(int Baud);
extern void UART4_DMATransfer(uint32_t *BufferSRC, uint32_t BufferSize);			//UASRT DMA��������
extern void DMA1_S2_Reset(void);																							//DMA1_Stream2 ��������	RX
extern void VOFA4_send(char *send,float data1,float data2);
#endif /* __USART1_DMA_H */
