/***
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 09:12:12
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-05 15:37:42
 * @FilePath: \Controller\Src\Hardware\Drv_Encoder\Drv_Encoder.c
 * @Description:
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved.
 */
#include "Drv_Encoder.h"
#include "main.h"
#include "System/System_Config.h"
#include "System/System_DataPool.h"

// 电机编码器初始化
EncoderTypeDef ENCODE_Motor = {
    /* 计数 */
    .Count = 0,
    
    /* GPIO引脚配置 */
    .A_GPIO_Port 			= ENCODE0_A_GPIO_Port,
    .A_GPIO_Pin  			= ENCODE0_A_Pin,
    .B_GPIO_Port 			= ENCODE0_B_GPIO_Port,
    .B_GPIO_Pin  			= ENCODE0_B_Pin,
    .Key_GPIO_Port 			= ENCODE0_KEY_GPIO_Port,
    .Key_GPIO_Pin  			= ENCODE0_KEY_Pin,
    
    /* 中断/电平标志（初始化为0） */
    .EXTI_Flag        		= 0,
    .Falling_B_Level  		= 0,
    .Rising_B_Level   		= 0,
    
    /* 按键处理标志（初始化为0） */
    .debounce_ms 			= 10,      // 消抖阈值20ms
    .longpress_ms 			= 500,     // 长按阈值500ms
    .double_click_ms	 	= 300,     // 双击检测窗口300ms
    .last_trigger_time 		= 0,
    .debounce_flag 			= 0,	
    .key_press_flag 		= 0,
    .click_cnt 				= 0,
    .longpress_time 		= 0,
    .IsKeyPush 				= 0,
	
    /* 回调函数 */
    .Callback       		= NULL,
    .Key_Callback   		= NULL
};

// 加热器编码器初始化
EncoderTypeDef ENCODE_Heater = {
    /* 计数 */
    .Count 					= 0,

    /* GPIO引脚配置 */
    .A_GPIO_Port 			= ENCODE1_A_GPIO_Port,
    .A_GPIO_Pin  			= ENCODE1_A_Pin,
    .B_GPIO_Port 			= ENCODE1_B_GPIO_Port,
    .B_GPIO_Pin  			= ENCODE1_B_Pin,
    .Key_GPIO_Port 			= ENCODE1_KEY_GPIO_Port,
    .Key_GPIO_Pin  			= ENCODE1_KEY_Pin,
    
    /* 中断/电平标志（初始化为0） */
    .EXTI_Flag        		= 0,
    .Falling_B_Level  		= 0,
    .Rising_B_Level   		= 0,
    
    /* 按键处理标志（初始化为0） */
    .debounce_ms 			= 10,      // 消抖阈值20ms
    .longpress_ms 			= 500,     // 长按阈值500ms
    .double_click_ms	 	= 300,     // 双击检测窗口300ms
    .last_trigger_time 		= 0,
    .debounce_flag 			= 0,	
    .key_press_flag 		= 0,
    .click_cnt 				= 0,
    .longpress_time 		= 0,
    .IsKeyPush 				= 0,
    
    /* 回调函数 */
    .Callback       		= NULL,
    .Key_Callback   		= NULL
};


uint32_t current_time;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
#if ENCODE_MOTOR_ENABLE
	current_time = HAL_GetTick(); // 获取当前系统时间（ms）
    if (GPIO_Pin == ENCODE_Motor.A_GPIO_Pin)
    {
		if(HAL_GPIO_ReadPin(ENCODE_Motor.A_GPIO_Port,ENCODE_Motor.A_GPIO_Pin) == 0 && ENCODE_Motor.EXTI_Flag == 0)//先处理下降沿中断
		{
			ENCODE_Motor.EXTI_Flag = 1;
			ENCODE_Motor.Falling_B_Level = HAL_GPIO_ReadPin(ENCODE_Motor.B_GPIO_Port,ENCODE_Motor.B_GPIO_Pin);
		}
		else if(HAL_GPIO_ReadPin(ENCODE_Motor.A_GPIO_Port,ENCODE_Motor.A_GPIO_Pin) == 1 && ENCODE_Motor.EXTI_Flag == 1){	//后处理上升沿中断
		
			ENCODE_Motor.EXTI_Flag = 0;
			ENCODE_Motor.Rising_B_Level = HAL_GPIO_ReadPin(ENCODE_Motor.B_GPIO_Port,ENCODE_Motor.B_GPIO_Pin);
			if(ENCODE_Motor.Falling_B_Level == 1 && ENCODE_Motor.Rising_B_Level == 0)
			{
				ENCODE_Motor.Count++; // 顺时针
			}
			else if(ENCODE_Motor.Falling_B_Level == 0 && ENCODE_Motor.Rising_B_Level == 1)
			{
				ENCODE_Motor.Count--; // 逆时针		
			}
		}
    }
	if(GPIO_Pin == ENCODE_Motor.Key_GPIO_Pin)
	{
		// 消抖判断
		if(current_time - ENCODE_Motor.last_trigger_time < ENCODE_Motor.debounce_ms)
		{
			return;
		}
		ENCODE_Motor.last_trigger_time = current_time;
		
		// 读取按键电平
		uint8_t key_level = HAL_GPIO_ReadPin(ENCODE_Motor.Key_GPIO_Port, ENCODE_Motor.Key_GPIO_Pin);
		
		// 按键按下（下降沿，低电平有效）
		if(key_level == GPIO_PIN_RESET && ENCODE_Motor.key_press_flag == 0)
		{
			ENCODE_Motor.key_press_flag = 1;          		// 标记按下边沿（类似AB相下降沿）
			ENCODE_Motor.longpress_time = current_time; 	// 记录长按起始时间
		}
		// 按键释放（上升沿）
		else if(key_level == GPIO_PIN_SET && ENCODE_Motor.key_press_flag == 1)
		{
			ENCODE_Motor.key_press_flag = 0;          		// 标记释放边沿
			
			if(current_time - ENCODE_Motor.longpress_time >= ENCODE_Motor.longpress_ms)
			{
				ENCODE_Motor.IsKeyPush = 3;            // 标记长按事件
				ENCODE_Motor.click_cnt = 0;            // 长按后重置单击计数
				if(ENCODE_Motor.Callback != NULL) {
					ENCODE_Motor.Callback();          // 长按回调
				}
			}
			else
			{
				ENCODE_Motor.click_cnt++;              // 单击计数+1
				
				// 第一次单击：记录时间，暂不触发事件（等待双击）
				if (ENCODE_Motor.click_cnt == 1)
				{
					ENCODE_Motor.first_click_time = current_time;
				}
				// 第二次单击：判断是否在双击时间窗口内
				else if (ENCODE_Motor.click_cnt == 2)
				{
					// 双击有效：触发双击事件
					if (current_time - ENCODE_Motor.first_click_time < ENCODE_Motor.double_click_ms)
					{
						ENCODE_Motor.IsKeyPush = 2;    // 标记双击事件
						if (ENCODE_Motor.Callback != NULL) {
							ENCODE_Motor.Callback();  // 双击回调
						}
					}
					// 双击超时：视为两次独立单击
					else
					{
						ENCODE_Motor.IsKeyPush = 1;    // 标记单击事件
						if (ENCODE_Motor.Callback != NULL) {
							ENCODE_Motor.Callback();  // 单击回调
						}
					}
					ENCODE_Motor.click_cnt = 0;        // 重置计数
				}
			}		
		}
	}
#endif

#if ENCODE_HEATER_ENABLE
    if (GPIO_Pin == ENCODE_Heater.A_GPIO_Pin)
    {
		if(HAL_GPIO_ReadPin(ENCODE_Heater.A_GPIO_Port,ENCODE_Heater.A_GPIO_Pin) == 0 && ENCODE_Heater.EXTI_Flag == 0)//先处理下降沿中断
		{
			ENCODE_Heater.EXTI_Flag = 1;
			ENCODE_Heater.Falling_B_Level = HAL_GPIO_ReadPin(ENCODE_Heater.B_GPIO_Port,ENCODE_Heater.B_GPIO_Pin);
		}
		else if(HAL_GPIO_ReadPin(ENCODE_Heater.A_GPIO_Port,ENCODE_Heater.A_GPIO_Pin) == 1 && ENCODE_Heater.EXTI_Flag == 1){	//后处理上升沿中断
		
			ENCODE_Heater.EXTI_Flag = 0;
			ENCODE_Heater.Rising_B_Level = HAL_GPIO_ReadPin(ENCODE_Heater.B_GPIO_Port,ENCODE_Heater.B_GPIO_Pin);
			if(ENCODE_Heater.Falling_B_Level == 1 && ENCODE_Heater.Rising_B_Level == 0)
			{
				ENCODE_Heater.Count++; // 顺时针
			}
			else if(ENCODE_Heater.Falling_B_Level == 0 && ENCODE_Heater.Rising_B_Level == 1)
			{
				ENCODE_Heater.Count--; // 逆时针		
			}
		}
    }
	if(GPIO_Pin == ENCODE_Heater.Key_GPIO_Pin)
	{
		// 消抖判断
		if (current_time - ENCODE_Heater.last_trigger_time < ENCODE_Heater.debounce_ms)
		{
			return;
		}
		ENCODE_Heater.last_trigger_time = current_time;
		
		// 读取按键电平
		uint8_t key_level = HAL_GPIO_ReadPin(ENCODE_Heater.Key_GPIO_Port, ENCODE_Heater.Key_GPIO_Pin);
		
		// 按键按下（下降沿，低电平有效）
		if(key_level == GPIO_PIN_RESET && ENCODE_Heater.key_press_flag == 0)
		{
			ENCODE_Heater.key_press_flag = 1;          		// 标记按下边沿（类似AB相下降沿）
			ENCODE_Heater.longpress_time = current_time; 	// 记录长按起始时间
		}
		// 按键释放（上升沿）
		else if(key_level == GPIO_PIN_SET && ENCODE_Heater.key_press_flag == 1)
		{
			ENCODE_Heater.key_press_flag = 0;          		// 标记释放边沿
			
			if(current_time - ENCODE_Heater.longpress_time >= ENCODE_Heater.longpress_ms)
			{
				ENCODE_Heater.IsKeyPush = 3;            // 标记长按事件
				ENCODE_Heater.click_cnt = 0;            // 长按后重置单击计数
				if(ENCODE_Heater.Callback != NULL) {
					ENCODE_Heater.Callback();          // 长按回调
				}
			}
			else
			{
				ENCODE_Heater.click_cnt++;              // 单击计数+1
				
				// 第一次单击：记录时间，暂不触发事件（等待双击）
				if (ENCODE_Heater.click_cnt == 1)
				{
					ENCODE_Heater.first_click_time = current_time;
				}
				// 第二次单击：判断是否在双击时间窗口内
				else if (ENCODE_Heater.click_cnt == 2)
				{
					// 双击有效：触发双击事件
					if (current_time - ENCODE_Heater.first_click_time < ENCODE_Heater.double_click_ms)
					{
						ENCODE_Heater.IsKeyPush = 2;    // 标记双击事件
						if (ENCODE_Heater.Callback != NULL) {
							ENCODE_Heater.Callback();  // 双击回调
						}
					}
					// 双击超时：视为两次独立单击
					else
					{
						ENCODE_Heater.IsKeyPush = 1;    // 标记单击事件
						if (ENCODE_Heater.Callback != NULL) {
							ENCODE_Heater.Callback();  // 单击回调
						}
					}
					ENCODE_Heater.click_cnt = 0;        // 重置计数
				}
			}		
		}
	}
#endif
}

void Encoder_Key_Check(void)
{
    uint32_t current_time = HAL_GetTick();  // 获取系统时间（ms）
    
    // 检测第一次单击后超时未触发第二次：判定为单击
    if (ENCODE_Motor.click_cnt == 1 && current_time - ENCODE_Motor.first_click_time > ENCODE_Motor.double_click_ms)
    {
        ENCODE_Motor.IsKeyPush = 1;            	// 标记单击事件
        if (ENCODE_Motor.Callback != NULL) {
            ENCODE_Motor.Callback();          	// 单击回调
        }
        ENCODE_Motor.click_cnt = 0;            	// 重置计数
    }
	
    // 检测第一次单击后超时未触发第二次：判定为单击
    if (ENCODE_Heater.click_cnt == 1 && current_time - ENCODE_Heater.first_click_time > ENCODE_Heater.double_click_ms)
    {
        ENCODE_Heater.IsKeyPush = 1;            	// 标记单击事件
        if (ENCODE_Heater.Callback != NULL) {
            ENCODE_Heater.Callback();          	// 单击回调
        }
        ENCODE_Heater.click_cnt = 0;            	// 重置计数
    }	
}

void Encoder_Callback_Resister(EncoderTypeDef *Encoder, void (*Callback)(void))
{
    Encoder->Callback = Callback;
}

void Encoder_Handler(void)
{
	if(ENCODE_Motor.Count != 0)
	{
		if(!Motor_Lock) 
		{
			DesSpeed += ENCODE_Motor.Count * MOTOR_SPEED_STEP;      //未上锁时，才可以修改速度
		}
        //ENCODE_Motor.Count = 0;
	}
	if(ENCODE_Heater.Count != 0)
	{
		if(!Heater_Lock)
		{
			DesTempture += ENCODE_Heater.Count * HEATER_TEMP_STEP;  //未上锁时，才可以修改温度
        }
        ENCODE_Heater.Count = 0;
	}
	
	if(ENCODE_Motor.IsKeyPush)				//按下按键即确认温度，不反色显示
	{
		ENCODE_Motor.IsKeyPush = 0;
		Motor_Lock = ~Motor_Lock;
	}	
	if(ENCODE_Heater.IsKeyPush)             //按下按键即确认温度，不反色显示
	{
		ENCODE_Heater.IsKeyPush = 0;
		Heater_Lock = ~Heater_Lock;
	}
\
}
