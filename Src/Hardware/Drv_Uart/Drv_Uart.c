/***
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 11:01:46
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-12 21:54:37
 * @FilePath: \Controller\Src\Hardware\Drv_Uart\Drv_Uart.c
 * @Description: 初始化UART1和UART2，收到消息后自动回传
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved.
 */
#include "Drv_Uart.h"
#include "Middleware/Protocol/Protocol.h"
#include "System/System_Config.h"
#include "main.h"
#include "stm32f1xx_hal_uart.h"
#include "System/System_Callback.h"

extern DMA_HandleTypeDef hdma_usart2_rx;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

#if UART1_ENABLE
void UART1_RxCallback(UART_HandleTypeDef *huart, uint16_t Size);
#if UART1_DMA_ENABLE
UART_RxTypeDef Uart1 = {&huart1, &hdma_usart1_rx, {0}, 0, 0, UART1_DMA_ENABLE, UART1_RxCallback}; // 为UART1初始化结构体
#else
UART_RxTypeDef Uart1 = {&huart1, NULL, {0}, 0, 0, UART1_DMA_ENABLE, UART1_RxCallback}; // 为UART1初始化结构体
#endif

#endif
#if UART2_ENABLE
void UART2_RxCallback(UART_HandleTypeDef *huart, uint16_t Size);
#if UART2_DMA_ENABLE
UART_RxTypeDef Uart2 = {&huart2, &hdma_usart2_rx, {0}, 0, 0, UART2_DMA_ENABLE, UART2_RxCallback}; // 为UART2初始化结构体
#else
UART_RxTypeDef Uart2 = {&huart2, NULL, {0}, 0, 0, UART2_DMA_ENABLE, UART2_RxCallback}; // 为UART2初始化结构体
#endif
#endif

// 重定向c库函数printf到huart1
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}
int fgetc(FILE *f)
{
    uint8_t ch = 0;
    HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
    return ch;
}

void Uart_Init(UART_RxTypeDef *UartRx)
{
    if (UartRx->UseDMA)
    {
        HAL_UARTEx_ReceiveToIdle_DMA(UartRx->huart, UartRx->RxBuffer,
                                     RX_BUFFER_SIZE);
        __HAL_DMA_DISABLE_IT(UartRx->hdma_rx, DMA_IT_HT);
    }
    else
    {
        HAL_UARTEx_ReceiveToIdle_IT(UartRx->huart, UartRx->RxBuffer,
                                    RX_BUFFER_SIZE);
    }
    UARTEx_RX_EVENT_CALLBACK_Register(UartRx->RxCallback,"UART_RxCallback");
}

#if UART1_ENABLE
void UART1_RxCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    #if UART1_DMA_ENABLE
    if (huart->Instance == Uart1.huart->Instance)
    {
        HAL_UART_Transmit_DMA(Uart1.huart, Uart1.RxBuffer, Size);
#if USE_UART1_DEBUG
        protocol_data_recv(Uart1.RxBuffer, Size);
#endif
        HAL_UARTEx_ReceiveToIdle_DMA(Uart1.huart, Uart1.RxBuffer, RX_BUFFER_SIZE);
        __HAL_DMA_DISABLE_IT(Uart1.hdma_rx, DMA_IT_HT);
    }
#else
    if (huart->Instance == Uart1.huart->Instance)
    {
        HAL_UART_Transmit(Uart1.huart, Uart1.RxBuffer, Size, 0xFFFF);
#if USE_UART1_DEBUG
        protocol_data_recv(Uart1.RxBuffer, Size);
#endif
        HAL_UARTEx_ReceiveToIdle_IT(&huart1, Uart1.RxBuffer, RX_BUFFER_SIZE);
    }
#endif
}
#endif

#if UART2_ENABLE
void UART2_RxCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
#if UART2_NODMA_ENABLE
    if (huart->Instance == Uart2.huart->Instance)
    {
        HAL_UART_Transmit(Uart2.huart, Uart2.RxBuffer, Size, 0xFFFF);
#if USE_UART2_DEBUG
        protocol_data_recv(Uart2.RxBuffer, Size);
#endif
        HAL_UARTEx_ReceiveToIdle_IT(Uart2.huart, Uart2.RxBuffer, RX_BUFFER_SIZE);
    }
#endif
#if UART2_DMA_ENABLE
    if (huart->Instance == Uart2.huart->Instance)
    {
        HAL_UART_Transmit_DMA(Uart2.huart, Uart2.RxBuffer, Size);

        HAL_UARTEx_ReceiveToIdle_DMA(Uart2.huart, Uart2.RxBuffer, RX_BUFFER_SIZE);
#if USE_UART2_DEBUG
        protocol_data_recv(Uart2.RxBuffer, Size);
#endif
        __HAL_DMA_DISABLE_IT(Uart2.hdma_rx, DMA_IT_HT);
    }
#endif
}
#endif

void UART_Send_Byte(char Byte)
{
#if USE_UART1_DEBUG
    HAL_UART_Transmit(&huart1, (uint8_t *)&Byte, 1, 0xFFFF);
#endif
#if USE_UART2_DEBUG
    HAL_UART_Transmit(&huart2, (uint8_t *)&Byte, 1, 0xFFFF);
#endif
}
