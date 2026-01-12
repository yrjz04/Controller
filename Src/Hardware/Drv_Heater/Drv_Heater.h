/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 09:11:18
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-05 09:30:09
 * @FilePath: \Controller\Src\Hardware\Drv_Encoder\Drv_Encoder.h
 * @Description: 
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#ifndef __DRV_HEATER_H__
#define __DRV_HEATER_H__

#include "main.h"

typedef struct
{
    TIM_HandleTypeDef* htim;
    uint32_t Channel;
}Heater_HandleTypeDef;

void Drv_Heater_Init(void);
void Drv_Heater_SetPower(uint16_t power);

#endif
