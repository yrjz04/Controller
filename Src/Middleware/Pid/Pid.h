#ifndef __PID_H__
#define __PID_H__

typedef struct {
    float Kp;          // 比例系数
    float Ki;          // 积分系数
    float Kd;          // 微分系数
    float target;      // 目标值（目标温度）
    float current;     // 当前值（当前温度）
    float err;         // 当前偏差（target - current）
    float err_last;    // 上一次偏差
    float integral;    // 积分项
    float output;      // PID输出（最终映射为PWM占空比）
} PID_HandleTypeDef;

void PID_Init(PID_HandleTypeDef *pid, float target);
float PID_Calculate(PID_HandleTypeDef *pid, float current);
#endif
