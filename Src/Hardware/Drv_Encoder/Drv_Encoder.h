/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 09:11:18
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-05 12:08:00
 * @FilePath: \Controller\Src\Hardware\Drv_Encoder\Drv_Encoder.h
 * @Description: 
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#ifndef __DRV_ENCODER_H__
#define __DRV_ENCODER_H__

#include "main.h"

typedef struct 
{
    int32_t  		Count;
    GPIO_TypeDef* 	A_GPIO_Port;
    uint16_t 		A_GPIO_Pin;
    GPIO_TypeDef* 	B_GPIO_Port;
    uint16_t 		B_GPIO_Pin;
    GPIO_TypeDef* 	Key_GPIO_Port;
	uint16_t 		Key_GPIO_Pin;

	uint8_t 		EXTI_Flag;              // 中断边沿处理标志（0：未处理，1：待处理）
    uint8_t 		Falling_B_Level;        // A相下降沿时B相的电平值
    uint8_t 		Rising_B_Level;         // A相上升沿时B相的电平值
	
    // 按键处理
	unsigned char 	IsKeyPush;
	
    uint32_t 		last_trigger_time;  	// 按键上次触发时间（ms）
    uint16_t 		debounce_ms;        	// 消抖阈值（建议20ms）
    uint8_t 		debounce_flag;       	// 消抖完成标志
    uint8_t 		key_press_flag;      	// 按键按下标志（边沿标记）
    uint8_t 		click_cnt;           	// 单击计数（用于双击检测）
    uint32_t 		longpress_time;     	// 长按计时（ms）
    uint16_t 		longpress_ms;       	// 长按阈值（500ms）
    uint16_t 		double_click_ms;   	 	// 双击检测窗口（300ms）
	uint32_t		first_click_time;      	// 第一次单击时间（双击检测用）
	
	void 			(*Callback)(void);
    void 			(*Key_Callback)(void);
} EncoderTypeDef;

extern EncoderTypeDef ENCODE_Motor;
extern EncoderTypeDef ENCODE_Heater;

void Encoder_Key_Check(void);
void Encoder_Handler(void);

#endif
