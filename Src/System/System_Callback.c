/***
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-12 16:09:21
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-12 21:43:56
 * @FilePath: \Controller\Src\System\System_Callback.c
 * @Description: 系统回调函数汇总
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved.
 */
#include "System_Callback.h"
#include "System_Config.h"
#include "main.h"
#include "System_Debug.h"
#include "string.h"

void System_CallBack_Init(void)
{
#if TIM_PERIOD_ELAPSED_CALLBACK_ENABLE
    for (uint8_t i = 0; i < TIM_PERIOD_ELAPSED_CALLBACK_TASK_NUM; i++)
    {
        TIM_PeriodElapsedCallback_TASK[i].Callback = NULL;
    }
#endif

#if UARTEx_RX_EVENT_CALLBACK_ENABLE
    for (uint8_t i = 0; i < UARTEx_RX_EVENT_CALLBACK_TASK_NUM; i++)
    {
        UARTEx_RxEventCallback_TASK[i].Callback = NULL;
    }
#endif

#if GPIO_EXTI_CALLBACK_ENABLE
    for (uint8_t i = 0; i < GPIO_EXTI_CALLBACK_TASK_NUM; i++)
    {
        GPIO_EXTI_Callback_TASK[i].Callback = NULL;
    }
#endif
}

void System_Print_All_CallbackName()
{
#if TIM_PERIOD_ELAPSED_CALLBACK_ENABLE
    for(uint8_t i=0;i<TIM_PERIOD_ELAPSED_CALLBACK_TASK_NUM;i++)
    {
        if(TIM_PeriodElapsedCallback_TASK[i].Callback!=NULL)
        {
            Debug_Log("TIM_PERIOD_ELAPSED_CALLBACK_TASK[%d]:%s\r\n",i,TIM_PeriodElapsedCallback_TASK[i].Name);
        }
    }
#endif

#if UARTEx_RX_EVENT_CALLBACK_ENABLE
    for(uint8_t i=0;i<UARTEx_RX_EVENT_CALLBACK_TASK_NUM;i++)
    {
        if(UARTEx_RxEventCallback_TASK[i].Callback!=NULL)
        {
            Debug_Log("UARTEx_RxEventCallback_TASK[%d]:%s\r\n",i,UARTEx_RxEventCallback_TASK[i].Name);
        }
    }
#endif

#if GPIO_EXTI_CALLBACK_ENABLE
    for(uint8_t i=0;i<GPIO_EXTI_CALLBACK_TASK_NUM;i++)
    {
        if(GPIO_EXTI_Callback_TASK[i].Callback!=NULL)
        {
            Debug_Log("GPIO_EXTI_Callback_TASK[%d]:%s\r\n",i,GPIO_EXTI_Callback_TASK[i].Name);
        }
    }
#endif
}

#if TIM_PERIOD_ELAPSED_CALLBACK_ENABLE
TIM_PeriodElapsedCallback_Item_t TIM_PeriodElapsedCallback_TASK[TIM_PERIOD_ELAPSED_CALLBACK_TASK_NUM]; // 定时器周期中断回调函数数组
void TIM_PERIOD_ELAPSED_CALLBACK_Register(TIM_PeriodElapsedCallback_t fun,char *Name)
{
    for (uint8_t i = 0; i < TIM_PERIOD_ELAPSED_CALLBACK_TASK_NUM; i++)
    {
        if (TIM_PeriodElapsedCallback_TASK[i].Callback == NULL)
        {
            TIM_PeriodElapsedCallback_TASK[i].Callback = fun;
            memcpy(TIM_PeriodElapsedCallback_TASK[i].Name,Name,strlen(Name));
            TIM_PeriodElapsedCallback_TASK[i].Name[strlen(Name)] = '\0';
            Debug_Log("TIM_PeriodElapsedCallback_TASK[%d] Register:%s\r\n",i,TIM_PeriodElapsedCallback_TASK[i].Name);
            break;
        }
    }
        Debug_Log("TIM_PeriodElapsedCallback_TASK Register Failed:%s————Not Found Empty Pos\r\n  ",Name);
}
void TIM_PERIOD_ELAPSED_CALLBACK_UnRegister(TIM_PeriodElapsedCallback_t fun,char *Name)
{
    for (uint8_t i = 0; i < TIM_PERIOD_ELAPSED_CALLBACK_TASK_NUM; i++)
    {
        if (TIM_PeriodElapsedCallback_TASK[i].Callback == fun)
        {
            TIM_PeriodElapsedCallback_TASK[i].Callback = NULL;
            Debug_Log("TIM_PeriodElapsedCallback_TASK[%d] UnRegister:%s\r\n",i,TIM_PeriodElapsedCallback_TASK[i].Name);
            break;
        }
    }
    Debug_Log("TIM_PeriodElapsedCallback_TASK UnRegister Failed:%s————Not Found Callback\r\n  ",Name);
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    for (uint8_t i = 0; i < TIM_PERIOD_ELAPSED_CALLBACK_TASK_NUM; i++)
    {
        if (TIM_PeriodElapsedCallback_TASK[i].Callback != NULL)
        {
            TIM_PeriodElapsedCallback_TASK[i].Callback(htim);
        }
    }
}
#endif

#if UARTEx_RX_EVENT_CALLBACK_ENABLE
UARTEx_RxEventCallback_Item_t UARTEx_RxEventCallback_TASK[UARTEx_RX_EVENT_CALLBACK_TASK_NUM]; // UART接收事件回调函数数组
void UARTEx_RX_EVENT_CALLBACK_Register(UARTEx_RxEventCallback_t fun,char *Name)
{
    for (uint8_t i = 0; i < UARTEx_RX_EVENT_CALLBACK_TASK_NUM; i++)
    {
        if (UARTEx_RxEventCallback_TASK[i].Callback == NULL)
        {
            UARTEx_RxEventCallback_TASK[i].Callback = fun;
            memcpy(UARTEx_RxEventCallback_TASK[i].Name,Name,strlen(Name));
            UARTEx_RxEventCallback_TASK[i].Name[strlen(Name)] = '\0';
            Debug_Log("UARTEx_RxEventCallback_TASK[%d] Register:%s\r\n",i,UARTEx_RxEventCallback_TASK[i].Name);
            break;
        }
    }
        Debug_Log("UARTEx_RxEventCallback_TASK Register Failed:%s————Not Found Empty Pos\r\n  ",Name);
}
void UARTEx_RX_EVENT_CALLBACK_UnRegister(UARTEx_RxEventCallback_t fun,char *Name)
{
    for (uint8_t i = 0; i < UARTEx_RX_EVENT_CALLBACK_TASK_NUM; i++)
    {
        if (UARTEx_RxEventCallback_TASK[i].Callback == fun)
        {
            UARTEx_RxEventCallback_TASK[i].Callback = NULL;
            Debug_Log("UARTEx_RxEventCallback_TASK[%d] UnRegister:%s\r\n",i,UARTEx_RxEventCallback_TASK[i].Name);
            break;
        }
    }
    Debug_Log("UARTEx_RxEventCallback_TASK UnRegister Failed:%s————Not Found Callback\r\n  ",Name);
}
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    for (uint8_t i = 0; i < UARTEx_RX_EVENT_CALLBACK_TASK_NUM; i++)
    {
        if (UARTEx_RxEventCallback_TASK[i].Callback != NULL)
        {
            UARTEx_RxEventCallback_TASK[i].Callback(huart, Size);
        }
    }
}
#endif

#if GPIO_EXTI_CALLBACK_ENABLE
GPIO_EXTI_Callback_Item_t GPIO_EXTI_Callback_TASK[GPIO_EXTI_CALLBACK_TASK_NUM]; // GPIO外部中断回调函数数组
void GPIO_EXTI_Callback_Register(GPIO_EXTI_Callback_t fun,char *Name)
{
    for (uint8_t i = 0; i < GPIO_EXTI_CALLBACK_TASK_NUM; i++)
    {
        if (GPIO_EXTI_Callback_TASK[i].Callback == NULL)
        {
            GPIO_EXTI_Callback_TASK[i].Callback = fun;
            memcpy(GPIO_EXTI_Callback_TASK[i].Name,Name,strlen(Name));
            GPIO_EXTI_Callback_TASK[i].Name[strlen(Name)] = '\0';
            Debug_Log("GPIO_EXTI_Callback_TASK[%d] Register:%s\r\n",i,GPIO_EXTI_Callback_TASK[i].Name);
            break;
        }
    }
        Debug_Log("GPIO_EXTI_Callback_TASK Register Failed:%s————Not Found Empty Pos\r\n  ",Name);
}
void GPIO_EXTI_Callback_UnRegister(GPIO_EXTI_Callback_t fun,char *Name)
{
    for (uint8_t i = 0; i < GPIO_EXTI_CALLBACK_TASK_NUM; i++)
    {
        if (GPIO_EXTI_Callback_TASK[i].Callback == fun)
        {
            GPIO_EXTI_Callback_TASK[i].Callback = NULL;
            Debug_Log("GPIO_EXTI_Callback_TASK[%d] UnRegister:%s\r\n",i,GPIO_EXTI_Callback_TASK[i].Name);
            break;
        }
    }
    Debug_Log("GPIO_EXTI_Callback_TASK UnRegister Failed:%s————Not Found Callback\r\n  ",Name);
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    for (uint8_t i = 0; i < GPIO_EXTI_CALLBACK_TASK_NUM; i++)
    {
        if (GPIO_EXTI_Callback_TASK[i].Callback != NULL)
        {
            GPIO_EXTI_Callback_TASK[i].Callback(GPIO_Pin);
        }
    }
}
#endif
