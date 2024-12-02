#include "math.h"
#include "pid_small.h"

PID_Position_TypeDef  yaw_base1_pid,yaw_base2_pid;
PID_Position_TypeDef  ultra_base1_pid,ultra_base2_pid;

void pid_yaw_y_Init(void)
{
	yaw_base1_pid.SetPoint = 0.0;       /* Ŀ��ֵ */
	yaw_base1_pid.ActualValue = 0.0;    /* �������ֵ */
	yaw_base1_pid.SumError = 0.0;       /* ����ֵ */
	
	yaw_base1_pid.Error = 0.0;          /* Error[1] */
	yaw_base1_pid.LastError = 0.0;      /* Error[-1] */
	yaw_base1_pid.PrevError = 0.0;      /* Error[-2] */
	
	yaw_base1_pid.Proportion =0.82;    /* �������� Proportional Const */
	yaw_base1_pid.Integral = 0;      /* ���ֳ��� Integral Const */
	yaw_base1_pid.Derivative = 0.106;    /* ΢�ֳ��� Derivative Const 0.59 */ 
	
	yaw_base1_pid.Output_MAX=200;
	yaw_base1_pid.Output_MIN=-200;
	yaw_base1_pid.SUM_MAX=100;

	yaw_base1_pid.STEP=100;
	yaw_base1_pid.Anti_saturation=100;
	
}

void pid_yaw_x_Init(void)
{
	yaw_base2_pid.SetPoint = 0.0;       /* Ŀ��ֵ */
	yaw_base2_pid.ActualValue = 0.0;    /* �������ֵ */
	yaw_base2_pid.SumError = 0.0;       /* ����ֵ */
	
	yaw_base2_pid.Error = 0.0;          /* Error[1] */
	yaw_base2_pid.LastError = 0.0;      /* Error[-1] */
	yaw_base2_pid.PrevError = 0.0;      /* Error[-2] */
	
	yaw_base2_pid.Proportion = 0.6;    //* �������� Proportional Const */0.75
	yaw_base2_pid.Integral = 0;    			/* ���ֳ��� Integral Const */
	yaw_base2_pid.Derivative = 0.73;    //* ΢�ֳ��� Derivative Const */ 0.29
	
	yaw_base2_pid.Output_MAX= 1000;
	yaw_base2_pid.Output_MIN= -1000;
	yaw_base2_pid.SUM_MAX=200;
	
	yaw_base2_pid.STEP=200;
	yaw_base2_pid.Anti_saturation=200;
	
	
}

void pid_ultra_1_Init(void)
{
	ultra_base1_pid.SetPoint = 0.0;       /* Ŀ��ֵ */
	ultra_base1_pid.ActualValue = 0.0;    /* �������ֵ */
	ultra_base1_pid.SumError = 0.0;       /* ����ֵ */
	
	ultra_base1_pid.Error = 0.0;          /* Error[1] */
	ultra_base1_pid.LastError = 0.0;      /* Error[-1] */
	ultra_base1_pid.PrevError = 0.0;      /* Error[-2] */
	
	ultra_base1_pid.Proportion =6.5;    /* �������� Proportional Const */
	ultra_base1_pid.Integral = 0;      /* ���ֳ��� Integral Const */
	ultra_base1_pid.Derivative = 2.5;    /* ΢�ֳ��� Derivative Const */ 
	
	ultra_base1_pid.Output_MAX=250;
	ultra_base1_pid.Output_MIN=-250;
	ultra_base1_pid.SUM_MAX=250;

	ultra_base1_pid.STEP=250;
	ultra_base1_pid.Anti_saturation=250;
	
}

void pid_ultra_2_Init(void)
{
	ultra_base2_pid.SetPoint = 0.0;       /* Ŀ��ֵ */
	ultra_base2_pid.ActualValue = 0.0;    /* �������ֵ */
	ultra_base2_pid.SumError = 0.0;       /* ����ֵ */
	
	ultra_base2_pid.Error = 0.0;          /* Error[1] */
	ultra_base2_pid.LastError = 0.0;      /* Error[-1] */
	ultra_base2_pid.PrevError = 0.0;      /* Error[-2] */
	
	ultra_base2_pid.Proportion =5.6;    /* �������� Proportional Const */
	ultra_base2_pid.Integral = 0;      /* ���ֳ��� Integral Const */
	ultra_base2_pid.Derivative = 2.5;    /* ΢�ֳ��� Derivative Const */ 
	
	ultra_base2_pid.Output_MAX=200;
	ultra_base2_pid.Output_MIN=-200;
	ultra_base2_pid.SUM_MAX=200;

	ultra_base2_pid.STEP=200;
	ultra_base2_pid.Anti_saturation=200;
	
}

float yaw_base1_Pid_Ctrl(PID_Position_TypeDef *PID,float data,float goal)
{
    float Last_result=PID->ActualValue;
	
	PID->Error = (float)(PID->SetPoint - (data-goal));               	   												 /* ����ƫ�� */	
  
	if((PID->Error<PID->Anti_saturation)&&(PID->Error>-PID->Anti_saturation))PID->SumError += PID->Error;
	
	if(PID->SumError>PID->SUM_MAX)PID->SumError=PID->SUM_MAX;
	else if(PID->SumError<-PID->SUM_MAX)PID->SumError=-PID->SUM_MAX;
	
	PID->ActualValue = (PID->Proportion * PID->Error)                      												 /* �������� */
                     + (PID->Integral * PID->SumError)                   												 /* ���ֻ��� */
                     + (PID->Derivative * (PID->Error - PID->LastError));												 /* ΢�ֻ��� */
	PID->LastError = PID->Error;
	
	if((PID->ActualValue-Last_result)>(PID->STEP))PID->ActualValue=Last_result+PID->STEP;
	else if((PID->ActualValue-Last_result)<-PID->STEP)PID->ActualValue=Last_result-PID->STEP;
	
	if(PID->ActualValue>PID->Output_MAX)PID->ActualValue=PID->Output_MAX;
	else if(PID->ActualValue<PID->Output_MIN)PID->ActualValue=PID->Output_MIN;
    
	return ((float)(PID->ActualValue));              
}

float ultra_base1_Pid_Ctrl(PID_Position_TypeDef *PID,float data,float goal)
{
    float Last_result=PID->ActualValue;
	
	if (((data-goal)<15.0f)&&((data-goal)>-15.0f))
	{
		PID->Error=0;
	}
	else if((data-goal)<-15.0f)
	{
	PID->Error = (float)(PID->SetPoint - (data-goal))-15;               	   												 /* ����ƫ�� */	
    }
	else if((data-goal)>15.0f)
	{
	PID->Error = (float)(PID->SetPoint - (data-goal))+15;               	   												 /* ����ƫ�� */	
    }
	if((PID->Error<PID->Anti_saturation)&&(PID->Error>-PID->Anti_saturation))PID->SumError += PID->Error;
	
	if(PID->SumError>PID->SUM_MAX)PID->SumError=PID->SUM_MAX;
	else if(PID->SumError<-PID->SUM_MAX)PID->SumError=-PID->SUM_MAX;
	
	PID->ActualValue = (PID->Proportion * PID->Error)                      												 /* �������� */
                     + (PID->Integral * PID->SumError)                   												 /* ���ֻ��� */
                     + (PID->Derivative * (PID->Error - PID->LastError));												 /* ΢�ֻ��� */
	PID->LastError = PID->Error;
	
	if((PID->ActualValue-Last_result)>(PID->STEP))PID->ActualValue=Last_result+PID->STEP;
	else if((PID->ActualValue-Last_result)<-PID->STEP)PID->ActualValue=Last_result-PID->STEP;
	
	if(PID->ActualValue>PID->Output_MAX)PID->ActualValue=PID->Output_MAX;
	else if(PID->ActualValue<PID->Output_MIN)PID->ActualValue=PID->Output_MIN;
    
	return ((float)(PID->ActualValue));              
}

float ultra_base2_Pid_Ctrl(PID_Position_TypeDef *PID,float data,float goal)
{
    float Last_result=PID->ActualValue;
	
	if (((data-goal)<10.0f)&&((data-goal)>-10.0f))
	{
		PID->Error=0;
	}
	else if((data-goal)<-10.0f)
	{
	PID->Error = (float)(PID->SetPoint - (data-goal))-10;               	   												 /* ����ƫ�� */	
    }
	else if((data-goal)>10.0f)
	{
	PID->Error = (float)(PID->SetPoint - (data-goal))+10;               	   												 /* ����ƫ�� */	
    }
	if((PID->Error<PID->Anti_saturation)&&(PID->Error>-PID->Anti_saturation))PID->SumError += PID->Error;
	
	if(PID->SumError>PID->SUM_MAX)PID->SumError=PID->SUM_MAX;
	else if(PID->SumError<-PID->SUM_MAX)PID->SumError=-PID->SUM_MAX;
	
	PID->ActualValue = (PID->Proportion * PID->Error)                      												 /* �������� */
                     + (PID->Integral * PID->SumError)                   												 /* ���ֻ��� */
                     + (PID->Derivative * (PID->Error - PID->LastError));												 /* ΢�ֻ��� */
	PID->LastError = PID->Error;
	
	if((PID->ActualValue-Last_result)>(PID->STEP))PID->ActualValue=Last_result+PID->STEP;
	else if((PID->ActualValue-Last_result)<-PID->STEP)PID->ActualValue=Last_result-PID->STEP;
	
	if(PID->ActualValue>PID->Output_MAX)PID->ActualValue=PID->Output_MAX;
	else if(PID->ActualValue<PID->Output_MIN)PID->ActualValue=PID->Output_MIN;
    
	return ((float)(PID->ActualValue));              
}