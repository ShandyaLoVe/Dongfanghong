#include "ultrasonic.h"
#include "sys.h"
#include "led.h"

/******************************************************************************
	���峬�����ĳ�ʼֵ����											
******************************************************************************/
/*	u8  CAPTURE_STA;               //ͨ�����벶���־������λ�������־����6λ�������־		
	u16 CAPTURE_UPVAL;               //ͨ����������
	u16 CAPTURE_DOWNVAL;             //ͨ���½�����
	u32	CAPTURE_VAL;	     				   //ͨ�����벶��ֵ
	
	float DIS; 									     //����������ֵ
	float Last_DIS;
	float max;
	float min;
	u8  CAPTURE_SELECT; */  
Ultra_cap_t ultra_L1 = {0, 0, 0, 0, 0.0f, 0.0f, 2550.0, 0.0, 0};   	//PE15
Ultra_cap_t ultra_L2 = {0, 0, 0, 0, 0.0f, 0.0f, 2550.0, 0.0, 0};		//PD11
Ultra_cap_t ultra_R1 = {0, 0, 0, 0, 0.0f, 0.0f, 2550.0, 0.0, 0};		//PE2
Ultra_cap_t ultra_R2 = {0, 0, 0, 0, 0.0f, 0.0f, 2550.0, 0.0, 0};		//PD10
Ultra_cap_t ultra_F1 = {0, 0, 0, 0, 0.0f, 0.0f, 2550.0, 0.0, 0};		//PB10
Ultra_cap_t ultra_F2 = {0, 0, 0, 0, 0.0f, 0.0f, 2550.0, 0.0, 0};		//PA8

UltrasonicFilter_Struct 	Ultrasonic_L1_Filter = {0,0,0,0,{0}};
UltrasonicFilter_Struct 	Ultrasonic_L2_Filter = {0,0,0,0,{0}};
UltrasonicFilter_Struct 	Ultrasonic_R1_Filter = {0,0,0,0,{0}};
UltrasonicFilter_Struct 	Ultrasonic_R2_Filter = {0,0,0,0,{0}};
UltrasonicFilter_Struct 	Ultrasonic_F1_Filter = {0,0,0,0,{0}};
UltrasonicFilter_Struct 	Ultrasonic_F2_Filter = {0,0,0,0,{0}};

UltrasonicDis             UL_DIS_F={0,0,0,0,0,0};

void Ultrasonic_Init(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(Left1_trig_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = Left1_trig_PIN;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(Left1_trig_GPIO_PORT, &GPIO_InitStructure);
	GPIO_ResetBits(Left1_trig_GPIO_PORT,Left1_trig_PIN);	
	
	RCC_AHB1PeriphClockCmd(Left2_trig_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = Left2_trig_PIN;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(Left2_trig_GPIO_PORT, &GPIO_InitStructure);
	GPIO_ResetBits(Left2_trig_GPIO_PORT,Left2_trig_PIN);
	
	RCC_AHB1PeriphClockCmd(Right1_trig_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = Right1_trig_PIN;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(Right1_trig_GPIO_PORT, &GPIO_InitStructure);
	GPIO_ResetBits(Right1_trig_GPIO_PORT,Right1_trig_PIN);
	
	RCC_AHB1PeriphClockCmd(Right2_trig_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = Right2_trig_PIN;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(Right2_trig_GPIO_PORT, &GPIO_InitStructure);
	GPIO_ResetBits(Right2_trig_GPIO_PORT,Right2_trig_PIN);
	
	RCC_AHB1PeriphClockCmd(Front1_trig_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = Front1_trig_PIN;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(Front1_trig_GPIO_PORT, &GPIO_InitStructure);
	GPIO_ResetBits(Front1_trig_GPIO_PORT,Front1_trig_PIN);
	
	RCC_AHB1PeriphClockCmd(Front2_trig_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = Front2_trig_PIN;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(Front2_trig_GPIO_PORT, &GPIO_InitStructure);
	GPIO_ResetBits(Front2_trig_GPIO_PORT,Front2_trig_PIN);
	
	Ultra_TIM3_Init(0xFFFF, 84 - 1);
	Ultra_TIM9_Init(0xFFFF, 168 - 1);

}


void Ultra_TIM3_Init(u32 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM3_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	                    		//ʹ��TIM3ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);                       	//ʹ��GPIOBʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);                       	//ʹ��GPIOAʱ��
	
	TIM_DeInit(TIM3);	                                                        		//���³�ʼ��TIM3ΪĬ��״̬	
	
	GPIO_InitStructure.GPIO_Pin = Left1_echo_PIN;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                                  //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	                          //�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                                //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;                                //����
	GPIO_Init(Left1_echo_GPIO_PORT, &GPIO_InitStructure);                         //��ʼ��PA2
	
	GPIO_InitStructure.GPIO_Pin = Left2_echo_PIN;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                                  //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	                          //�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                               	//���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;                               	//����
	GPIO_Init(Left2_echo_GPIO_PORT, &GPIO_InitStructure);    

	GPIO_InitStructure.GPIO_Pin = Right1_echo_PIN;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                                 	//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	                         	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                               	//���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;                               	//����
	GPIO_Init(Right1_echo_GPIO_PORT, &GPIO_InitStructure);   
	
	GPIO_InitStructure.GPIO_Pin = Right2_echo_PIN;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                                  //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	                          //�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                                //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;                                //����
	GPIO_Init(Right2_echo_GPIO_PORT, &GPIO_InitStructure);    
	
	GPIO_PinAFConfig(Left1_echo_GPIO_PORT,Left1_echo_GPIO_PinSource,GPIO_AF_TIM3);	//PA2 ����ΪTIM3 CH3
	GPIO_PinAFConfig(Left2_echo_GPIO_PORT,Left2_echo_GPIO_PinSource,GPIO_AF_TIM3);	//PA3 ����ΪTIM3 CH4
	GPIO_PinAFConfig(Right1_echo_GPIO_PORT,Right1_echo_GPIO_PinSource,GPIO_AF_TIM3);//PA5 ����ΪTIM3 CH1
	GPIO_PinAFConfig(Right2_echo_GPIO_PORT,Right2_echo_GPIO_PinSource,GPIO_AF_TIM3);//PB3 ����ΪTIM3 CH2
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM3_ICInitStructure.TIM_ICFilter = 0;
	
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInit(TIM3, &TIM3_ICInitStructure);
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInit(TIM3, &TIM3_ICInitStructure);
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_3;
	TIM_ICInit(TIM3, &TIM3_ICInitStructure);
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_4;
	TIM_ICInit(TIM3, &TIM3_ICInitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ITConfig(TIM3, TIM_IT_Update | TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
}

void Ultra_TIM9_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM9_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);	                    	//ʹ��TIM9ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);                       	//ʹ��GPIOEʱ��
	
	TIM_DeInit(TIM9);
	
	GPIO_InitStructure.GPIO_Pin = Front1_echo_PIN|Front2_echo_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                                   	//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	                           	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                                 	//���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;                                 	//����
	GPIO_Init(GPIOE, &GPIO_InitStructure);                                         	//��ʼ��PB11 
	
	GPIO_PinAFConfig(Front1_echo_GPIO_PORT,Front1_echo_GPIO_PinSource,GPIO_AF_TIM9);//PE5����ΪTIM9 CH1
	GPIO_PinAFConfig(Front2_echo_GPIO_PORT,Front2_echo_GPIO_PinSource, GPIO_AF_TIM9);//PE6 ����ΪTIM9 CH2
	
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);
	
	TIM9_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM9_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM9_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM9_ICInitStructure.TIM_ICFilter = 0;
	
	TIM9_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInit(TIM9, &TIM9_ICInitStructure);
	TIM9_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInit(TIM9, &TIM9_ICInitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_TIM9_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ITConfig(TIM9,TIM_IT_Update | TIM_IT_CC1 | TIM_IT_CC2, ENABLE);
	TIM_Cmd(TIM9, ENABLE);
}

/******************************************************************************
	* @brief  ��ʱ��2�жϷ��������� 
	* @param  ��
	* @retval ��
	* @bug
	* @todo	
	*****************************************************************************
	*/
void TIM3_IRQHandler(void)
{
	if((ultra_L1.CAPTURE_STA & 0x80) == 0)
	{
		if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		{
			if(ultra_L1.CAPTURE_STA & 0x40)
			{
				if((ultra_L1.CAPTURE_STA & 0x02) == 0x02)
				{
					ultra_L1.CAPTURE_STA = 0;
					TIM_OC3PolarityConfig(TIM3, TIM_ICPolarity_Rising);
					ultra_L1.CAPTURE_VAL = 0xFFFFFFFF;
				}
				else ultra_L1.CAPTURE_STA++;			
			}
		}
		if(TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_CC3);
			if(ultra_L1.CAPTURE_STA & 0x40)
			{
				ultra_L1.CAPTURE_DOWNVAL = TIM_GetCapture3(TIM3);
				ultra_L1.CAPTURE_VAL = ultra_L1.CAPTURE_DOWNVAL - ultra_L1.CAPTURE_UPVAL + (ultra_L1.CAPTURE_STA&0X3F)*0XFFFF;
				ultra_L1.DIS = ultra_L1.CAPTURE_VAL * 340.0f / 2000.0f;
				ultra_L1.DIS = Limit(ultra_L1.DIS,0,2550);
				ultra_L1.CAPTURE_STA = 0;		                                    //�����־λ����
				Ultrasonic_Filter(&Ultrasonic_L1_Filter,ultra_L1.DIS,7,&UL_DIS_F.L1);
				TIM_OC3PolarityConfig(TIM3, TIM_ICPolarity_Rising);                 //����Ϊ�����ز���		  
			}
			else
			{
				ultra_L1.CAPTURE_UPVAL = TIM_GetCapture3(TIM3);		                //��ȡ����������
				ultra_L1.CAPTURE_STA |= 0X40;		                                //����Ѳ���������
				TIM_OC3PolarityConfig(TIM3, TIM_ICPolarity_Falling);                //����Ϊ�½��ز���
			}
		}
	}
//------------------------------------------------------------------------------------------------------------------------
	if((ultra_L2.CAPTURE_STA & 0X80) == 0)
	{
		if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		{
			if(ultra_L2.CAPTURE_STA & 0x40)
			{
				if((ultra_L2.CAPTURE_STA & 0x02) == 0x02)
				{
					ultra_L2.CAPTURE_STA = 0;
					TIM_OC4PolarityConfig(TIM3, TIM_ICPolarity_Rising);
					ultra_L2.CAPTURE_VAL = 0xFFFFFFFF;
				}
				else ultra_L2.CAPTURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM3, TIM_IT_CC4) != RESET)
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_CC4);
			if(ultra_L2.CAPTURE_STA & 0x40)
			{
				ultra_L2.CAPTURE_DOWNVAL = TIM_GetCapture4(TIM3);
				ultra_L2.CAPTURE_VAL = ultra_L2.CAPTURE_DOWNVAL - ultra_L2.CAPTURE_UPVAL + (ultra_L2.CAPTURE_STA&0X3F)*0XFFFF;
				ultra_L2.DIS = ultra_L2.CAPTURE_VAL * 340.0f / 2000.0f;
				ultra_L2.DIS = Limit(ultra_L2.DIS,0,2550);
				ultra_L2.CAPTURE_STA = 0;
				Ultrasonic_Filter(&Ultrasonic_L2_Filter,ultra_L2.DIS,7,&UL_DIS_F.L2);
				TIM_OC4PolarityConfig(TIM3, TIM_ICPolarity_Rising);
			}
			else
			{
				ultra_L2.CAPTURE_UPVAL = TIM_GetCapture4(TIM3);
				ultra_L2.CAPTURE_STA |= 0x40;
				TIM_OC4PolarityConfig(TIM3, TIM_ICPolarity_Falling);
			}
		}
	}
	
//----------------------------------------------------------------------------------------------------------------------------
	if((ultra_R1.CAPTURE_STA & 0X80) == 0)
	{
		if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		{
			if(ultra_R1.CAPTURE_STA & 0x40)
			{
				if((ultra_R1.CAPTURE_STA & 0x02) == 0x02)
				{
					ultra_R1.CAPTURE_STA = 0;
					TIM_OC1PolarityConfig(TIM3, TIM_ICPolarity_Rising);
					ultra_R1.CAPTURE_VAL = 0xFFFFFFFF;
				}
				else ultra_R1.CAPTURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
			if(ultra_R1.CAPTURE_STA & 0x40)
			{
				ultra_R1.CAPTURE_DOWNVAL = TIM_GetCapture1(TIM3);
				ultra_R1.CAPTURE_VAL = ultra_R1.CAPTURE_DOWNVAL - ultra_R1.CAPTURE_UPVAL + (ultra_R1.CAPTURE_STA&0X3F)*0XFFFF;
				ultra_R1.DIS = ultra_R1.CAPTURE_VAL * 340.0f / 2000.0f;
				ultra_R1.DIS = Limit(ultra_R1.DIS,0,2550);
				ultra_R1.CAPTURE_STA = 0;
				Ultrasonic_Filter(&Ultrasonic_R1_Filter,ultra_R1.DIS,7,&UL_DIS_F.R1);
				TIM_OC1PolarityConfig(TIM3, TIM_ICPolarity_Rising);
			}
			else
			{
				ultra_R1.CAPTURE_UPVAL = TIM_GetCapture1(TIM3);
				ultra_R1.CAPTURE_STA |= 0x40;
				TIM_OC1PolarityConfig(TIM3, TIM_ICPolarity_Falling);
			}
		}
	}
	
//------------------------------------------------------------------------------------------------------------------------------
	if((ultra_R2.CAPTURE_STA & 0X80) == 0)
	{
		if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		{
			if(ultra_R2.CAPTURE_STA & 0x40)
			{
				if((ultra_R2.CAPTURE_STA & 0x02) == 0x02)
				{
					ultra_R2.CAPTURE_STA = 0;
					TIM_OC2PolarityConfig(TIM3, TIM_ICPolarity_Rising);
					ultra_R2.CAPTURE_VAL = 0xFFFFFFFF;
				}
				else ultra_R2.CAPTURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);
			if(ultra_R2.CAPTURE_STA & 0x40)
			{
				ultra_R2.CAPTURE_DOWNVAL = TIM_GetCapture2(TIM3);
				ultra_R2.CAPTURE_VAL = ultra_R2.CAPTURE_DOWNVAL - ultra_R2.CAPTURE_UPVAL + (ultra_R2.CAPTURE_STA&0X3F)*0XFFFF;
				ultra_R2.DIS = ultra_R2.CAPTURE_VAL * 340.0f / 2000.0f;
				ultra_R2.DIS = Limit(ultra_R2.DIS,0,2550);
				ultra_R2.CAPTURE_STA = 0;
				Ultrasonic_Filter(&Ultrasonic_R2_Filter,ultra_R2.DIS,7,&UL_DIS_F.R2);
				TIM_OC2PolarityConfig(TIM3, TIM_ICPolarity_Rising);
			}
			else
			{
				ultra_R2.CAPTURE_UPVAL = TIM_GetCapture2(TIM3);
				ultra_R2.CAPTURE_STA |= 0x40;
				TIM_OC2PolarityConfig(TIM3, TIM_ICPolarity_Falling);
			}
		}
	}
//------------------------------------------------------------------------------------------------------------------------------

	TIM_ClearITPendingBit(TIM3, TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4 ); //����жϱ�־λ	
}

void TIM1_BRK_TIM9_IRQHandler(void)
{
	if((ultra_F1.CAPTURE_STA & 0x80) == 0)
	{
		if(TIM_GetITStatus(TIM9, TIM_IT_Update) != RESET)
		{
			if(ultra_F1.CAPTURE_STA & 0x40)
			{
				if((ultra_F1.CAPTURE_STA & 0x02) == 0x02)
				{
					ultra_F1.CAPTURE_STA = 0;
					TIM_OC1PolarityConfig(TIM9, TIM_ICPolarity_Rising);
					ultra_F1.CAPTURE_VAL = 0xFFFFFFFF;
				}
				else ultra_F1.CAPTURE_STA++;			
			}
		}
		if(TIM_GetITStatus(TIM9, TIM_IT_CC1) != RESET)
		{
			TIM_ClearITPendingBit(TIM9, TIM_IT_CC1);
			if(ultra_F1.CAPTURE_STA & 0x40)
			{
				ultra_F1.CAPTURE_DOWNVAL = TIM_GetCapture1(TIM9);
				ultra_F1.CAPTURE_VAL = ultra_F1.CAPTURE_DOWNVAL - ultra_F1.CAPTURE_UPVAL + (ultra_F1.CAPTURE_STA&0X3F)*0XFFFF;
				ultra_F1.DIS = ultra_F1.CAPTURE_VAL * 340.0f / 2000.0f;
				ultra_F1.DIS = Limit(ultra_F1.DIS,0,2550);
				ultra_F1.CAPTURE_STA = 0;		                                    //�����־λ����
				Ultrasonic_Filter(&Ultrasonic_F1_Filter,ultra_F1.DIS,7,&UL_DIS_F.F1);
				TIM_OC1PolarityConfig(TIM9, TIM_ICPolarity_Rising);                 //����Ϊ�����ز���		  
			}
			else
			{
				ultra_F1.CAPTURE_UPVAL = TIM_GetCapture1(TIM9);		                //��ȡ����������
				ultra_F1.CAPTURE_STA |= 0X40;		                                //����Ѳ���������
				TIM_OC1PolarityConfig(TIM9, TIM_ICPolarity_Falling);                //����Ϊ�½��ز���
			}
		}
	}
//------------------------------------------------------------------------------------------------------------------------------
	if((ultra_F2.CAPTURE_STA & 0X80) == 0)
	{
		if(TIM_GetITStatus(TIM9, TIM_IT_Update) != RESET)
		{
			if(ultra_F2.CAPTURE_STA & 0x40)
			{
				if((ultra_F2.CAPTURE_STA & 0x02) == 0x02)
				{
					ultra_F2.CAPTURE_STA = 0;
					TIM_OC2PolarityConfig(TIM9, TIM_ICPolarity_Rising);
					ultra_F2.CAPTURE_VAL = 0xFFFFFFFF;
				}
				else ultra_F2.CAPTURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM9, TIM_IT_CC2) != RESET)
		{
			TIM_ClearITPendingBit(TIM9, TIM_IT_CC2);
			if(ultra_F2.CAPTURE_STA & 0x40)
			{
				ultra_F2.CAPTURE_DOWNVAL = TIM_GetCapture2(TIM9);
				ultra_F2.CAPTURE_VAL = ultra_F2.CAPTURE_DOWNVAL - ultra_F2.CAPTURE_UPVAL + (ultra_F2.CAPTURE_STA&0X3F)*0XFFFF;
				ultra_F2.DIS = ultra_F2.CAPTURE_VAL * 340.0f / 2000.0f;
				ultra_F2.DIS = Limit(ultra_F2.DIS,0,2550);
				ultra_F2.CAPTURE_STA = 0;
				Ultrasonic_Filter(&Ultrasonic_F2_Filter,ultra_F2.DIS,7,&UL_DIS_F.F2);
				TIM_OC2PolarityConfig(TIM9, TIM_ICPolarity_Rising);
			}
			else
			{
				ultra_F2.CAPTURE_UPVAL = TIM_GetCapture2(TIM9);
				ultra_F2.CAPTURE_STA |= 0x40;
				TIM_OC2PolarityConfig(TIM9, TIM_ICPolarity_Falling);
			}
		}
	}
	
//------------------------------------------------------------------------------------------------------------------------------

	
	TIM_ClearITPendingBit(TIM9, TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2); //����жϱ�־λ	
}

void Delay_ULTRA(unsigned char n)
{
	unsigned int i,j;
	for(j = 0;j < n;j++)
	{
		for(i=0;i<40;i++);
	}
}


void Ultrasonic_Get_Distance(void)
{
	 TRIG_L1 
	 TRIG_L2 
	 TRIG_R1 					//6��������Trig����15us�ߵ�ƽ����
   TRIG_R2
	 TRIG_F1
	 TRIG_F2
	
}

void Ultrasonic_Filter(UltrasonicFilter_Struct *filterStruct,float newDatas,unsigned char FilterNum,u16 *Out)
{
	unsigned int i = 0;
	float FilterSum  = 0;
	static unsigned short int max,min;
	
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
		filterStruct->Cache = FilterSum/(FilterNum-2);
	}
	
	if(filterStruct->Complete==1)
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
		filterStruct->Complete=1;
		filterStruct->Count = 0;
	}
}


