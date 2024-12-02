#include "encoder.h"
#include "sys.h"
#include "led.h"

float Total_speed=0,Total_distance=0;

//cntA;cntB;speedA;speedB;disA; disB;
EncoderStruct Encoders={0,0,0,0,0,0};

//�˲��Ľṹ��
EncoderFilter_Struct EncoAspeed_Filter = {0,0,0,0,{0}};
EncoderFilter_Struct EncoBspeed_Filter = {0,0,0,0,{0}};
/*
********************************************************************************************************************
*                  void TIM3_EncoderB_Init(u16 arr,u16 psc)
*
*Description : ��ʱ��3�����벶������
*Arguments   : ���ʱ��Ϊ����arr+1��*��psc+1��/84M
*Returns     : none
*Notes       : arr:�Զ���װֵ,psc:ʱ��Ԥ��Ƶ��
********************************************************************************************************************
*/
void TIM3_EncoderB_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 6;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	TIM_SetCounter(TIM3, 0);
	TIM_Cmd(TIM3, ENABLE);	
}
	
/*
********************************************************************************************************************
*              void TIM5_EncoderA_Init(u16 arr,u16 psc)
*
*Description : ��ʱ��5�����벶������
*Arguments   : ���ʱ��Ϊ����arr+1��*��psc+1��/84M
*Returns     : none
*Notes       : arr:�Զ���װֵ,psc:ʱ��Ԥ��Ƶ��
********************************************************************************************************************
*/
void TIM5_EncoderA_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure; 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);//ʹ�ñ�����ģʽ3
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 6;
	TIM_ICInit(TIM5, &TIM_ICInitStructure);
	
	TIM_ClearFlag(TIM5, TIM_FLAG_Update);
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	
	TIM_SetCounter(TIM5, 0);
	TIM_Cmd(TIM5, ENABLE);
}	

/*
********************************************************************************************************************
*                  void Read_Encoder_Cnt(void)
*
*Description : ���ұ��������ٺ���
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void Read_Encoder_Cnt(void)
{
	Encoders.cntA = (short)TIM5->CNT;
	Encoders.cntB = -(short)TIM3->CNT;
	TIM5->CNT = 0;
	TIM3->CNT = 0;
}
/*
********************************************************************************************************************
*                  void Solve_EncoData(void)
*
*Description : ������������롢�ٶȺ���
*Arguments   : none
*Returns     : none
*Notes       : 3168�������תһȦ��CNT����ֵ  3.14��Pi   10.0������ֱ��/cm  time������Ƶ��/s
********************************************************************************************************************
*/
void Solve_EncoData()//��λcm
{
	float Encoder_disA=0,SpeedA_Origion=0;
	float Encoder_disB=0,SpeedB_Origion=0;
	float Encoder_Check_Time=TIM14->CNT*0.0002;
	TIM14->CNT=0;
	Read_Encoder_Cnt();
	Encoder_disA=(Encoders.cntA/952.0f)*3.14f*9.6f;
	Encoder_disB=(Encoders.cntB/952.0f)*3.14f*9.6f;
	SpeedA_Origion=Encoder_disA/Encoder_Check_Time;
	SpeedB_Origion=Encoder_disB/Encoder_Check_Time;
	Encoder_Filter(&EncoAspeed_Filter,SpeedA_Origion,5,&Encoders.speedA);
	Encoder_Filter(&EncoBspeed_Filter,SpeedB_Origion,5,&Encoders.speedB);
	Encoders.disA+=Encoder_disA;
	Encoders.disB+=Encoder_disB;
	Total_speed=(Encoders.speedA+Encoders.speedB)/2;
	Total_distance=(Encoders.disA +Encoders.disB)/2;
}



void TIM14_Speed_Check_Init()//0.2ms
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);

	TIM_TimeBaseStructure.TIM_Prescaler=16799;
	TIM_TimeBaseStructure.TIM_Period=0xffff;//65535,arr
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM14,&TIM_TimeBaseStructure);
	
	TIM_Cmd(TIM14, ENABLE); //ʹ�� TIM14
}

void Encoder_Clear()
{
	Encoders.disA=0;
	Encoders.disB=0;
	Total_distance=0;
}
	

/******************************************************************************************************************
*             void Encoder_Filter(Filter_Struct *filterStruct,float newDatas,unsigned char FilterNum,float *Out)
*
*Description : ��ǿ�;�ֵ�˲�  ȥ��һ�����ֵ����Сֵ
*Returns     : ��ǰ������
*Notes       : ����������ڳ�������ɻ���
*              
							*filterStruct		ѡ���˲��Ľṹ��
							newDatas				������
							FilterNum				�˲���������
							*Out						���ֵ
*******************************************************************************************************************
*/
void Encoder_Filter(EncoderFilter_Struct *filterStruct,float newDatas,unsigned char FilterNum,float *Out)
{
	unsigned int i = 0;
	float FilterSum  = 0;
	static float max,min;
	
	filterStruct->Data_His[filterStruct->Count++] = newDatas;
	
	if( filterStruct->Complete )                //�Ѿ��ɼ��������AdcFilterNum������
	{
		max = min = filterStruct->Data_His[0];    //��ʼ��
	//�ҵ������Сֵ
		for(i =1;i < FilterNum; i ++)
		{
			if(filterStruct->Data_His[i] > max)
			{
				max = filterStruct->Data_His[i];
			}
			
			if(filterStruct->Data_His[i] < min)
			{
				min = filterStruct->Data_His[i];
			}
		}
		
		for(i = 0; i < FilterNum; i++)
		{
			FilterSum += filterStruct->Data_His[i];
		}
		FilterSum -= max + min;
		filterStruct->Cache = FilterSum / (FilterNum-2);
	}
	
	if(filterStruct->Complete  == 1)
	{
		if(filterStruct->Cache < 5000)
		{
			*Out = filterStruct->Cache;
			filterStruct->Last_Data 	 = filterStruct->Cache;
		}
		else
			*Out = filterStruct->Last_Data;
	}
	if(filterStruct->Count == FilterNum)
	{
		filterStruct->Complete   = 1;
		filterStruct->Count = 0;
	}
}

