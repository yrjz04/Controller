/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-12 20:55:29
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-12 21:14:15
 * @FilePath: \Controller\Src\System\System_Debug.c
 * @Description: 
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#include "System_Debug.h"
#include "stdio.h"
#include "main.h"
#include "System_Config.h"
#include <stdarg.h>
#include "string.h"
extern UART_HandleTypeDef huart1;
void Debug_Log(char *fmt, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
#if DEBUG_ENABLE
    HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), 0xFFFF);
#endif
}
