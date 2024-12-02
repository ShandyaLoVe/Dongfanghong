#include "PID.h"

PID_Increment_TypeDef PID_SpeedA;
PID_Increment_TypeDef PID_SpeedB;
PID_Position_TypeDef PID_Angle_yaw;
PID_Position_TypeDef PID_Ultra_Cross;
extern float start_yaw,end_yaw;

int Increment_Pid_Ctrl(PID_Increment_TypeDef *PID,float Feedback_value)						/* 增量式PID */
{
	int Last_result=PID->ActualValue;
	PID->Error = (float)(PID->SetPoint - Feedback_value);               	 				/* 计算偏差 */
                                                         
	PID->ActualValue += (PID->Proportion * (PID->Error - PID->LastError))                          /* 比例环节 */
                      + (PID->Integral * PID->Error)                                             /* 积分环节 */
                      + (PID->Derivative * (PID->Error - 2 * PID->LastError + PID->PrevError));  /* 微分环节 */
    
	PID->PrevError = PID->LastError;                                       					 /* 存储偏差，用于下次计算 */
	PID->LastError = PID->Error;
	
//	if((PID->ActualValue-Last_result)>(55))PID->ActualValue=Last_result+55;
//	else if((PID->ActualValue-Last_result)<-55)PID->ActualValue=Last_result-55;
	
	if(PID->ActualValue>PID->Output_MAX)PID->ActualValue=PID->Output_MAX;
	else if(PID->ActualValue<PID->Output_MIN)PID->ActualValue=PID->Output_MIN;
    
	return ((int)(PID->ActualValue));                                															 /* 返回计算后输出的数值 */
}

int Positional_Pid_Ctrl(PID_Position_TypeDef *PID,float Feedback_value)									/* 位置式PID */
{
	PID->Error = (float)(PID->SetPoint - Feedback_value);                  							    /* 计算偏差 */	
  
	PID->ActualValue = (PID->Proportion * PID->Error)                      		/* 比例环节 */
                       +(PID->Integral * PID->SumError)
                     + (PID->Derivative * (PID->Error - PID->LastError));	    /* 微分环节 */
	PID->LastError = PID->Error;
    PID->SumError = PID->SumError + PID->Error;
    
    //积分量输出限幅
    if( PID->SumError>15) PID->SumError=15;
	else if( PID->SumError<-15) PID->SumError=-15;
	//整体输出量限幅
	if(PID->ActualValue>PID->Output_MAX)PID->ActualValue=PID->Output_MAX;
	else if(PID->ActualValue<PID->Output_MIN)PID->ActualValue=PID->Output_MIN;
    
	return ((int)(PID->ActualValue));                             														     /* 返回计算后输出的数值 */
}

float Two_Positional_Pid_Ctrl(PID_Position_TypeDef *PID,float Feedback_value)													 /* 位置式PID */
{
	float Last_result=PID->ActualValue;
	
	PID->Error = (float)(PID->SetPoint - Feedback_value);                  												 /* 计算偏差 */	
  
	if((PID->Error<PID->Anti_saturation)&&(PID->Error>-PID->Anti_saturation))PID->SumError += PID->Error;
	
	if(PID->SumError>PID->SUM_MAX)PID->SumError=PID->SUM_MAX;
	else if(PID->SumError<-PID->SUM_MAX)PID->SumError=-PID->SUM_MAX;
	
	PID->ActualValue = (PID->Proportion * PID->Error)                      												 /* 比例环节 */
                     + (PID->Integral * PID->SumError)                   												 /* 积分环节 */
                     + (PID->Derivative * (PID->Error - PID->LastError));												 /* 微分环节 */
	PID->LastError = PID->Error;
	
	if((PID->ActualValue-Last_result)>(PID->STEP))PID->ActualValue=Last_result+PID->STEP;
	else if((PID->ActualValue-Last_result)<-PID->STEP)PID->ActualValue=Last_result-PID->STEP;
	
	if(PID->ActualValue>PID->Output_MAX)PID->ActualValue=PID->Output_MAX;
	else if(PID->ActualValue<PID->Output_MIN)PID->ActualValue=PID->Output_MIN;
    
	return ((float)(PID->ActualValue));                             														     /* 返回计算后输出的数值 */
}



