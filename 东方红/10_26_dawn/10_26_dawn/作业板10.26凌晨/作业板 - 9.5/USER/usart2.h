#ifndef __USART1_H
#define __USART1_H	 
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
#define U2_DATA_LEN  								15

extern u8 rec_data_u2[U2_DATA_LEN];   										// ��������
extern u8 send_data_u2[U2_DATA_LEN];   										// ��������
/*
*******************************************************************************
*                            FUNCTION PROTOTYPES
*                                ���ں���
*******************************************************************************
*/
extern void USART2_Init(int Baud);
extern void USART2_DMATransfer(uint32_t *BufferSRC, uint32_t BufferSize);			//UASRT DMA��������
extern void DMA2_S2_Reset(void);																							//DMA1_Stream2 ��������	RX
extern void VOFA_send(char *send,float data1,float data2);
#endif /* __USART1_DMA_H */
