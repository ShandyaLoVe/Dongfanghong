#include "sys.h"
#include "openmv.h"
#include "SW.h" 

unsigned char d=0;
int error=0;
int tree=0;
int t,i=0;
int fornt=0;
int x,y;
float angle1,angle2;
float omgra=360;
int leftover=0;
int key=0;










extern unsigned int Timer10ms;

int main(void)
{
	delay_init(168);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();//OLED初始化函数
	uart_init(115200);
	servo_init();
	Timer_Init();
	USART1_Init(115200);
	Motor_Init();
	sevo1_angle(135);
	key_init();
	OLED_Clear();//清屏函数
	System_TIM7_Init();
	
	//      正     上    1
	//      正		 下    4
//	Motor_TB_Set(0,0,0,0); 
	



  while(1)
  {
//		fornt = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6);
		OLED_Show3FNum(0, 0,  tree_colour,3,3,12); 
//		OLED_Show3FNum(60, 0,  key ,3,3,12);
		OLED_Show3FNum(60, 0,  work_state ,3,3,12);
//		OLED_Show3FNum(0, 0,  time_10ms ,3,3,12);	
		OLED_Show3FNum(0, 24,  fornt ,3,3,12);
//		delay_ms(300);
	  OLED_Refresh_Gram();
		
		key=key_scan(1);
		
		if(key==KEY1_PRES)
		{	  
//			Motor_TB_Set(0,0,0,100); 
				Motor_TB_Set(1000,0,0,1000);
//					delay_ms(30);
//					Motor_TB_Set(0,0,0,0);
			
			
		
		}
		if(key==KEY2_PRES)
		{	  
			
			
			
			Motor_TB_Set(0,0,0,0); 
//			OLED_Show3FNum(0, 0,  time_10ms ,3,3,12);
//			delay_ms(300);
//			OLED_Refresh_Gram();
		}	
		
		
		if(time_10ms%10 && work_state==1)
			{
//				while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)==1);fornt
				while(1)
				{
					if((GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)) == 1)   break;	
				}


				if(tree_colour==green_tree)
				{
					Motor_TB_Set(1000,0,0,0);
					work_state=0;
					delay_ms(60);
					Motor_TB_Set(0,0,0,0);
				}
				else if(tree_colour==red_tree)
				{
					//while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)==0);
					Motor_TB_Set(1000,0,0,1000); 				
					work_state=0;
					delay_ms(60);
					Motor_TB_Set(0,0,0,0);

				}
			
			}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
// 	  if(time_10ms%10)
////	  if(time_10ms%10&&work_state==1)
//	  {
//  
//			if(tree_colour==green_tree)
//			{
//				Motor_TB_Set(0,0,0,600);
//				delay_ms(300);
//			}
//			else if(tree_colour==red_tree)
//			{
//				Motor_TB_Set(600,0,0,600); 
//				delay_ms(300);
//			}
//				work_state=0;
//				Motor_TB_Set(0,0,0,0); 

//			Motor_TB_Set(770,770,770,600); 
		}

	


	
	
	
}
//	openmv      串口1
//	上下通信		串口2
//通过两侧光电对管扫到树，主控板对作业板发送信号start_work
//start_work是准备喷水信号
















//				if(tree_colour==green_tree)
//				{
//					Motor_TB_Set(0,0,0,600);
//					while(1)
//					{
//						if(!(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)))
//						{
//							work_state=0;
//							Motor_TB_Set(0,0,0,0); 
//							break;
//						}
//					}
//				}
//				else if(tree_colour==red_tree)
//				{
//					//while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)==0);
//					Motor_TB_Set(600,0,0,600); 
//					while(1)
//					{
//						if(!(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)))
//						{
//							work_state=0;
//							Motor_TB_Set(0,0,0,0); 
//							break;
//						}
//					}

//				}



//				if(tree_colour==green_tree)
//				{
//					Motor_TB_Set(0,0,0,600);
//					work_state=0;
//					delay_ms(30);
//					Motor_TB_Set(0,0,0,0);
//				}
//				else if(tree_colour==red_tree)
//				{
//					//while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)==0);
//					Motor_TB_Set(600,0,0,600); 				
//					work_state=0;
//					delay_ms(30);
//					Motor_TB_Set(0,0,0,0);

//				}







