#ifndef __STEER_H
#define __STEER_H

extern int Total_Degree;

void TIM4_Steer_Init(void);
void TIM8_Servo_PWM_Init(u32 arr, u16 psc);
void Steer1_degree(float degree);
void Steer2_degree(float degree);
void Steer3_degree(float degree);
void Steer4_degree(float degree);
void Steer_Control_F_AB(float Goal_Degree,float Correct_Degree);
void Steer_Control_F_CD(float Goal_Degree,float Correct_Degree);


void Steer_Control_F_ABCD(float Goal_Degree,float Correct_Degree,float Yaw_Degree);
void Steer_Control_B_ABCD(float Goal_Degree,float Correct_Degree,float Yaw_Degree);

void Steer_Control_B(float Goal_Degree,float Correct_Degree);

#endif
