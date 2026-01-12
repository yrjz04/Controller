/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 09:11:42
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-05 12:54:16
 * @FilePath: \Controller\Src\Hardware\Drv_Lcd\Drv_Lcd.h
 * @Description: 
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#ifndef __DRV_LCD_H__
#define __DRV_LCD_H__

#include "main.h"
typedef struct 
{
    SPI_HandleTypeDef* hspi;
    GPIO_TypeDef* CS_GPIO_Port;
    uint16_t CS_GPIO_Pin;
    GPIO_TypeDef* RST_GPIO_Port;
    uint16_t RST_GPIO_Pin;
    GPIO_TypeDef* DC_GPIO_Port;
    uint16_t DC_GPIO_Pin;
} LcdSpiTypeDef;
void Drv_Lcd_Init(void);

#endif
