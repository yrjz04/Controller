/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 09:16:13
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-05 16:32:10
 * @FilePath: \Controller\Src\System\System_DataPool.c
 * @Description: 
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#include "System_DataPool.h"
#include "System_Config.h"
#include "main.h"
#include "Middleware/Pid/Pid.h"

uint32_t NowTempture = HEATER_TEMP_STEP, DesTempture = DEFAULT_TARGET_TEMP;      //传感器测得温度，显示温度，设定目标温度
uint16_t NowSpeed = 0,    DesSpeed = DEFAULT_TARGET_SPEED;              //电机当前速度，显示速度，设定目标速度
uint8_t Motor_Lock = 0,Heater_Lock = 0;
float Heater_p = 2.0,Heater_i = 0.5,Heater_d = 0.1;                                    //Pid输出
PID_HandleTypeDef Heater_pid;
