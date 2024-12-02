#ifndef __PID_H
#define __PID_H

#include "sys.h"
typedef struct
{
	float kp,ki,kd;
	float error,lastError,lastlastError;
	float integral,maxIntegral;
	float output,maxOutput;
}PID;
void PID_init(PID *pid,float p,float i,float d,float maxI,float maxout);
void PID_Calc(PID *pid,float reference,float feedback);
void PID_2(PID *pid,float reference,float feedback,float max_angel,float min_angel);

extern PID PIDGO,PIDTURN,PID_X,PID_Y;


#endif
