#include "WT1.h"

void WT1_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);

	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource2,GPIO_AF_UART5);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12,GPIO_AF_UART5);

	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl =  USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(UART5, &USART_InitStruct);
	
	USART_Cmd(UART5, ENABLE);  //使能串口5
	
	USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);
	NVIC_InitStruct.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=  1;
	NVIC_Init(&NVIC_InitStruct);


}



void sendcmd_uart5(unsigned char *cmd)
{
	u8 i;
	for(i=0;i<3;i++)
	{
		USART_SendData(USART2,cmd[i]);
		USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
	}
	
}


	 int16_t usData[4];
	 int16_t usData1[4];
	 int16_t usData2[4];
void CopeSerial2Data(unsigned char ucData)
{

	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
 
	ucRxBuffer[ucRxCnt++]=ucData;	
	if (ucRxBuffer[0]!=0x55) 
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<8) {return;}
	else
	{
		switch(ucRxBuffer[1])
		{
			
			case 0x53:
			usData[0] = ((uint16_t)ucRxBuffer[3] << 8) | (uint16_t)ucRxBuffer[2];
			usData[1] = ((uint16_t)ucRxBuffer[5] << 8) | (uint16_t)ucRxBuffer[4];
			usData[2] = ((uint16_t)ucRxBuffer[7] << 8) | (uint16_t)ucRxBuffer[6];
			//OLED_Show3FNum(1,1,usData[0]/32768.0*180,3,3,12);//显示有符号浮点数字
			//OLED_Show3FNum(1,15,usData[1]/32768.0*180,3,3,12);//显示有符号浮点数字

			break;
			case 0x52:	//jiaosudu
			usData1[0] = ((uint16_t)ucRxBuffer[3] << 8) | (uint16_t)ucRxBuffer[2];
			usData1[1] = ((uint16_t)ucRxBuffer[5] << 8) | (uint16_t)ucRxBuffer[4];
			usData1[2] = ((uint16_t)ucRxBuffer[7] << 8) | (uint16_t)ucRxBuffer[6];

			
			break;
			case 0x51:
			usData2[0] = ((uint16_t)ucRxBuffer[3] << 8) | (uint16_t)ucRxBuffer[2];
			usData2[1] = ((uint16_t)ucRxBuffer[5] << 8) | (uint16_t)ucRxBuffer[4];
			usData2[2] = ((uint16_t)ucRxBuffer[7] << 8) | (uint16_t)ucRxBuffer[6];
			
//			OLED_Show3FNum(1,29,usData2[0]/32768.0*16*9.8,3,3,12);//显示有符号浮点数字
//			
			break;
 
		}

		ucRxCnt=0;
	}
}
void UART5_IRQHandler(void)
{
	unsigned char i;
	if(USART_GetFlagStatus(UART5,USART_IT_RXNE) !=RESET)
	{
		USART_ClearITPendingBit(UART5,USART_IT_RXNE);
		i = USART_ReceiveData(UART5);
		CopeSerial2Data(i);
		//OLED_ShowNum(1,35,i,10,12);//显示数字
		//OLED_Refresh_Gram();
		//delay_ms(10);
		
	}
}

