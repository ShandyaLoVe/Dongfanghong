#ifndef __PID_H
#define __PID_H

typedef struct
{
	volatile float  SetPoint;            /* 目标值 */
	volatile float  ActualValue;         /* 期望输出值 */
	volatile float  SumError;            /* 误差累计 */
	volatile float  Proportion;          /* 比例常数 P */
	volatile float  Integral;            /* 积分常数 I */
	volatile float  Derivative;          /* 微分常数 D */
	volatile float  Error;               /* Error[1] */
	volatile float	LastError;           /* Error[-1] */
	volatile float	PrevError;           /* Error[-2] */
	volatile float	Output_MAX;          /* 输出限幅 */
	volatile float	Output_MIN;          /* 输出限幅 */
	volatile float	SUM_MAX;         		 /* 积分限幅 */
	volatile float	STEP;         		   /* 步长 */
	volatile float	Anti_saturation;     /* 抗积分饱和 */
}PID_Position_TypeDef;


typedef struct												 //增量式PID
{
	volatile float  SetPoint;            /* 目标值 */
	volatile float  ActualValue;         /* 期望输出值 */
	volatile float  SumError;            /* 误差累计 */
	volatile float  Proportion;          /* 比例常数 P */
	volatile float  Integral;            /* 积分常数 I */
	volatile float  Derivative;          /* 微分常数 D */
	volatile float  Error;               /* Error[1] */
	volatile float	LastError;           /* Error[-1] */
	volatile float	PrevError;           /* Error[-2] */
	volatile float	Output_MAX;          /* 输出限幅 */
	volatile float	Output_MIN;          /* 输出限幅 */
}PID_Increment_TypeDef;

extern PID_Increment_TypeDef PID_SpeedA;
extern PID_Increment_TypeDef PID_SpeedB;

extern PID_Position_TypeDef PID_Angle_yaw;
extern PID_Position_TypeDef PID_Ultra_Cross;

extern float yaw;

int Increment_Pid_Ctrl(PID_Increment_TypeDef *PID,float Feedback_value);
int Positional_Pid_Ctrl(PID_Position_TypeDef *PID,float Feedback_value);
float Two_Positional_Pid_Ctrl(PID_Position_TypeDef *PID,float Feedback_value);	

#endif
