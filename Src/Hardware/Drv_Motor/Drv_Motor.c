/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 09:11:51
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-05 15:39:28
 * @FilePath: \Controller\Src\Hardware\Drv_Motor\Drv_Motor.c
 * @Description: 
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#include "main.h"
#include "Drv_Motor.h"
#include "stm32f1xx_hal_tim.h"

extern TIM_HandleTypeDef htim3;
Motor_HandleTypeDef Motor = {&htim3, TIM_CHANNEL_1};
void Drv_Motor_Init(void)
{
    HAL_TIM_PWM_Start(Motor.htim, Motor.Channel);           //PWM频率=72000(35+1)/(99+1)=20 KHz
	__HAL_TIM_SET_COMPARE(Motor.htim, Motor.Channel, 0);	//速度初始为零
}

void Drv_Motor_SetSpeed(uint16_t speed)
{
    __HAL_TIM_SET_COMPARE(Motor.htim, Motor.Channel, speed);
}
