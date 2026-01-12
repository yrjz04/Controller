/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 09:16:36
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-05 09:46:51
 * @FilePath: \Controller\Src\System\Application.h
 * @Description: 
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Hardware/Drv_Lcd/Drv_Lcd.h"
#include "Hardware/Drv_Motor/Drv_Motor.h"
#include "Hardware/Drv_Sensor/Drv_Sensor.h"

void Sys_Init(void);
void Sys_Task(void);

#endif
