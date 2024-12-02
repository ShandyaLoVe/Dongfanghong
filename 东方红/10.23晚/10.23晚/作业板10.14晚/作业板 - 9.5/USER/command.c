#include "command.h"

float calculate_angle(void)
{
	  float angle=0;
	  int x,y;
	  if(data[3]==0)
	  {
		x=data[1];
	  }
	  else   
	  {
		x=-data[1];
	  }
	  if(data[4]==0)
	  {
		y=data[2];
	  }
	  else  
	  {
		y=-data[2];
	  }
	  angle=atan(x/500.0)*k;
	  		  if(angle>60)
		  {
		  angle=60;}
		  else if(angle<-60)
		  {
		  angle=-60;
		  }
	  return angle;
}
