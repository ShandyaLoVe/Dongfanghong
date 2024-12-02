#ifndef __USART2_DMA_H
#define __USART2_DMA_H	 
#include "sys.h"


//使用USART2时开启，不用可以注释
#define U2_DATA_LEN  11

extern u8 rec_data_u2[U2_DATA_LEN]; // 接收数据
extern u8 send_data_u2[U2_DATA_LEN];// 接收数据
extern float yaw;

void USART2_Init(int Baud);
void USART2_DMATransfer(uint32_t *BufferSRC, uint32_t BufferSize);//UASRT DMA发送设置
void DMA1_S5_Reset(void);
void Uart2Send(unsigned char *p_data, unsigned int uiSize);

#endif
