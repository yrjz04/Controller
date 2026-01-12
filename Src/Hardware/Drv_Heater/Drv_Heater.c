/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 09:11:18
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-08 14:43:40
 * @FilePath: \Controller\Src\Hardware\Drv_Heater\Drv_Heater.c
 * @Description: 
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#include "main.h"
#include "Drv_Heater.h"

extern TIM_HandleTypeDef htim2;
Heater_HandleTypeDef Heater = {&htim2, TIM_CHANNEL_2};

void Drv_Heater_Init(void)
{
    HAL_TIM_PWM_Start(Heater.htim, Heater.Channel);          	 //PWM频率=72000(35+1)/(99+1)=20 KHz
	__HAL_TIM_SET_COMPARE(Heater.htim, Heater.Channel, 0);	 	 //初始加热为0
}

void Drv_Heater_SetPower(uint16_t power)
{
    __HAL_TIM_SET_COMPARE(Heater.htim, Heater.Channel, power);
}
