#ifndef __OPENMV_H
#define __OPENMV_H 
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
#define U1_DATA_LEN  								15

extern u16 work_state;// ��������
extern int tree_colour;



void USART1_Init(int Baud);
																			//DMA1_Stream2 ��������	RX
#endif /* __USART1_DMA_H */
