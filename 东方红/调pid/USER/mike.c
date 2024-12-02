#include "mike.h"


void mike_wheel(int vx,int vy,float yaw)
{
	int speed_1=0,speed_2=0,speed_3=0,speed_4=0;
	
	speed_1=(1/wheel_R)*(vy+vx-yaw*(wheel_L1+wheel_L2));//左上
	speed_2=(1/wheel_R)*(vy-vx+yaw*(wheel_L1+wheel_L2));//右上
	speed_3=(1/wheel_R)*(vy-vx-yaw*(wheel_L1+wheel_L2));//左下
	speed_4=(1/wheel_R)*(vy+vx+yaw*(wheel_L1+wheel_L2));//右下
	
	Motor_TB_Set(speed_3,speed_1,speed_4,speed_2);
	//
}


