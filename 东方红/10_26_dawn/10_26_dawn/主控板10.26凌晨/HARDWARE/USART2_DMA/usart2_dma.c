#include "usart2_dma.h"

u8 rec_data_u2[U2_DATA_LEN]={0};   // 接收数据
u8 send_data_u2[U2_DATA_LEN]={0};  // 发送数据

float yaw=0;
short yaw_H=0;
short yaw_L=0;
short yaw_temp=0;

void USART2_Init(int Baud)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream6_IRQn;    //DMA1的通道6
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  //USART2_TX
	DMA_DeInit(DMA1_Stream6);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);//外设地址
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)send_data_u2;//内存地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//dma传输方向
	DMA_InitStructure.DMA_BufferSize = U2_DATA_LEN;//设置DMA在传输时缓冲区的长度
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//设置DMA的外设递增模式，一个外设
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//设置DMA的内存递增模式

	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//外设数据字长
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;//内存数据字长
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//设置DMA的传输模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;	//设置DMA的优先级别
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;    //指定如果FIFO模式或直接模式将用于指定的流 ： 不使能FIFO模式
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;  	//指定了FIFO阈值水平
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; //指定的Burst转移配置内存传输
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; //指定的Burst转移配置外围转移 */

	DMA_Init(DMA1_Stream6,&DMA_InitStructure);//配置DMA1的通道
	DMA_ITConfig(DMA1_Stream6,DMA_IT_TC,ENABLE);//使能中断

  USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);//使能串口的DMA发送接口 
	DMA_Cmd(DMA1_Stream6,DISABLE);//关闭通道
  //USART2_RX
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);//DMA通道配置
	
	DMA_DeInit(DMA1_Stream5);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);//外设地址
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rec_data_u2;//内存地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//dma传输方向
	DMA_InitStructure.DMA_BufferSize = U2_DATA_LEN;//设置DMA在传输时缓冲区的长度
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//设置DMA的外设递增模式，一个外设
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//设置DMA的内存递增模式
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//外设数据字长
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//内存数据字长
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//设置DMA的传输模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//设置DMA的优先级别
	
	DMA_Init(DMA1_Stream5, &DMA_InitStructure);//配置DMA1的通道	
	DMA_Cmd(DMA1_Stream5,ENABLE);//使能通道

	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);//使能串口的DMA接收

  //初始化串口参数
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStructure.USART_BaudRate = Baud;
	//初始化串口
  USART_Init(USART2,&USART_InitStructure);
	//配置中断
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;               //通道设置为串口中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //中断占先等级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;              //中断响应优先级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //打开中断
  NVIC_Init(&NVIC_InitStructure);

	//采用DMA方式发送
	USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
	//采用DMA方式接收
	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);

	//中断配置
	USART_ITConfig(USART2,USART_IT_TC,DISABLE);
	USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);
	USART_ITConfig(USART2,USART_IT_TXE,DISABLE);
	USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);
   
  USART_Cmd(USART2, ENABLE);//启动串口

  //设置IO口
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	  //管脚模式:输出口
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //类型:推挽模式
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	  //上拉下拉设置
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	  //管脚模式:输入口
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//上拉下拉设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/*
********************************************************************************************************************
*                  void  USART2_IRQHandler(void)
*
*Description : 串口2发送函数 
*Arguments   : BufferSRC:发送数据存放地址；BufferSize:发送数据字节数
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void USART2_DMATransfer(uint32_t *BufferSRC, uint32_t BufferSize)//UASRT DMA发送设置
{
	DMA_ClearFlag(DMA1_Stream6,DMA_FLAG_TCIF6);
	DMA1_Stream6->NDTR = BufferSize;    //配置BUFFER大小
	DMA1_Stream6->M0AR = (uint32_t)BufferSRC;   //配置地址
	DMA1_Stream6->CR |= DMA_SxCR_EN;	//打开DMA,开始发送
}



/*
********************************************************************************************************************
*                  void  USART2_IRQHandler(void)
*
*Description : 串口2接收函数 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void USART2_IRQHandler(void)
{
	uint16_t t;
	if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)  //接收中断
	{
		t= USART_ReceiveData(USART2);//读取数据 注意：这句必须要，否则不能够清除中断标志位。
		if((rec_data_u2[0]==0X55)&&(rec_data_u2[1]==0X53))
			{
			yaw_H=rec_data_u2[7];
			yaw_L=rec_data_u2[6];
			yaw_temp=(yaw_H<<8)|yaw_L;
			yaw=yaw_temp/32768.0f*180.0f;
			}
	 USART_ClearITPendingBit(USART2, USART_IT_IDLE);         //清除中断标志
	 DMA1_S5_Reset();                                       //恢复DMA指针，等待下一次的接收
   }
	else if(USART_GetITStatus(USART2, USART_IT_TC) != RESET)
	{
		USART_ClearITPendingBit(USART2, USART_IT_TC);
		DMA1_Stream6->CR &= (uint32_t)(~DMA_SxCR_EN);   //关闭DMA,发送完成
	}
}

/*
********************************************************************************************************************
*                  void DMA1_Stream6_IRQHandler(void)
*
*Description : 串口2发送中断函数 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void DMA1_Stream6_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_Stream6,DMA_IT_TCIF6) != RESET)
    {
        /* 清除标志位 */
        DMA_ClearFlag(DMA1_Stream6,DMA_IT_TCIF6);
        /* 关闭DMA */
        DMA_Cmd(DMA1_Stream6,DISABLE);
        /* 打开发送完成中断,确保最后一个字节发送成功 */
        USART_ITConfig(USART2,USART_IT_TC,ENABLE);
    }
}

/*
********************************************************************************************************************
*                  void DMA1_S5_Reset(void)
*
*Description : 串口2接收重置 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/

void DMA1_S5_Reset(void)//DMA1_Stream6 接收重置
{ 
	DMA_ClearFlag(DMA1_Stream5,DMA_IT_TCIF5|DMA_FLAG_HTIF5|DMA_FLAG_TEIF5|DMA_FLAG_DMEIF5|DMA_FLAG_FEIF5);  
	
	DMA_Cmd(DMA1_Stream5,DISABLE); //关闭USART2 TX DMA1 所指示的通道

 	//DMA_SetCurrDataCounter(DMA1_Channel5,Uart1_DMA_Len);//DMA通道的DMA缓存的大小
	DMA1_Stream5->NDTR = U2_DATA_LEN;
 	//DMA_Cmd(DMA1_Channel5, ENABLE);                    
	DMA_Cmd(DMA1_Stream5,ENABLE); //使能USART2 TX DMA1 所指示的通道
	/* 清除标志位 */
   
}

void Uart2Send(unsigned char *p_data, unsigned int uiSize)//串口2数据发送
{    
    unsigned int i;
    for(i = 0; i < uiSize; i++)
    {
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);//判断数据发送是否完成
        USART_SendData(USART2, *p_data++);//串口2数据发送        
    }
    while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
}

