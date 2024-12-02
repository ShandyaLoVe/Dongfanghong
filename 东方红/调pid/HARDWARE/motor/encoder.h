#ifndef __ENCODER_H
#define __ENCODER_H
#include "stm32f4xx.h"

typedef struct
{
	float cntA;
	float cntB;
	float	speedA;
	float speedB;
	float disA;
	float disB;
	
}EncoderStruct;

//�������˲��ṹ��
typedef struct
{
	unsigned char 	Complete;
	unsigned char   Count;
	float   				Cache;	        //�����м仺��ֵ
	float 		 			Last_Data;	    //��һ�β���ֵ
	float  					Data_His[10];		//������ʷֵ
}EncoderFilter_Struct;

extern EncoderStruct Encoders;


extern float Total_speed,Total_distance;

void TIM2_EncoderB_Init(u16 arr, u16 psc);
void TIM5_EncoderA_Init(u16 arr, u16 psc);

void TIM14_Speed_Check_Init(void);
void Encoder_Clear(void);
void Read_Encoder_Cnt(void);
void Solve_EncoData(void);
void Encoder_Filter(EncoderFilter_Struct *filterStruct,float newDatas,unsigned char FilterNum,float *Out);


#endif

