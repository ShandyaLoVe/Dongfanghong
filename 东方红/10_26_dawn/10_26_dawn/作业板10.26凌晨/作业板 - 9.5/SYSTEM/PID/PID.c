#include "PID.H"

void PID_init(PID *pid,float p,float i,float d,float maxI,float maxout)
{
	pid->kp =p;
	pid->ki =i;
	pid->kd =d;
	pid->maxIntegral=maxI;
	pid->maxOutput=maxout;
	
}

void PID_Calc(PID *pid,float reference,float feedback)
{
	pid->lastError=pid->error;
	pid->error=reference-feedback;
	float dout=(pid->error-pid->lastError)*pid->kd;
	float pout=pid->error*pid->kp;
	pid->integral+=pid->error*pid->ki;
	if(pid->integral > pid->maxIntegral)pid->integral=pid->maxIntegral;
	else if(pid->integral < -pid->maxIntegral)pid->integral=-pid->maxIntegral;
	
	pid->output=pout+dout+pid->integral;
	if(pid->output>pid->maxOutput)pid->output=pid->maxOutput;
	else if(pid->output<-pid->maxOutput)pid->output=-pid->maxOutput;
}
void PID_2(PID *pid,float reference,float feedback,float max_angel,float min_angel)
{
	pid->lastlastError = pid->lastError;
	pid->lastError=pid->error;
	pid->error=reference-feedback;
	float pout=(pid->error-pid->lastError)*pid->kp;
	float dout=(pid->error-2*pid->lastError+pid->lastlastError)*pid->kd;
	pid->integral=pid->error*pid->ki;
	if(pout+dout+pid->integral>3.5)pid->output +=3.5;
	else if(pout+dout+pid->integral<-3.5)pid->output -=3.5;
	else pid->output +=pout+dout+pid->integral;
	if(pid->output>max_angel)pid->output=max_angel;
	else if(pid->output<min_angel)pid->output=min_angel;
}
PID PIDGO,PIDTURN,PID_X,PID_Y;
