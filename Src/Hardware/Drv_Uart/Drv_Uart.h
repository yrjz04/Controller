/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 11:01:50
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-05 11:49:46
 * @FilePath: \Controller\Src\Hardware\Drv_Uart\Drv_Uart.h
 * @Description: 
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include "main.h"
#include "stdio.h"
#include "System/System_Config.h"
 
typedef struct {
    UART_HandleTypeDef *huart;
    DMA_HandleTypeDef *hdma_rx;
    uint8_t RxBuffer[RX_BUFFER_SIZE];
    uint8_t RxData;
    uint16_t RxDataCnt;
    uint8_t UseDMA;
}UART_RxTypeDef;
 
extern UART_RxTypeDef Uart1;   // 为UART1声明外部结构体变量
extern UART_RxTypeDef Uart2;   // 为UART2声明外部结构体变量
 
void Uart_Init(UART_RxTypeDef *UartRx);


#endif
