#ifndef __USART3_H
#define __USART3_H

#include "sys.h"	  	
 	
#define ANGLE_PER_FRAME 12
#define HEADER 0x54
#define POINT_PER_PACK 12
#define VERLEN  0x2C 	//低五位是一帧数据接收到的点数，目前固定是12，高三位固定为1

typedef struct __attribute__((packed)) Point_Data
{
	u16 distance_1;//距离
	u8 intensity;//置信度
	
}LidarPointStructDef;

typedef struct __attribute__((packed)) Pack_Data
{
	uint8_t header;
	uint8_t ver_len;
	uint16_t temperature;
	uint16_t start_angle;
	LidarPointStructDef point[POINT_PER_PACK];
	uint16_t end_angle;
	uint16_t timestamp;
	uint8_t crc8;
}LiDARFrameTypeDef;


extern u16 receive_cnt_1;
extern u16 distance_1;


void uart4_init(u32 bound);
void UART4_IRQHandler(void);
void data_process_1(void);


#endif


