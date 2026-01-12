/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 14:32:11
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-12 21:45:53
 * @FilePath: \Controller\Src\Middleware\MTimer\MTimer.c
 * @Description: 
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#include "MTimer.h"
#include "main.h"
#include "stm32f1xx_hal_tim.h"
#include "System/System_Callback.h"

extern TIM_HandleTypeDef htim1;
uint8_t MTimer_Flag = 0;
TIM_PeriodElapsedCallback_t TIM_PeriodElapsedCallback = MTimer_Callback;

void MTimer_Init(void)
{
    __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_UPDATE);
    HAL_TIM_Base_Start(&htim1);
    TIM_PERIOD_ELAPSED_CALLBACK_Register(TIM_PeriodElapsedCallback,"MTimer_Callback");
}
void MTimer_Callback(TIM_HandleTypeDef *htim)   //中断20ms一次，标志位置1
{
    if(htim == &htim1)
    {
        MTimer_Flag = 1;
    }
}
