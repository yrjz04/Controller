/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 09:11:00
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-05 09:29:31
 * @FilePath: \Controller\Src\Hardware\Drv_Bluetooth\Drv_Bluetooth.h
 * @Description: 
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#ifndef __DRV_BLUETOOTH_H__
#define __DRV_BLUETOOTH_H__

#include "main.h"

void Drv_Bluetooth_Init(void);
void Drv_Bluetooth_Transmit(uint8_t *Data, uint16_t Len);
void Drv_Bluetooth_GetData(uint8_t *Data, uint16_t Len);

#endif
