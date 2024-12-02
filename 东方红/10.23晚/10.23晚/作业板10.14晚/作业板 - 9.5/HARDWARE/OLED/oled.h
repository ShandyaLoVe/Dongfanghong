#ifndef __OLED_H
#define __OLED_H			  	 

#include "sys.h"
#include "stdlib.h"	    

 /*
******************************************************************************************************************
*                                            CONSTANTS & MACROS
******************************************************************************************************************
*/    						  
//-----------------OLED�˿ڶ���------------------------------------------------------- 		
//D0/SCK--PB12��D1/MOSI--PB13��CS--PB15��DC--PB14  RST--3.3V
#define OLED_CS 	                          	PBout(15) 		//OLED��CS
#define OLED_DC	                            	PBout(14) 		//OLED��DC��
#define OLED_SCK 	                          	PBout(12) 		//OLED��D0��
#define OLED_MOSI	                            PBout(13) 		//OLED��D1
#define OLED_CMD  	                               0			//д����
#define OLED_DATA 	                               1			//д����

/*
******************************************************************************************************************
*                                            FUNCTION PROTOTYPES
*                                                   OLED�����ú���
******************************************************************************************************************
*/
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);//����OLED��ʾ  
void OLED_Display_Off(void);//�ر�OLED��ʾ  
void OLED_Refresh_Gram(void);//�����Դ浽OLED	(��ÿһ����ʾ�Ľ�βһ��Ҫ�ӣ�ʵʱˢ�£���Ȼ��ʵʱˢ�¾ͻ�һֱ����)	   
							   		    
void OLED_Init(void);//OLED��ʼ������
void OLED_Clear(void);//��������
void OLED_DrawPoint(u8 x,u8 y,u8 t);//���㺯��
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);//���
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);//��ʾ�ַ�
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);//��ʾ����
void OLED_ShowIntNum(u8 x,u8 y,int32_t num,u8 len,u8 size);//��ʾ�з�������
void OLED_Show3FNum(u8 x,u8 y,float num,u8 lenf,u8 lenb,u8 size);//��ʾ�з��Ÿ�������
void OLED_ShowString(u8 x,u8 y,const u8 *p,u16 size);//��ʾ�ַ��� 
void OLED_ShowCHinese(u8 x,u8 y,u8 no);//��ʾ����
#endif  
	 
