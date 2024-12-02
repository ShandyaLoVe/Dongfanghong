//    OLED_Show3FNum(0,0, Ultra_F_L,3,3,12);      //3   Ç°
//	  OLED_Show3FNum(60,0, Ultra_B_L,3,3,12);     //4   ×ó
//	  OLED_Show3FNum(0,24, Ultra_F_R,3,3,12);     //1   ºó
//	  OLED_Show3FNum(60,24, Ultra_B_R,3,3,12);    //2   ÓÒ
		

#include "Move_Command.h"
#include "math.h"

extern float fix;
extern int task;
extern float start_yaw;
extern float end_yaw;
extern int flag_speed;
extern u8 falg_ultrastop;
extern u8 flag_1;
extern u8 flag_2;
u8 flag_open=0;

int Move_flag=0;
int Step_flag=0;
int state=0;
int i;

float my_abs(float x)
{
	if (x>=0)
	{
		return x;
	}
	else
        return -x;
}

void Get_init_flag(void)
{
   if(Move_flag==1)
   {
	   	pid_yaw_x_Init();
			pid_yaw_y_Init();
	    pid_ultra_1_Init();
			pid_ultra_2_Init();
	    Encoder_Clear();
	    Move_flag=2;
	    task=0;
   }
      if(Move_flag==5)    //½øÈë1ºÅ 
   {
	   	pid_yaw_x_Init();
	    pid_ultra_1_Init();
	    pid_ultra_2_Init();
	    Encoder_Clear();
	    Move_flag=6;
   }
      if(Move_flag==9)    //³ö1ºÅ
   {
	   	pid_yaw_y_Init();
	    pid_ultra_1_Init();
	    Encoder_Clear();
	    Move_flag=10;
   }
         if(Move_flag==11)    //½øÈë2ºÅ
   {
	   	pid_yaw_x_Init();
	    pid_ultra_2_Init();
	    Encoder_Clear();
	    Move_flag=12;
   }
         if(Move_flag==15)    //³ö2ºÅ
   {
	   	pid_yaw_y_Init();
	    pid_ultra_1_Init();
	    Encoder_Clear();
	    Move_flag=16;
   }
         if(Move_flag==17)    //½øÈë3ºÅ
   {
	   	pid_yaw_x_Init();
	    pid_ultra_2_Init();
	    Encoder_Clear();
	    Move_flag=18;
   }
	    if(Move_flag==21)    //³ö3ºÅ
   {
	   	pid_yaw_y_Init();
	    pid_ultra_1_Init();
	    Encoder_Clear();
	    Move_flag=22;
   }
   	    if(Move_flag==23)    //½øÈë4ºÅ
   {
	   	pid_yaw_x_Init();
	    pid_ultra_2_Init();
	    Encoder_Clear();
	    Move_flag=24;
   }
        if(Move_flag==27)    //³ö4ºÅ
   {
	   	pid_yaw_y_Init();
	    pid_ultra_1_Init();
	    Encoder_Clear();
	    Move_flag=28;
   }
        if(Move_flag==29)    //½øÈë5ºÅ
   {
	   	pid_yaw_x_Init();
	    pid_ultra_2_Init();
	    Encoder_Clear();
	    Move_flag=30;
   }
   	    if(Move_flag==33)    //³ö5ºÅ
   {
	   	pid_yaw_y_Init();
	    pid_ultra_1_Init();
	    Encoder_Clear();
	    Move_flag=34;
   }
      	if(Move_flag==35)    //½øÈë6ºÅ
   {
	   	pid_yaw_x_Init();
	    pid_ultra_2_Init();
	    Encoder_Clear();
	    Move_flag=36;
   }
        if(Move_flag==39)    //·µ»ØÆðÊ¼Çø
   {
	   	pid_yaw_y_Init();
	    pid_ultra_1_Init();
	    Encoder_Clear();
	    Move_flag=40;
   }
}


void Get_flag()
{
    /*ÈëÂ¢*/
	if(Move_flag==2)start_1(0,900);//85//	if(Move_flag==2)start_1(0,900);//85
	else if(Move_flag==3)start_2(0,950);//85
	else if(Move_flag==4)start_3(0,650);//75

    /*¿çÂ¢1*/
	else if(Move_flag==6)first_1(880,0);
	else if(Move_flag==7)first_2(1000,0);//1
	else if(Move_flag==8)first_3(880,0);
//    
    /*¿çÂ¢1*/
	else if(Move_flag==6)first_1(880,0);
	else if(Move_flag==7)first_2(1000,0);//1
	else if(Move_flag==8)first_3(880,0);
    
	/*»»Â¢1*/
	else if(Move_flag==10)tran_1(0,-700);
    
	/*¿çÂ¢2*/
	else if(Move_flag==12)second_1(-880,0);
	else if(Move_flag==13)second_2(-1000,0);//2
	else if(Move_flag==14)second_3(-880,0);
    
	/*»»Â¢2*/
	else if(Move_flag==16)tran_2(0,-700);
    
	/*¿çÂ¢3*/
	else if(Move_flag==18)third_1(880,0);
	else if(Move_flag==19)third_2(1000,0);
	else if(Move_flag==20)third_3(880,0);
    
	/*»»Â¢3*/
	else if(Move_flag==22)tran_3(0,-700);
	
    /*¿çÂ¢4*/
	else if(Move_flag==24)fourth_1(-880,0);
	else if(Move_flag==25)fourth_2(-1000,0);
	else if(Move_flag==26)fourth_3(-880,0);
    
	/*»»Â¢4*/
	else if(Move_flag==28)tran_4(0,-700);
	
    /*¿çÂ¢5*/
	else if(Move_flag==30)fifth_1(880,0);
	else if(Move_flag==31)fifth_2(1000,0);
	else if(Move_flag==32)fifth_3(880,0);
	
	/*»»Â¢5*/
	else if(Move_flag==34)tran_5(0,-700);
	
	/*¿çÂ¢6*/
	else if(Move_flag==36)sixth_1(-880,0);
	else if(Move_flag==37)sixth_2(-1000,0);
	else if(Move_flag==38)sixth_3(-880,0);
	
	else if(Move_flag==40)back(0,-980);
	else if(Move_flag==41)back_2(0,-650);
//    
}










//////    /*¿çÂ¢1*/
//////	else if(Move_flag==6)first_1(800,0);
//////	else if(Move_flag==7)first_2(1000,0);//1
//////	else if(Move_flag==8)first_3(600,0);
////////    
////////	/*»»Â¢1*/
//////	else if(Move_flag==10)tran_1(0,-600);
////////    
//////	/*¿çÂ¢2*/
//////	else if(Move_flag==12)second_1(-800,0);
//////	else if(Move_flag==13)second_2(-900,0);//2
//////	else if(Move_flag==14)second_3(-800,0);
////////    
//////	/*»»Â¢2*/
//////	else if(Move_flag==16)tran_2(0,-600);
////////    
//////	/*¿çÂ¢3*/
//////	else if(Move_flag==18)third_1(800,0);
//////	else if(Move_flag==19)third_2(900,0);
//////	else if(Move_flag==20)third_3(800,0);
////////    
////////	/*»»Â¢3*/
//////	else if(Move_flag==22)tran_3(0,-600);
////////	
//////    /*¿çÂ¢4*/
//////	else if(Move_flag==24)fourth_1(-800,0);
//////	else if(Move_flag==25)fourth_2(-900,0);
//////	else if(Move_flag==26)fourth_3(-800,0);
////////    
////////	/*»»Â¢4*/
//////	else if(Move_flag==28)tran_4(0,-600);
////////	
////////    /*¿çÂ¢5*/
//////	else if(Move_flag==30)fifth_1(800,0);
//////	else if(Move_flag==31)fifth_2(900,0);
//////	else if(Move_flag==32)fifth_3(800,0);
//////	
////////	/*»»Â¢5*/
//////	else if(Move_flag==34)tran_5(0,-600);
//////	
////////	/*¿çÂ¢6*/
//////	else if(Move_flag==36)sixth_1(-800,0);
//////	else if(Move_flag==37)sixth_2(-900,0);
//////	else if(Move_flag==38)sixth_3(-800,0);
//////	
//////	else if(Move_flag==40)back(0,-850);
//////	else if(Move_flag==41)back_2(0,-750);






void start_1(int vx,int vy)
{
	
	float out=0;
	
	TRIG_3
	TRIG_4
	out=yaw_base1_Pid_Ctrl(&yaw_base1_pid,yaw,start_yaw);
	
	mike_wheel(vx,vy,out);
	Solve_EncoData();
	if(my_abs(Encoders.disA)>40.0f||my_abs(Encoders.disB)>40.0f)
	{
		mike_wheel(0,0,0);
		Encoder_Clear();
     	Move_flag=3;

	}
	
}

void start_2(int vx,int vy)
{
	float out1=0,out2=0;
	
	TRIG_3
	TRIG_4

	out1=yaw_base1_Pid_Ctrl(&yaw_base1_pid,yaw,start_yaw);
	out2=ultra_base1_Pid_Ctrl(&ultra_base1_pid,Ultra_B_L,62.0f);
	mike_wheel(vx+out2,vy,out1);
	Solve_EncoData();
	if(my_abs(Encoders.disA)>680.0f||my_abs(Encoders.disB)>680.0f)
	{
		mike_wheel(0,0,0);
		Move_flag=4;
	}
	
}

void start_3(int vx,int vy)
{
	float out1=0,out2=0;

	TRIG_3
	TRIG_4
	out1=yaw_base1_Pid_Ctrl(&yaw_base1_pid,yaw,start_yaw);
	out2=ultra_base1_Pid_Ctrl(&ultra_base1_pid,Ultra_B_L,73.0f);
	mike_wheel(vx+out2,vy,out1);
	Solve_EncoData();
	if(Ultra_F_L<230.0f&&Ultra_F_L>15.0f)
	{

        filter(15);
		Encoder_Clear();
		Move_flag=5;

	}

	
}

void first_1(int vx,int vy)
{
	float out1=0,out2=0;
	TRIG_3
	TRIG_1
	out1=yaw_base1_Pid_Ctrl(&yaw_base2_pid,yaw,start_yaw);
	out2=ultra_base1_Pid_Ctrl(&ultra_base1_pid,Ultra_F_L,40.0f);
	mike_wheel(vx,vy+out2,out1);
	Solve_EncoData();
	if(my_abs(Encoders.disA)>80.0f||my_abs(Encoders.disB)>80.0f)
	{
		mike_wheel(0,0,0);
		Encoder_Clear();
		Move_flag=7;
	}
	
}

void first_2(int vx,int vy)
{
	float out1=0,out2=0;
	TRIG_1
	TRIG_2
	TRIG_3
	out1=yaw_base1_Pid_Ctrl(&yaw_base2_pid,yaw,start_yaw);
	out2=ultra_base2_Pid_Ctrl(&ultra_base2_pid,Ultra_F_R,Ultra_F_L);
	mike_wheel(vx,vy+out2,out1);
	Solve_EncoData();
	if(my_abs(Encoders.disA)>480.0f||my_abs(Encoders.disB)>480.0f)
	{
		mike_wheel(0,0,0);
		Encoder_Clear();
		Move_flag=8;
	}
	
}

void first_3(int vx,int vy)
{
	float out1=0,out2=0;
	TRIG_3
	TRIG_2
	out1=yaw_base1_Pid_Ctrl(&yaw_base2_pid,yaw,start_yaw);
	out2=ultra_base1_Pid_Ctrl(&ultra_base1_pid,Ultra_F_L,42.0f);
	mike_wheel(vx,vy+out2,out1);
	Solve_EncoData();
	if(Ultra_B_R<193.0f&&Ultra_B_R>10.0f)
	{
        filter(15);
		Encoder_Clear();
//		USART_SendData(USART1,2);
		Move_flag=9;

	}
	
}

void tran_1(int vx,int vy)
{
	float out1=0,out2=0;
	TRIG_2
	TRIG_4
	out1=yaw_base1_Pid_Ctrl(&yaw_base1_pid,yaw,start_yaw);
	out2=ultra_base1_Pid_Ctrl(&ultra_base1_pid,Ultra_B_R,76.0f);
	mike_wheel(vx-out2,vy,out1);
	Solve_EncoData();
	if((my_abs(Encoders.disA)>80.0f||my_abs(Encoders.disB)>80.0f)&&Ultra_B_L>300.0f) //130 130 300
	{
			Encoder_Clear();
		    state=1;


	}
    if(state==1&&(my_abs(Encoders.disA)>10.0f||my_abs(Encoders.disB)>10.0f))
	{
			mike_wheel(0,0,0);
			filter(15);
			Encoder_Clear();

			Move_flag=11;
		    state=0;
	}

	
	
}

void second_1(int vx,int vy)
{
	float out1=0;
	TRIG_1
	TRIG_3
    decrease_speed_1(&vx,0.22); // 22

	
	out1=yaw_base1_Pid_Ctrl(&yaw_base2_pid,yaw,start_yaw);
	mike_wheel(vx,vy,out1);
	Solve_EncoData();
	if(my_abs(Encoders.disA)>120.0f||my_abs(Encoders.disB)>120.0f)
	{
		mike_wheel(0,0,0);
		Encoder_Clear();
		Move_flag=13;
	}
}

void second_2(int vx,int vy)
{
	float out1=0,out2=0;
	TRIG_1
	TRIG_4
	TRIG_3
//    decrease_speed_1(&vx,0.22);

	
	out1=yaw_base1_Pid_Ctrl(&yaw_base2_pid,yaw,start_yaw);
	out2=ultra_base2_Pid_Ctrl(&ultra_base2_pid,Ultra_F_R,Ultra_F_L);
	mike_wheel(vx,vy+out2,out1);
	Solve_EncoData();
	if(my_abs(Encoders.disA)>430.0f||my_abs(Encoders.disB)>430.0f)
	{
		mike_wheel(0,0,0);
		Encoder_Clear();
		Move_flag=14;
	}
}

void second_3(int vx,int vy)
{
	float out1=0;
	TRIG_4
	
    decrease_speed_1(&vx,0.22);

	
	out1=yaw_base1_Pid_Ctrl(&yaw_base2_pid,yaw,start_yaw);
	mike_wheel(vx,vy,out1);
	Solve_EncoData();
	if(Ultra_B_L<215.0f&&Ultra_B_L>10.0f)
	{
		
		filter(15);
		Encoder_Clear();
//		USART_SendData(USART1,3);
		Move_flag=15;

	}
	
}

void tran_2(int vx,int vy)
{
	float out1=0,out2=0;

	TRIG_2
	TRIG_4
	out1=yaw_base1_Pid_Ctrl(&yaw_base1_pid,yaw,start_yaw);
	out2=ultra_base1_Pid_Ctrl(&ultra_base1_pid,Ultra_B_L,76.0f);
	mike_wheel(vx+out2,vy,out1);
	Solve_EncoData();
	
	if((my_abs(Encoders.disA)>80.0f||my_abs(Encoders.disB)>80.0f)&&Ultra_B_R>300.0f)
	{
			Encoder_Clear();
		    state=1;
	}
	

    if(state==1&&(my_abs(Encoders.disA)>15.0f||my_abs(Encoders.disB)>15.0f))
	{
			mike_wheel(0,0,0);
			filter(15);
			Encoder_Clear();

			Move_flag=17;
		    state=0;
	}
	
}

void third_1(int vx,int vy)
{
	float out1=0;
	TRIG_3
	TRIG_1
    decrease_speed_2(&vx,0.22);
	out1=yaw_base1_Pid_Ctrl(&yaw_base2_pid,yaw,start_yaw);
	mike_wheel(vx,vy,out1);
	Solve_EncoData();
	if(my_abs(Encoders.disA)>80.0f||my_abs(Encoders.disB)>80.0f)
	{
		mike_wheel(0,0,0);
		Encoder_Clear();
		Move_flag=19;
	}
//	if((task==0)&&PEin(6)==1)
//	{
//		mike_wheel(0,50,0);
//        task=1;
//		USART_SendData(USART1,start_work);
//		while(rec_data_u1[0]!=1);
//		rec_data_u1[0]=0;
//	}
//		else if((task==1)&&PEin(6)==0)
//	{

//		task=0;
//	}
	
	}


void third_2(int vx,int vy)
{
	float out1=0,out2=0;
	TRIG_3
	TRIG_2
	TRIG_1
	decrease_speed_2(&vx,0.22);
	out1=yaw_base1_Pid_Ctrl(&yaw_base2_pid,yaw,start_yaw);
	out2=ultra_base2_Pid_Ctrl(&ultra_base2_pid,Ultra_F_R,Ultra_F_L);
	mike_wheel(vx,vy+out2,out1);
	Solve_EncoData();
	if(my_abs(Encoders.disA)>480.0f||my_abs(Encoders.disB)>480.0f)
	{
		mike_wheel(0,0,0);
		Encoder_Clear();
		Move_flag=20;
	}
//	if((task==0)&&PEin(6)==1)
//	{
//		mike_wheel(0,50,0);
//        task=1;
//		USART_SendData(USART1,start_work);
//		while(rec_data_u1[0]!=1);
//		rec_data_u1[0]=0;
//	}
//		else if((task==1)&&PEin(6)==0)
//	{

//		task=0;
//	}
	
}

void third_3(int vx,int vy)
{
	float out1=0;
	TRIG_2
	decrease_speed_2(&vx,0.22);
	out1=yaw_base1_Pid_Ctrl(&yaw_base2_pid,yaw,start_yaw);
	mike_wheel(vx,vy,out1);
	Solve_EncoData();
	if(Ultra_B_R<193.0f&&Ultra_B_R>10.0f) //200   10
	{
        filter(15);
		Encoder_Clear();
//		USART_SendData(USART1,2);
		Move_flag=21;

	}
//	if((task==0)&&PEin(6)==1)
//	{
//		mike_wheel(0,50,0);
//        task=1;
//		USART_SendData(USART1,start_work);
//		while(rec_data_u1[0]!=1);
//		rec_data_u1[0]=0;
//	}
//		else if((task==1)&&PEin(6)==0)
//	{

//		task=0;
//	}

}

void tran_3(int vx,int vy)
{
	float out1=0,out2=0;
	TRIG_2
	TRIG_4
	out1=yaw_base1_Pid_Ctrl(&yaw_base1_pid,yaw,start_yaw);
	out2=ultra_base1_Pid_Ctrl(&ultra_base1_pid,Ultra_B_R,72.0f);
	mike_wheel(vx-out2,vy,out1);
	Solve_EncoData();
	if((my_abs(Encoders.disA)>80.0f||my_abs(Encoders.disB)>80.0f)&&Ultra_B_L>300.0f)
	{
			Encoder_Clear();
		    state=1;
	}
	
    if(state==1&&(my_abs(Encoders.disA)>15.0f||my_abs(Encoders.disB)>15.0f))
	{
			mike_wheel(0,0,0);
			filter(15);
			Encoder_Clear();

		    Move_flag=23;
		    state=0;
	}	
	
}

void fourth_1(int vx,int vy)
{
	float out1=0;
	TRIG_1
	TRIG_3
	decrease_speed_1(&vx,0.22);
	out1=yaw_base1_Pid_Ctrl(&yaw_base2_pid,yaw,start_yaw);
	mike_wheel(vx,vy,out1);
	Solve_EncoData();
	if(my_abs(Encoders.disA)>120.0f||my_abs(Encoders.disB)>120.0f)
	{
		mike_wheel(0,0,0);
		Encoder_Clear();
		Move_flag=25;
	}
//	if(task==0&&PEin(5)==1)
//	{
//		mike_wheel(0,-50,0);
//        task=1;
//		USART_SendData(USART1,start_work);
//		while(rec_data_u1[0]!=1);
//		rec_data_u1[0]=0;
//	}
//		else if((task==1)&&PEin(5)==0)
//	{

//		task=0;
//	}
	
}

void fourth_2(int vx,int vy)
{
	float out1=0,out2=0;
	TRIG_1
	TRIG_4
	TRIG_3
	decrease_speed_1(&vx,0.22);
	out1=yaw_base1_Pid_Ctrl(&yaw_base2_pid,yaw,start_yaw);
	out2=ultra_base2_Pid_Ctrl(&ultra_base2_pid,Ultra_F_R,Ultra_F_L);
	mike_wheel(vx,vy+out2,out1);
	Solve_EncoData();
	if(my_abs(Encoders.disA)>430.0f||my_abs(Encoders.disB)>430.0f)
	{
		mike_wheel(0,0,0);
		Encoder_Clear();
		Move_flag=26;
	}
//	if(task==0&&PEin(5)==1)
//	{
//		mike_wheel(0,-50,0);
//        task=1;
//		USART_SendData(USART1,start_work);
//		while(rec_data_u1[0]!=1)
//		{

//		}
//		rec_data_u1[0]=0;
//	}
//		else if((task==1)&&PEin(5)==0)
//	{

//		task=0;
//	}
	
}

void fourth_3(int vx,int vy)
{
	float out1=0;
	TRIG_4
	decrease_speed_1(&vx,0.22);	
	out1=yaw_base1_Pid_Ctrl(&yaw_base2_pid,yaw,start_yaw);
	mike_wheel(vx,vy,out1);
	Solve_EncoData();
	if(Ultra_B_L<215.0f&&Ultra_B_L>10.0f)
	{
        filter(15);
		Encoder_Clear();
//		USART_SendData(USART1,3);
		Move_flag=27;

	}
//	if(task==0&&PEin(5)==1)
//	{
//		mike_wheel(0,-50,0);
//        task=1;
//		USART_SendData(USART1,start_work);
//		while(rec_data_u1[0]!=1)
//		{
//	
//		}
//		rec_data_u1[0]=0;
//	}
//		else if((task==1)&&PEin(5)==0)
//	{

//		task=0;
//	}
	
}

void tran_4(int vx,int vy)
{
	float out1=0,out2=0;

	TRIG_2
	TRIG_4
	out1=yaw_base1_Pid_Ctrl(&yaw_base1_pid,yaw,start_yaw);
	out2=ultra_base1_Pid_Ctrl(&ultra_base1_pid,Ultra_B_L,76.0f);
	mike_wheel(vx+out2,vy,out1);
	Solve_EncoData();
	
	if((my_abs(Encoders.disA)>80.0f||my_abs(Encoders.disB)>80.0f)&&Ultra_B_R>300.0f)
	{
			Encoder_Clear();
		    state=1;
	}
	

    if(state==1&&(my_abs(Encoders.disA)>15.0f||my_abs(Encoders.disB)>15.0f))
	{
			mike_wheel(0,0,0);
			filter(15);
			Encoder_Clear();

			Move_flag=29;
		    state=0;
	}
	
}

void fifth_1(int vx,int vy)
{
	float out1=0;
	TRIG_3
	TRIG_1
	decrease_speed_2(&vx,0.22);
	out1=yaw_base1_Pid_Ctrl(&yaw_base2_pid,yaw,start_yaw);
	mike_wheel(vx,vy,out1);
	Solve_EncoData();
	if(my_abs(Encoders.disA)>80.0f||my_abs(Encoders.disB)>80.0f)
	{
		mike_wheel(0,0,0);
		Encoder_Clear();
		Move_flag=31;
	}
	
}

void fifth_2(int vx,int vy)
{
	float out1=0,out2=0;
	TRIG_3
	TRIG_2
	TRIG_1
	decrease_speed_2(&vx,0.22);
	out1=yaw_base1_Pid_Ctrl(&yaw_base2_pid,yaw,start_yaw);
	out2=ultra_base2_Pid_Ctrl(&ultra_base2_pid,Ultra_F_R,Ultra_F_L);
	mike_wheel(vx,vy+out2,out1);
	Solve_EncoData();
	if(my_abs(Encoders.disA)>480.0f||my_abs(Encoders.disB)>480.0f)
	{
		mike_wheel(0,0,0);
		Encoder_Clear();
		Move_flag=32;
	}
	
}

void fifth_3(int vx,int vy)
{
	float out1=0;
	TRIG_1
	TRIG_2
	decrease_speed_2(&vx,0.22);
	out1=yaw_base1_Pid_Ctrl(&yaw_base2_pid,yaw,start_yaw);
	mike_wheel(vx,vy,out1);
	Solve_EncoData();
	if(Ultra_B_R<210.0f&&Ultra_B_R>10.0f)
	{
        filter(15);
		Encoder_Clear();
//		USART_SendData(USART1,2);
		Move_flag=33;

	}
	
}

void tran_5(int vx,int vy)
{
	float out1=0,out2=0;
	TRIG_1
	TRIG_2
	
	out1=yaw_base1_Pid_Ctrl(&yaw_base1_pid,yaw,start_yaw);
	out2=ultra_base1_Pid_Ctrl(&ultra_base1_pid,Ultra_B_R,76.0f);
	mike_wheel(vx-out2,vy,out1);
	Solve_EncoData();
	if(Ultra_F_R<230.0f&&Ultra_F_R>10.0f)
	//if(my_abs(Encoders.disA)>158.0f||my_abs(Encoders.disB)>158.0f)
	{

        filter(15);
		Encoder_Clear();

		Move_flag=35;
	}
	
}


void sixth_1(int vx,int vy)
{
	float out1=0;
	TRIG_1
	TRIG_3
	decrease_speed_1(&vx,0.22);
	out1=yaw_base1_Pid_Ctrl(&yaw_base2_pid,yaw,start_yaw);
	mike_wheel(vx,vy,out1);
	Solve_EncoData();
	if(my_abs(Encoders.disA)>120.0f||my_abs(Encoders.disB)>120.0f)
	{
		mike_wheel(0,0,0);
		Encoder_Clear();
		Move_flag=37;
	}
	
}

void sixth_2(int vx,int vy)
{
	float out1=0,out2=0;
	TRIG_1
	TRIG_4
	TRIG_3
	decrease_speed_1(&vx,0.22);
	out1=yaw_base1_Pid_Ctrl(&yaw_base2_pid,yaw,start_yaw);
	out2=ultra_base2_Pid_Ctrl(&ultra_base2_pid,Ultra_F_R,Ultra_F_L);
	mike_wheel(vx,vy+out2,out1);
	Solve_EncoData();
	if(my_abs(Encoders.disA)>430.0f||my_abs(Encoders.disB)>430.0f)
	{
		mike_wheel(0,0,0);
		Encoder_Clear();
		Move_flag=38;
	}
	
}

void sixth_3(int vx,int vy)
{
	float out1=0;
	TRIG_4
	decrease_speed_1(&vx,0.22);
	out1=yaw_base1_Pid_Ctrl(&yaw_base2_pid,yaw,start_yaw);
	mike_wheel(vx,vy,out1);
	Solve_EncoData();
	if(Ultra_B_L<195.0f&&Ultra_B_L>10.0f)
	{
		mike_wheel(0,0,0);
        filter(15);
		Encoder_Clear();
//		USART_SendData(USART1,3);
		Move_flag=39;

	}
	
}

void back(int vx,int vy)
{
	float out1=0,out2=0;
	TRIG_4

	out1=yaw_base1_Pid_Ctrl(&yaw_base1_pid,yaw,start_yaw);
	out2=ultra_base1_Pid_Ctrl(&ultra_base1_pid,Ultra_B_L,72.0f);
	mike_wheel(vx+out2,vy,out1);
	Solve_EncoData();
	if(my_abs(Encoders.disA)>75.0f||my_abs(Encoders.disB)>75.0f)
	{
		mike_wheel(0,0,0);
		Encoder_Clear();
		Move_flag=41;
	}

}
void back_2(int vx,int vy)
{
	float out=0;
	out=yaw_base1_Pid_Ctrl(&yaw_base2_pid,yaw,start_yaw);
	
	mike_wheel(vx,vy,out);
	Solve_EncoData();
	if(my_abs(Encoders.disA)>15.0f||my_abs(Encoders.disB)>15.0f)
	{
		
		filter(15);
		Encoder_Clear();
     	Move_flag=42;
		mike_wheel(0,0,0);

	}
	
}




void filter(int time)
{
	int out1=0;
	for(i=0;i<time;i++)
{
	out1=yaw_base1_Pid_Ctrl(&yaw_base1_pid,yaw,start_yaw);
	mike_wheel(0,0,out1);
	delay_ms(10);
}
	
}


//    E5        ÓÒÃæ		1  ÆæÊý
//    E6        ×óÃæ		2  Å¼Êý
//    #define start_work    1

void decrease_speed_1(int *vx,float k)
{

	static int speed=0;
	int state=1;
	if(*vx<0)
		state=-1;
	if(PEin(5)==1&&task==0)
	{
	  USART_SendData(USART1,start_work); 
		task=1;
		speed=*vx;
	}
	else if(task==1&&PEin(6)==1)
	{
		
		task=0;
	}
	if(task==1)
	{
		speed = speed-60*state;
		if(myabs(speed)<myabs((*vx)*k))
		{
			speed=(*vx)*k;
		}
			*vx =speed;
  }
	
	
	if(task==0)
	{
		speed = speed+50*state;
		if(myabs(speed)>myabs((*vx)))
		{
			speed=(*vx);
		}
			*vx =speed;
   }
	
	
	
	
}

void decrease_speed_2(int *vx,float k)
{
	//k=0.1;
	static int speed=0;
	int state=1;
	if(*vx<0)
		state=-1;
	
	if(PEin(6)==1&&task==0)
	{
	  USART_SendData(USART1,start_work);
		task=1;
		speed=*vx;
		
	}
	else if(task==1&&PEin(5)==1)
	{
		task=0;
	}
	
	if(task==1)
	{
		speed = speed-60*state;
		if(myabs(speed)<myabs((*vx)*k))
		{
			speed=(*vx)*k;
		}
		*vx =speed;
	}

	if(task==0)
	{
		speed = speed+60*state;
		if(myabs(speed)>myabs((*vx)))
		{
			speed=(*vx);
		}
		*vx =speed;
   }
	
}
