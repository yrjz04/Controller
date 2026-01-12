/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 09:16:33
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-05 16:30:18
 * @FilePath: \Controller\Src\System\Application.c
 * @Description: 
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#include "stdio.h"
#include "Application.h"
#include "Middleware/MTimer/MTimer.h"
#include "Middleware/Pid/Pid.h"
#include "Middleware/Protocol/Protocol.h"
#include "Hardware/Drv_Uart/Drv_Uart.h"
#include "Hardware/Drv_Bluetooth/Drv_Bluetooth.h"
#include "Hardware/Drv_Encoder/Drv_Encoder.h"
#include "Hardware/Drv_Heater/Drv_Heater.h"
#include "Hardware/Drv_Lcd/Drv_Lcd.h"
#include "Hardware/Drv_Lcd/uc1609.h"
#include "Hardware/Drv_Motor/Drv_Motor.h"
#include "Hardware/Drv_Sensor/Drv_Sensor.h"
#include "System/System_DataPool.h"
#include "System/System_Config.h"



extern uint8_t MTimer_Flag;
extern LcdSpiTypeDef Lcd_Spi;
UART_RxTypeDef* Debug_UART = &Uart1;

char DesSpeedStr[10],DesTemptureStr[10],NowSpeedStr[10],NowTemptureStr[10];

void Sys_Init(void)
{
	protocol_init();			//野火上位机
	Uart_Init(Debug_UART);
    MTimer_Init();				//定时器产生20ms中断
	Drv_Bluetooth_Init();	    //串口初始化DMA不定长
    // Drv_Encoder_Init();
    Drv_Heater_Init();		    //加热PWM初始化，频率120 KHz，占空比0-100%，步长1%
	Drv_Motor_Init();			//电机PWM初始化，频率120 KHz，占空比0-100%，步长1%
	Drv_Lcd_Init();				//Lcd初始化，并显示不变的UI
    PID_Init(&Heater_pid, DEFAULT_TARGET_TEMP);
    // Drv_Sensor_Init();
}

void Sys_Task(void)
{
	Encoder_Key_Check();		//确认单击，避免双击误判
    Encoder_Handler();			//这里更新DesTempture和DesSpeed			
	receiving_process();		//野火上位机
    if(MTimer_Flag)             //20ms周期到
    {
        MTimer_Flag = 0;
        //读取传感器数据
        Drv_Sensor_Update();        //这里更新了NowTempture
        set_computer_value(SEND_FACT_CMD,CURVES_CH1,&NowTempture,1);
        //UI界面
        sprintf(NowSpeedStr,"%d",NowSpeed);
        sprintf(NowTemptureStr,"%d",NowTempture);
        if(!Heater_Lock)
        {
            sprintf(DesTemptureStr,"%d",DesTempture);
        }
        if(!Motor_Lock)
        {
            sprintf(DesSpeedStr,"%d",DesSpeed);
        }
        display_list_char(42,0,NowTemptureStr,0);
        display_list_char(138,0,DesTemptureStr,Heater_Lock?0:1);
        display_list_char(42,32,NowSpeedStr,0);
        display_list_char(138,32,DesSpeedStr,Motor_Lock?0:1);          //如果在可修改状态，则反色显示
        //刷新LCD
        HAL_SPI_Transmit_DMA(Lcd_Spi.hspi, disp_buf, 1536);   
        //计算Pid
        Heater_pid.target = DesTempture;
        Heater_pid.current = NowTempture;
        float power = PID_Calculate(&Heater_pid, NowTempture);
        //控制加热器功率
        if(Heater_Lock)                 //不修改温度时，才可以修改功率
        {
			if(power > 99)
			{
				power = 99;				//限幅
			}			
            Drv_Heater_SetPower(power);
        }
        //控制电机速度
        if(!Motor_Lock)                 //不修改速度时，才可以修改速度
        {
			if(DesSpeed > 32)
			{
				DesSpeed = 32;			//电机驱动电压直流110V，220V整流后是311V，所以要限幅
			}
            Drv_Motor_SetSpeed(DesSpeed);
        }
    }
}
