/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 09:10:57
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-05 11:53:50
 * @FilePath: \Controller\Src\Hardware\Drv_Bluetooth\Drv_Bluetooth.c
 * @Description: 
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#include "main.h"
#include "stdint.h"
#include "string.h"
#include "Drv_Bluetooth.h"
#include "Hardware/Drv_Uart/Drv_Uart.h"
#include "System/System_DataPool.h"

UART_RxTypeDef* Bluetooth_Uart = &Uart2;

void Drv_Bluetooth_Init(void)
{
    Uart_Init(Bluetooth_Uart);
}

void Drv_Bluetooth_Transmit(uint8_t *Data, uint16_t Len)
{
    HAL_UART_Transmit_DMA(Bluetooth_Uart->huart, Data, Len);
}

void Drv_Bluetooth_GetData(uint8_t *Data, uint16_t Len)
{
    memcpy(Data, Bluetooth_Uart->RxBuffer, Len);
}
