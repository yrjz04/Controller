/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 09:11:59
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-08 14:39:47
 * @FilePath: \Controller\Src\Hardware\Drv_Motor\Drv_Motor.h
 * @Description: 
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#ifndef __DRV_MOTOR_H__
#define __DRV_MOTOR_H__

#include "main.h"

typedef struct
{
    TIM_HandleTypeDef* htim;
    uint32_t Channel;
}Motor_HandleTypeDef;



void Drv_Motor_Init(void);
void Drv_Motor_SetSpeed(uint16_t speed);

#endif

