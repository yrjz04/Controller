/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 16:17:47
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-05 16:26:51
 * @FilePath: \Controller\Src\Middleware\Pid\Pid.c
 * @Description: PID控制器实现
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#include "Pid.h"
#include "System/System_DataPool.h"
#include "System/System_Config.h"

void PID_Init(PID_HandleTypeDef *pid, float target) {
    pid->Kp = PID_KP;
    pid->Ki = PID_KI;
    pid->Kd = PID_KD;
    pid->target = target;
    pid->current = 0.0f;
    pid->err = 0.0f;
    pid->err_last = 0.0f;
    pid->integral = 0.0f;
    pid->output = 0.0f;
}

float PID_Calculate(PID_HandleTypeDef *pid, float current) {
    // 1. 更新当前值与偏差
    pid->current = current;
    pid->err = pid->target - pid->current;

    // 2. 积分项（积分饱和抑制：仅当输出未超限且偏差较小时累积）
    if (pid->output >= PWM_MAX_DUTY || pid->output <= PWM_MIN_DUTY) {
        pid->integral = pid->integral;  // 输出超限，暂停积分
    } else {
        pid->integral += pid->err * pid->Ki;  // 积分累积
    }

    // 3. PID三部分计算
    float p_out = pid->Kp * pid->err;          // 比例项
    float i_out = pid->integral;               // 积分项
    float d_out = pid->Kd * (pid->err - pid->err_last);  // 微分项

    // 4. 总输出
    pid->output = p_out + i_out + d_out;

    // 5. 输出限幅（映射到PWM占空比范围）
    if (pid->output > PWM_MAX_DUTY) {
        pid->output = PWM_MAX_DUTY;
    } else if (pid->output < PWM_MIN_DUTY) {
        pid->output = PWM_MIN_DUTY;
    }

    // 6. 保存本次偏差，供下次微分计算
    pid->err_last = pid->err;

    return pid->output;
}

