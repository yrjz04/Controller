#include "System_Debug.h"
#include "stdio.h"
#include "main.h"
#include "System_Config.h"

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