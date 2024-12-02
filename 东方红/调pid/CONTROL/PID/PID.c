#include "PID.h"

PID_Increment_TypeDef PID_SpeedA;
PID_Increment_TypeDef PID_SpeedB;
PID_Position_TypeDef PID_Angle_yaw;
PID_Position_TypeDef PID_Ultra_Cross;
extern float start_yaw,end_yaw;

int Increment_Pid_Ctrl(PID_Increment_TypeDef *PID,float Feedback_value)						/* ����ʽPID */
{
	int Last_result=PID->ActualValue;
	PID->Error = (float)(PID->SetPoint - Feedback_value);               	 				/* ����ƫ�� */
                                                         
	PID->ActualValue += (PID->Proportion * (PID->Error - PID->LastError))                          /* �������� */
                      + (PID->Integral * PID->Error)                                             /* ���ֻ��� */
                      + (PID->Derivative * (PID->Error - 2 * PID->LastError + PID->PrevError));  /* ΢�ֻ��� */
    
	PID->PrevError = PID->LastError;                                       					 /* �洢ƫ������´μ��� */
	PID->LastError = PID->Error;
	
//	if((PID->ActualValue-Last_result)>(55))PID->ActualValue=Last_result+55;
//	else if((PID->ActualValue-Last_result)<-55)PID->ActualValue=Last_result-55;
	
	if(PID->ActualValue>PID->Output_MAX)PID->ActualValue=PID->Output_MAX;
	else if(PID->ActualValue<PID->Output_MIN)PID->ActualValue=PID->Output_MIN;
    
	return ((int)(PID->ActualValue));                                															 /* ���ؼ�����������ֵ */
}

int Positional_Pid_Ctrl(PID_Position_TypeDef *PID,float Feedback_value)									/* λ��ʽPID */
{
	PID->Error = (float)(PID->SetPoint - Feedback_value);                  							    /* ����ƫ�� */	
  
	PID->ActualValue = (PID->Proportion * PID->Error)                      		/* �������� */
                       +(PID->Integral * PID->SumError)
                     + (PID->Derivative * (PID->Error - PID->LastError));	    /* ΢�ֻ��� */
	PID->LastError = PID->Error;
    PID->SumError = PID->SumError + PID->Error;
    
    //����������޷�
    if( PID->SumError>15) PID->SumError=15;
	else if( PID->SumError<-15) PID->SumError=-15;
	//����������޷�
	if(PID->ActualValue>PID->Output_MAX)PID->ActualValue=PID->Output_MAX;
	else if(PID->ActualValue<PID->Output_MIN)PID->ActualValue=PID->Output_MIN;
    
	return ((int)(PID->ActualValue));                             														     /* ���ؼ�����������ֵ */
}

float Two_Positional_Pid_Ctrl(PID_Position_TypeDef *PID,float Feedback_value)													 /* λ��ʽPID */
{
	float Last_result=PID->ActualValue;
	
	PID->Error = (float)(PID->SetPoint - Feedback_value);                  												 /* ����ƫ�� */	
  
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
    
	return ((float)(PID->ActualValue));                             														     /* ���ؼ�����������ֵ */
}



