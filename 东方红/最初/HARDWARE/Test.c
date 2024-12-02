#include "stm32f4xx.h"
#include "Test.h"
#include "delay.h"
#include "oled.h"
#include "Ultrasonic.h"
#include "motor.h"

extern int start_flag;
extern int Angle_PWM;
extern float yaw;
extern int Move_flag;

//void Test_Basics()
//{
//	static int x=0;
//	LED1_ON;
//	LED2_ON;
//	LED3_ON;
//	delay_ms(200);
//	LED1_OFF;
//	LED2_OFF;
//	LED3_OFF;
//	delay_ms(200);
//	OLED_ShowString(0,0,(void *)"Test",12);
//	OLED_ShowIntNum(0,16,x,3,12);
//	OLED_Refresh_Gram();
//	if(KEY1==0)
//	{
//		delay_ms(10);
//		{
//			x++;
//		}
//	}
//	if(KEY2==0)
//	{
//		delay_ms(10);
//		{
//			x--;
//		}
//	}
//	if(KEY3==0)
//	{
//		delay_ms(10);
//		{
//			x+=5;
//		}
//	}
//	if(KEY4==0)
//	{
//		delay_ms(10);
//		{
//			x-=5;
//		}
//	}
//	
//}


void Test_Ultrasonic()
{
	TRIG_L1 		
	TRIG_L2 		
	TRIG_R1 		
	TRIG_R2 		
	TRIG_F1 		
	TRIG_F2 		
	OLED_Show3FNum(0,0,Ultra_F_L,4,2,12);
	OLED_Show3FNum(0,12,Ultra_F_R,4,2,12);
	OLED_Show3FNum(0,24,Ultra_M_L,4,2,12);//zhong,84
	OLED_Show3FNum(64,0,Ultra_M_R,4,2,12);//qian,149
	OLED_Show3FNum(64,12,Ultra_B_L,4,2,12);
	OLED_Show3FNum(64,24,Ultra_B_R,4,2,12);
	OLED_Refresh_Gram();
	delay_ms(10);
}
////ECHO1	TIM5
////ECHO2	TIM11
////ECHO3	TIM5
////ECHO4	TIM13
////ECHO5	TIM11
////ECHO6	TIM13

//void OLED_Encoder_Text()
//{
//	OLED_ShowIntNum(0,0,PWM_speedB,8,12);
//	
//	OLED_ShowIntNum(0,12,Encoder_CNT[0],8,12);
//	OLED_Show3FNum(0,24,Encoders.speedA,5,2,12);
//	OLED_Show3FNum(0,36,Encoders.disA ,5,2,12);
//	
//	OLED_ShowIntNum(72,0,PWM_speedA,8,12);
//	OLED_ShowIntNum(72,12,Encoder_CNT[1],8,12);
//	OLED_Show3FNum(72,24,Encoders.speedB,5,2,12);
//	OLED_Show3FNum(72,36,Encoders.disB,5,2,12);
//	
//	OLED_Show3FNum(0,0,Encoder_Check_Time,6,3,12);
//	
//	OLED_Refresh_Gram();
//}

//void OLED_TuoLuo_Text()
//{
//	OLED_Show3FNum(0,0,yaw,5,2,12);
//	OLED_Show3FNum(0,12,Ultra_M_R,4,2,12);
//	OLED_Show3FNum(72,12,Ultra_M_L,4,2,12);
//	OLED_ShowIntNum(0,36,Move_flag,3,12);
////	OLED_ShowIntNum(72,36,Move_flag,3,12);
////	OLED_Show3FNum(0,48,Total_distance,5,2,12);
//	
//	OLED_Refresh_Gram();
//}


