/***
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 11:30:58
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-12 21:55:50
 * @FilePath: \Controller\Src\System\System_Config.h
 * @Description: 系统配置文件
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved.
 */

///<<< Use Configuration Wizard in Context Menu >>>
#ifndef __SYSTEM_CONFIG_H__
#define __SYSTEM_CONFIG_H__

#define PID_KP 0.5f
#define PID_KI 0.0f
#define PID_KD 0.0f

// <e> 系统配置
#define SYSTEM_CONFIG_ENABLE 1

// <q> 使能调试功能,使用串口1输出
#define DEBUG_ENABLE 1

// <e> 各中断回调函数使能配置
#define INTERRUPT_CONFIG_ENABLE 1

// <q> 使能定时器周期中断回调函数
#define TIM_PERIOD_ELAPSED_CALLBACK_ENABLE 1

// <o> 定时器周期中断回调函数任务数
#define TIM_PERIOD_ELAPSED_CALLBACK_TASK_NUM 1

// <q> 使能UART接收事件回调函数
#define UARTEx_RX_EVENT_CALLBACK_ENABLE 1
// <o> UART接收事件回调函数任务数
#define UARTEx_RX_EVENT_CALLBACK_TASK_NUM 2

// <q> 使能GPIO外部中断回调函数
#define GPIO_EXTI_CALLBACK_ENABLE 0
// <o> GPIO外部中断回调函数任务数
#define GPIO_EXTI_CALLBACK_TASK_NUM 1

// </e> 各中断回调函数使能配置

// <e> UART配置
#define UART_CONFIG_ENABLE 1
// <o> UART接收缓冲区大小
#define RX_BUFFER_SIZE 256
// <e> 使能UART1
#define UART1_ENABLE 1
// <o> UART1 接收方式
// <0=> 不使能DMA接收
// <1=> 使能DMA接收
#define UART1_DMA_ENABLE 0
// </e> 使能UART1

// <e> 使能UART2
#define UART2_ENABLE 1
// <o> UART2 接收方式
// <0=> 不使能DMA接收
// <1=> 使能DMA接收
#define UART2_DMA_ENABLE 1
// </e> 使能UART2

// 野火上位机使用串口配置
#define USE_UART1_DEBUG 1
#define USE_UART2_DEBUG 0

// </e> 系统配置
// =============

// <e> 额外配置
// <e> 电机配置
#define ENCODE_MOTOR_ENABLE 1
// <o> 电机速度步长
#define MOTOR_SPEED_STEP 100
// <o> 默认目标速度
#define DEFAULT_TARGET_SPEED 20
// </e> 电机配置
// =============

// <e> 加热器配置
#define ENCODE_HEATER_ENABLE 1
// <o> 加热器温度步长
#define HEATER_TEMP_STEP 200
// <o> 默认目标温度
#define DEFAULT_TARGET_TEMP 210
// </e> 加热器配置
// =============

// <e> PWM配置
// =============
// <o> PWM最大占空比
#define PWM_MAX_DUTY 99
// <o> PWM最小占空比
#define PWM_MIN_DUTY 0
// </e> PWM配置
// =============

#endif
// <<< end of configuration section >>>
