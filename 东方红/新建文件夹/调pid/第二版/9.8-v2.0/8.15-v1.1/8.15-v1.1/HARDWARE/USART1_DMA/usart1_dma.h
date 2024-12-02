#ifndef __USART1_DMA_H
#define __USART1_DMA_H	 
#include "sys.h"
/****
	*****************************************************************************
	* @file    usartx_dma.c
	* @author  杨少文
	* @version V1.0
	* @date    2021-7-7
	* @brief   串口DMA驱动
	* @license Copyright 2021. All rights reserved. 

	*****************************************************************************
	* @note  	 串口_DMA
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
	* @brief  数据长度和接收发送的数组
	*/
#define U1_DATA_LEN  								15

#define start_work 1

extern uint16_t rec_data_u1[U1_DATA_LEN];   										// 接收数据
extern u8 send_data_u1[U1_DATA_LEN];   										// 接收数据
/*
*******************************************************************************
*                            FUNCTION PROTOTYPES
*                                串口函数
*******************************************************************************
*/
extern void USART1_Init(int Baud);
extern void USART1_DMATransfer(uint32_t *BufferSRC, uint32_t BufferSize);			//UASRT DMA发送设置
extern void DMA2_S2_Reset(void);																							//DMA1_Stream2 接收重置	RX
extern void VOFA_send(char *send,float data1,float data2);
#endif /* __USART1_DMA_H */
