#ifndef __PID_H
#define __PID_H

typedef struct
{
	volatile float  SetPoint;            /* Ŀ��ֵ */
	volatile float  ActualValue;         /* �������ֵ */
	volatile float  SumError;            /* ����ۼ� */
	volatile float  Proportion;          /* �������� P */
	volatile float  Integral;            /* ���ֳ��� I */
	volatile float  Derivative;          /* ΢�ֳ��� D */
	volatile float  Error;               /* Error[1] */
	volatile float	LastError;           /* Error[-1] */
	volatile float	PrevError;           /* Error[-2] */
	volatile float	Output_MAX;          /* ����޷� */
	volatile float	Output_MIN;          /* ����޷� */
	volatile float	SUM_MAX;         		 /* �����޷� */
	volatile float	STEP;         		   /* ���� */
	volatile float	Anti_saturation;     /* �����ֱ��� */
}PID_Position_TypeDef;


typedef struct												 //����ʽPID
{
	volatile float  SetPoint;            /* Ŀ��ֵ */
	volatile float  ActualValue;         /* �������ֵ */
	volatile float  SumError;            /* ����ۼ� */
	volatile float  Proportion;          /* �������� P */
	volatile float  Integral;            /* ���ֳ��� I */
	volatile float  Derivative;          /* ΢�ֳ��� D */
	volatile float  Error;               /* Error[1] */
	volatile float	LastError;           /* Error[-1] */
	volatile float	PrevError;           /* Error[-2] */
	volatile float	Output_MAX;          /* ����޷� */
	volatile float	Output_MIN;          /* ����޷� */
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
