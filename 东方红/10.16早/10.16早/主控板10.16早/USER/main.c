#include "Move_Command.h"
#include "usart4_dma.h"

unsigned char data_yaw[5]={0xFF,0xAA,0x76,0x00,0x00};
extern int Move_flag;

float out=0;
float start_yaw=0,end_yaw=0;
int a=0;
int start_flag=0;
int task=0;
int key=0;

char send[50] = {0};

u8 Flag_Step=0;
u8 time_5ms=0;//中断判断标志位
u8 time_7ms=0;
u8 time_10ms=0;
u8 time_20ms=0;
u8 time_50ms=0;
u8 time_100ms=0;


int main()
{

	  delay_init(168);
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	  Key_Init();
	  OLED_Init();
////----------------------------------------------------------------------
	  Light_Init();
	  USART1_Init(115200);
	  USART2_Init(9600);
	  UART4_Init(115200);
	  Uart2Send(data_yaw,5);
////----------------------------------------------------------------------
	  Ultrasonic_Init();
		Motor_Init();
		TIM5_EncoderA_Init(0xFFFF, 1-1);
		TIM2_EncoderB_Init(0xFFFF, 1-1);
		TIM14_Speed_Check_Init();
////---------------------------------------------------------------------- 
	  System_TIM7_Init();

	while(1)
	{
			
//	    OLED_Show3FNum(0,0,task,3,3,12);
//		OLED_Show3FNum(0,12,yaw,3,3,12);
//		OLED_Show3FNum(0,24, start_work,3,3,12);      //4
//		OLED_Show3FNum(50,24,PEin(5),3,3,12);      //4
//		OLED_Show3FNum(0,36,PEin(6),3,3,12);
//		OLED_Show3FNum(0,0, Encoders.disA,3,3,12);       //3
//		OLED_Show3FNum(60,0, Encoders.disB,3,3,12);       //3
		
		
//		TRIG_1
//		TRIG_2
//		TRIG_3  
//		TRIG_4
	
		
		
    OLED_Show3FNum(0, 0,  Ultra_F_L,3,3,12);     //3   前
	  OLED_Show3FNum(60,0,  Ultra_B_L,3,3,12);     //4   左
	  OLED_Show3FNum(0, 24, Ultra_F_R,3,3,12);     //1   后
	  OLED_Show3FNum(60,24, Ultra_B_R,3,3,12);     //2   右
		
		
		
	  OLED_Refresh_Gram();
	 /*---按键调整函数---*/
	  key=Key_Scan();

	 /*入垄角度初始化*/
	 if(key==KEY1_PRES)
	{
		start_yaw=yaw;
		Encoder_Clear();
		start_flag=1;
		Move_flag=1;
		
	}
				
	if(key==KEY2_PRES)
	{	  
       USART_SendData(USART1,start_work);
	}
	if(key==KEY3_PRES)
	{	  
       USART_SendData(USART1,start_work);
	}
	if(key==KEY4_PRES)
	{
		Motor_TB_Set(500,500,500,500);
//		PCout(12)=0;
//		PAout(12)=0;
		
	}
        
        /*任务筛选函数*/
   if(time_10ms >= 10)//控制周期修改为10ms
     {
        time_10ms = 0;
        if(start_flag==1)//任务选取函数
          {

			   Get_init_flag();
               Get_flag();
          }		
      }
	if(time_5ms >= 5)//控制周期修改为10ms
      {
		    VOFA4_send(send,0,yaw);
        time_5ms = 0;
			}
		
        /*上位机测试函数，一般不打开*/
    if(time_20ms >= 20)
      {
          time_20ms = 0;
			

      }
        
  }
}

		
//		OLED_Show3FNum(0,0, Ultra_F_L,3,3,12);      //3   前
//	  OLED_Show3FNum(60,0, Ultra_B_L,3,3,12);     //4   左
//	  OLED_Show3FNum(0,24, Ultra_F_R,3,3,12);     //1   后
//	  OLED_Show3FNum(60,24, Ultra_B_R,3,3,12);    //2   右
//    E6        左面		
//    E5        右面		

	