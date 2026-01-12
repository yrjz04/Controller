/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 11:30:58
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-11 16:56:50
 * @FilePath: \Controller\Src\System\System_Config.h
 * @Description: 系统配置文件
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#ifndef __SYSTEM_CONFIG_H__
#define __SYSTEM_CONFIG_H__

//串口DMA配置
#define RX_BUFFER_SIZE 256
#define UART1_DMA_ENABLE 0
#define UART2_DMA_ENABLE 1
#define UART1_NODMA_ENABLE 1
#define UART2_NODMA_ENABLE 0

//野火上位机使用串口配置
#define USE_UART1_DEBUG 1
#define USE_UART2_DEBUG 0

//编码器配置
#define ENCODE_MOTOR_ENABLE 1
#define ENCODE_HEATER_ENABLE 1

//电机配置
#define MOTOR_SPEED_STEP 0
#define DEFAULT_TARGET_SPEED 0

//加热器配置
#define HEATER_TEMP_STEP 0
#define DEFAULT_TARGET_TEMP 0

//Pid配置
#define PID_KP 0.1
#define PID_KI 0.5
#define PID_KD 0.1

//PWM配置
#define PWM_MAX_DUTY 99
#define PWM_MIN_DUTY 0



#endif
