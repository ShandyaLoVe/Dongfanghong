#ifndef __WT1_H
#define __WT1_H

#include "sys.h"
void WT1_init(void);
void CopeSerial2Data(unsigned char ucData);
void sendcmd_usart2(unsigned char *cmd);

extern int16_t usData[4];
extern int16_t usData1[4];
extern int16_t usData2[4];



#endif
