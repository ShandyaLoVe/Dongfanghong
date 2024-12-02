#ifndef __PID_SMALL_H
#define __PID_SMALL_H

#include "PID.h"

extern PID_Position_TypeDef  yaw_base1_pid,yaw_base2_pid;
extern PID_Position_TypeDef  ultra_base1_pid,ultra_base2_pid;

void pid_yaw_y_Init(void);
void pid_yaw_x_Init(void);
void pid_ultra_1_Init(void);
void pid_ultra_2_Init(void);
float yaw_base1_Pid_Ctrl(PID_Position_TypeDef *PID,float data,float goal);
float ultra_base1_Pid_Ctrl(PID_Position_TypeDef *PID,float data,float goal);
float ultra_base2_Pid_Ctrl(PID_Position_TypeDef *PID,float data,float goal);
#endif

