#include "SW.h"
/*
****************************************************************************
*                  void key_init(void)
*Description : ������ʼ��
*Arguments   : none
*Returns     : none
*Notes       : none
****************************************************************************
*/
void key_init(void)
{
	GPIO_InitTypeDef	GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);		//ʹ��IOʱ��

	GPIO_InitStruct.GPIO_Mode	=	GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd	=	GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Pin	=	KEY1_Pin | KEY2_Pin;
	GPIO_InitStruct.GPIO_Speed	=	GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,  &GPIO_InitStruct);
	
}
/*
****************************************************************************
*                  u8   key_scan(u8 mode)
*Description : ����ɨ�躯��
*Arguments   : u8 mode
*Returns     : �����������
*Notes       : mode=1	����	mode = 0	��֧������
****************************************************************************
*/
u8   key_scan(u8 mode)
{
	static u8 key_up = 1;
	
	if(mode)			//mode==1ʱ,֧������
		key_up = 1;
	
	if( key_up&&(KEY1==0||KEY2==0) )
	{
		delay_ms(10);
		key_up = 0;
		if(KEY1==0)		return KEY1_PRES;
		if(KEY2==0)		return KEY2_PRES;
	
	}else if(KEY1==1&&KEY2==1)
		key_up = 1;
	
	return 0;
}

