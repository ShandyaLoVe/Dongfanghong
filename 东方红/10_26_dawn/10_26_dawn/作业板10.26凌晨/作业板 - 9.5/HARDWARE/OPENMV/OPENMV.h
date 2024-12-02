#ifndef __OPENMV_H
#define __OPENMV_H 
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

extern u16 work_state;// 接收数据
extern int tree_colour;



void USART1_Init(int Baud);
																			//DMA1_Stream2 接收重置	RX
#endif /* __USART1_DMA_H */
