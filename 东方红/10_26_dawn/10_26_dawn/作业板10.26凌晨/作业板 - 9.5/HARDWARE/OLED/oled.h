#ifndef __OLED_H
#define __OLED_H			  	 

#include "sys.h"
#include "stdlib.h"	    

 /*
******************************************************************************************************************
*                                            CONSTANTS & MACROS
******************************************************************************************************************
*/    						  
//-----------------OLED端口定义------------------------------------------------------- 		
//D0/SCK--PB12，D1/MOSI--PB13，CS--PB15，DC--PB14  RST--3.3V
#define OLED_CS 	                          	PBout(15) 		//OLED的CS
#define OLED_DC	                            	PBout(14) 		//OLED的DC口
#define OLED_SCK 	                          	PBout(12) 		//OLED的D0口
#define OLED_MOSI	                            PBout(13) 		//OLED的D1
#define OLED_CMD  	                               0			//写命令
#define OLED_DATA 	                               1			//写数据

/*
******************************************************************************************************************
*                                            FUNCTION PROTOTYPES
*                                                   OLED控制用函数
******************************************************************************************************************
*/
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);//开启OLED显示  
void OLED_Display_Off(void);//关闭OLED显示  
void OLED_Refresh_Gram(void);//更新显存到OLED	(在每一次显示的结尾一定要加，实时刷新，不然不实时刷新就会一直黑屏)	   
							   		    
void OLED_Init(void);//OLED初始化函数
void OLED_Clear(void);//清屏函数
void OLED_DrawPoint(u8 x,u8 y,u8 t);//画点函数
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);//填充
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);//显示字符
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);//显示数字
void OLED_ShowIntNum(u8 x,u8 y,int32_t num,u8 len,u8 size);//显示有符号数字
void OLED_Show3FNum(u8 x,u8 y,float num,u8 lenf,u8 lenb,u8 size);//显示有符号浮点数字
void OLED_ShowString(u8 x,u8 y,const u8 *p,u16 size);//显示字符串 
void OLED_ShowCHinese(u8 x,u8 y,u8 no);//显示汉字
#endif  
	 
