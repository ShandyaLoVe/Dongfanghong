//#include "stm32f4xx.h"
//#include "usart_my.h"

////int 0000 0000 0000 0000		0x0000
////char 0000 0000						0x00

//u8 xxx=0;

//void USART1_IRQHandler()
//{
//	u8 com_data;
//	if( USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)  	   //接收中断  
//	{
//		USART_ClearITPendingBit(USART1,USART_IT_RXNE);   //清除中断标志
//		
//		com_data = USART_ReceiveData(USART1);
//		xxx=com_data;
//		
//	}
//}


//void USART1_Init()//PB6 USART1_TX  PB7 USART1_RX
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//  USART_InitTypeDef USART_InitStructure;
//  NVIC_InitTypeDef NVIC_InitStructure;
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //使能 GPIOA 时钟
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能 USART1 时钟
//	
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_USART1); //PB6 复用为USART1
//  GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1); //PB7 复用为USART1
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
//  GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化 PB6， PB7
//	
//	USART_InitStructure.USART_BaudRate = 115200;
//  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为 8 位数据格式
//  USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
//  USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
//  USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
//  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式
//  USART_Init(USART1, &USART_InitStructure); //初始化串口
//	
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
//	
//	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级 2
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority =2; //响应优先级 2
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ 通道使能
//  NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化 VIC 寄存器
//	
//	USART_Cmd(USART1, ENABLE); //使能串口 
//	
//	USART_ClearFlag(USART1,USART_FLAG_TC);
//}


