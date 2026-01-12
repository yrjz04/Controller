/***
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-12 16:09:21
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-12 16:59:11
 * @FilePath: \Controller\Src\System\System_Callback.c
 * @Description: 系统回调函数汇总
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved.
 */
#include "System_Callback.h"
#include "System_Config.h"
#include "main.h"
#include "System_Debug.h"

void System_CallBack_Init(void)
{
#if TIM_PERIOD_ELAPSED_CALLBACK_ENABLE
    for (uint8_t i = 0; i < TIM_PERIOD_ELAPSED_CALLBACK_TASK_NUM; i++)
    {
        TIM_PERIOD_ELAPSED_CALLBACK_TASK[i].Callback = NULL;
        TIM_PERIOD_ELAPSED_CALLBACK_TASK[i].Name = NULL;
    }
#endif

#if UARTEx_RX_EVENT_CALLBACK_ENABLE
    for (uint8_t i = 0; i < UARTEx_RX_EVENT_CALLBACK_TASK_NUM; i++)
    {
        UARTEx_RxEventCallback_TASK[i].Callback = NULL;
        UARTEx_RxEventCallback_TASK[i].Name = NULL;
    }
#endif

#if GPIO_EXTI_CALLBACK_ENABLE
    for (uint8_t i = 0; i < GPIO_EXTI_CALLBACK_TASK_NUM; i++)
    {
        GPIO_EXTI_Callback_TASK[i].Callback = NULL;
        GPIO_EXTI_Callback_TASK[i].Name = NULL;
    }
#endif
}

void System_Print_All_CallbackName()
{
#if TIM_PERIOD_ELAPSED_CALLBACK_ENABLE
    for(uint8_t i=0;i<TIM_PERIOD_ELAPSED_CALLBACK_TASK_NUM;i++)
    {
        if(TIM_PERIOD_ELAPSED_CALLBACK_TASK[i]!=NULL)
        {
            Debug_Log("TIM_PERIOD_ELAPSED_CALLBACK_TASK[%d]:%s\r\n",i,TIM_PERIOD_ELAPSED_CALLBACK_TASK[i].Name);
        }
    }
#endif

#if UARTEx_RX_EVENT_CALLBACK_ENABLE
    for(uint8_t i=0;i<UARTEx_RX_EVENT_CALLBACK_TASK_NUM;i++)
    {
        if(UARTEx_RxEventCallback_TASK[i]!=NULL)
        {
            Debug_Log("UARTEx_RxEventCallback_TASK[%d]:%s\r\n",i,UARTEx_RxEventCallback_TASK[i].Name);
        }
    }
#endif

#if GPIO_EXTI_CALLBACK_ENABLE
    for(uint8_t i=0;i<GPIO_EXTI_CALLBACK_TASK_NUM;i++)
    {
        if(GPIO_EXTI_Callback_TASK[i]!=NULL)
        {
            Debug_Log("GPIO_EXTI_Callback_TASK[%d]:%s\r\n",i,GPIO_EXTI_Callback_TASK[i].Name);
        }
    }
#endif
}

#if TIM_PERIOD_ELAPSED_CALLBACK_ENABLE
TIM_PeriodElapsedCallback_Item_t TIM_PERIOD_ELAPSED_CALLBACK_TASK[TIM_PERIOD_ELAPSED_CALLBACK_TASK_NUM]; // 定时器周期中断回调函数数组
void TIM_PERIOD_ELAPSED_CALLBACK_Register(TIM_PeriodElapsedCallback_Item_t Callback_Item)
{
    for (uint8_t i = 0; i < TIM_PERIOD_ELAPSED_CALLBACK_TASK_NUM; i++)
    {
        if (TIM_PERIOD_ELAPSED_CALLBACK_TASK[i].Callback == NULL)
        {
            TIM_PERIOD_ELAPSED_CALLBACK_TASK[i].Callback = Callback_Item.Callback;
            TIM_PERIOD_ELAPSED_CALLBACK_TASK[i].Name = Callback_Item.Name;
            Debug_Log("TIM_PERIOD_ELAPSED_CALLBACK_TASK[%d] Register:%s\r\n",i,Callback_Item.Name);
            break;
        }
    }
        Debug_Log("TIM_PERIOD_ELAPSED_CALLBACK_TASK Register Failed:%s————Not Found Empty Pos\r\n  ",Callback_Item.Name);
}
void TIM_PERIOD_ELAPSED_CALLBACK_UnRegister(TIM_PeriodElapsedCallback_Item_t Callback_Item)
{
    for (uint8_t i = 0; i < TIM_PERIOD_ELAPSED_CALLBACK_TASK_NUM; i++)
    {
        if (TIM_PERIOD_ELAPSED_CALLBACK_TASK[i].Callback == Callback_Item.Callback)
        {
            TIM_PERIOD_ELAPSED_CALLBACK_TASK[i].Callback = NULL;
            TIM_PERIOD_ELAPSED_CALLBACK_TASK[i].Name = NULL;
            Debug_Log("TIM_PERIOD_ELAPSED_CALLBACK_TASK[%d] UnRegister:%s\r\n",i,TIM_PERIOD_ELAPSED_CALLBACK_TASK[i].Name);
            break;
        }
    }
    Debug_Log("TIM_PERIOD_ELAPSED_CALLBACK_TASK UnRegister Failed:%s————Not Found Callback\r\n  ",Callback_Item.Name);
}
void TIM_PeriodElapsedCallback_Handler(TIM_HandleTypeDef *htim)
{
    for (uint8_t i = 0; i < TIM_PERIOD_ELAPSED_CALLBACK_TASK_NUM; i++)
    {
        if (TIM_PERIOD_ELAPSED_CALLBACK_TASK[i].Callback != NULL)
        {
            TIM_PERIOD_ELAPSED_CALLBACK_TASK[i].Callback(htim);
        }
    }
}
#endif

#if UARTEx_RX_EVENT_CALLBACK_ENABLE
UARTEx_RxEventCallback_Item_t UARTEx_RxEventCallback_TASK[UARTEx_RX_EVENT_CALLBACK_TASK_NUM]; // UART接收事件回调函数数组
void UARTEx_RxEventCallback_Register(UARTEx_RxEventCallback_Item_t Callback_Item)
{
    for (uint8_t i = 0; i < UARTEx_RX_EVENT_CALLBACK_TASK_NUM; i++)
    {
        if (UARTEx_RxEventCallback_TASK[i].Callback == NULL)
        {
            UARTEx_RxEventCallback_TASK[i].Callback = Callback_Item.Callback;
            UARTEx_RxEventCallback_TASK[i].Name = Callback_Item.Name;
            Debug_Log("UARTEx_RxEventCallback_TASK[%d] Register:%s\r\n",i,Callback_Item.Name);
            break;
        }
    }
        Debug_Log("UARTEx_RxEventCallback_TASK Register Failed:%s————Not Found Empty Pos\r\n  ",Callback_Item.Name);
}
void UARTEx_RxEventCallback_UnRegister(UARTEx_RxEventCallback_Item_t Callback_Item)
{
    for (uint8_t i = 0; i < UARTEx_RX_EVENT_CALLBACK_TASK_NUM; i++)
    {
        if (UARTEx_RxEventCallback_TASK[i].Callback == Callback_Item.Callback)
        {
            UARTEx_RxEventCallback_TASK[i].Callback = NULL;
            UARTEx_RxEventCallback_TASK[i].Name = NULL;
            Debug_Log("UARTEx_RxEventCallback_TASK[%d] UnRegister:%s\r\n",i,Callback_Item.Name);
            break;
        }
    }
    Debug_Log("UARTEx_RxEventCallback_TASK UnRegister Failed:%s————Not Found Callback\r\n  ",Callback_Item.Name);
}
void UARTEx_RxEventCallback_Handler(UART_HandleTypeDef *huart, uint16_t Size)
{
    for (uint8_t i = 0; i < UARTEx_RX_EVENT_CALLBACK_TASK_NUM; i++)
    {
        if (UARTEx_RxEventCallback_TASK[i] != NULL)
        {
            UARTEx_RxEventCallback_TASK[i].Callback(huart, Size);
        }
    }
}
#endif

#if GPIO_EXTI_CALLBACK_ENABLE
GPIO_EXTI_Callback_Item_t GPIO_EXTI_Callback_TASK[GPIO_EXTI_CALLBACK_TASK_NUM]; // GPIO外部中断回调函数数组
void GPIO_EXTI_Callback_Register(GPIO_EXTI_Callback_Item_t Callback_Item)
{
    for (uint8_t i = 0; i < GPIO_EXTI_CALLBACK_TASK_NUM; i++)
    {
        if (GPIO_EXTI_Callback_TASK[i] == NULL)
        {
            GPIO_EXTI_Callback_TASK[i].Callback = Callback_Item.Callback;
            GPIO_EXTI_Callback_TASK[i].Name = Callback_Item.Name;
            Debug_Log("GPIO_EXTI_Callback_TASK[%d] Register:%s\r\n",i,Callback_Item.Name);
            break;
        }
    }
        Debug_Log("GPIO_EXTI_Callback_TASK Register Failed:%s————Not Found Empty Pos\r\n  ",Callback_Item.Name);
}
void GPIO_EXTI_Callback_UnRegister(GPIO_EXTI_Callback_Item_t Callback_Item)
{
    for (uint8_t i = 0; i < GPIO_EXTI_CALLBACK_TASK_NUM; i++)
    {
        if (GPIO_EXTI_Callback_TASK[i] == Callback_Item)
        {
            GPIO_EXTI_Callback_TASK[i].Callback = NULL;
            GPIO_EXTI_Callback_TASK[i].Name = NULL;
            Debug_Log("GPIO_EXTI_Callback_TASK[%d] UnRegister:%s\r\n",i,Callback_Item.Name);
            break;
        }
    }
    Debug_Log("GPIO_EXTI_Callback_TASK UnRegister Failed:%s————Not Found Callback\r\n  ",Callback_Item.Name);
}
void GPIO_EXTI_Callback_Handler(uint16_t GPIO_Pin)
{
    for (uint8_t i = 0; i < GPIO_EXTI_CALLBACK_TASK_NUM; i++)
    {
        if (GPIO_EXTI_Callback_TASK[i] != NULL)
        {
            GPIO_EXTI_Callback_TASK[i].Callback(GPIO_Pin);
        }
    }
}
#endif
