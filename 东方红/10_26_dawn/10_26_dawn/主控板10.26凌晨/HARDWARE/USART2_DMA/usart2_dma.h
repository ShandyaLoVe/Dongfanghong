#ifndef __USART2_DMA_H
#define __USART2_DMA_H	 
#include "sys.h"


//ʹ��USART2ʱ���������ÿ���ע��
#define U2_DATA_LEN  11

extern u8 rec_data_u2[U2_DATA_LEN]; // ��������
extern u8 send_data_u2[U2_DATA_LEN];// ��������
extern float yaw;

void USART2_Init(int Baud);
void USART2_DMATransfer(uint32_t *BufferSRC, uint32_t BufferSize);//UASRT DMA��������
void DMA1_S5_Reset(void);
void Uart2Send(unsigned char *p_data, unsigned int uiSize);

#endif
