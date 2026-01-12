/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-12 16:09:25
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-12 21:35:06
 * @FilePath: \Controller\Src\System\System_Callback.h
 * @Description: 系统回调函数汇总 只需要调用注册函数即可实现中断函数的重写
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#ifndef __SYSTEM_CALLBACK_H__
#define __SYSTEM_CALLBACK_H__
#include "main.h"
#include "System_Config.h"

typedef void (*TIM_PeriodElapsedCallback_t)(TIM_HandleTypeDef *htim);        //定时器周期中断回调函数类型
typedef void (*UARTEx_RxEventCallback_t)(UART_HandleTypeDef *huart, uint16_t Size);        //UART接收事件回调函数类型
typedef void (*GPIO_EXTI_Callback_t)(uint16_t GPIO_Pin);        //GPIO外部中断回调函数类型

typedef struct 
{
    char Name[10];
    TIM_PeriodElapsedCallback_t Callback;
}TIM_PeriodElapsedCallback_Item_t;
typedef struct 
{
    char Name[10];
    UARTEx_RxEventCallback_t Callback;
}UARTEx_RxEventCallback_Item_t;
typedef struct 
{
    char Name[10];
    GPIO_EXTI_Callback_t Callback;
}GPIO_EXTI_Callback_Item_t;

#if TIM_PERIOD_ELAPSED_CALLBACK_ENABLE
extern TIM_PeriodElapsedCallback_Item_t TIM_PeriodElapsedCallback_TASK[TIM_PERIOD_ELAPSED_CALLBACK_TASK_NUM];
void TIM_PERIOD_ELAPSED_CALLBACK_Register(TIM_PeriodElapsedCallback_t fun,char *Name);
void TIM_PERIOD_ELAPSED_CALLBACK_UnRegister(TIM_PeriodElapsedCallback_t fun,char *Name);
#endif

#if UARTEx_RX_EVENT_CALLBACK_ENABLE
extern UARTEx_RxEventCallback_Item_t UARTEx_RxEventCallback_TASK[UARTEx_RX_EVENT_CALLBACK_TASK_NUM];
void UARTEx_RX_EVENT_CALLBACK_Register(UARTEx_RxEventCallback_t fun,char *Name);
void UARTEx_RX_EVENT_CALLBACK_UnRegister(UARTEx_RxEventCallback_t fun,char *Name);
#endif

#if GPIO_EXTI_CALLBACK_ENABLE
extern GPIO_EXTI_Callback_Item_t GPIO_EXTI_Callback_TASK[GPIO_EXTI_CALLBACK_TASK_NUM];
void GPIO_EXTI_CALLBACK_Register(GPIO_EXTI_Callback_t fun,char *Name);
void GPIO_EXTI_CALLBACK_UnRegister(GPIO_EXTI_Callback_t fun,char *Name);
#endif

#endif
