/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 11:34:48
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-05 12:48:02
 * @FilePath: \Controller\Src\Hardware\Drv_Spi\Drv_Spi.h
 * @Description: 
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__
#include "main.h"
typedef struct 
{
    SPI_HandleTypeDef* hspi;
    GPIO_TypeDef* CS_GPIO_Port;
    uint16_t CS_GPIO_Pin;
} SpiTypeDef;


#endif
