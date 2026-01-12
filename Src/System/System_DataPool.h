/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 09:16:16
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-05 16:20:06
 * @FilePath: \Controller\Src\System\System_DataPool.h
 * @Description: 
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#ifndef __SYSTEM_DATAPOOL_H__
#define __SYSTEM_DATAPOOL_H__

#include "main.h"
#include "Middleware/Pid/Pid.h"
extern uint32_t NowTempture, DisTempture,DesTempture;      //传感器测得温度，显示温度，设定目标温度
extern uint16_t NowSpeed, DisSpeed, DesSpeed;              //电机当前速度，显示速度，设定目标速度
extern uint8_t Motor_Lock,Heater_Lock;                     //电机修改锁，温度修改锁
extern PID_HandleTypeDef Heater_pid;

#endif
