/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 09:11:18
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-05 15:39:02
 * @FilePath: \Controller\Src\Hardware\Drv_Lcd\Drv_Lcd.c
 * @Description: 
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#include "Drv_Lcd.h"
#include "uc1609.h"
extern LcdSpiTypeDef Lcd_Spi;

void Drv_Lcd_Init(void)
{
  	lcd_init();
	lcd_cls(1);
	HAL_Delay(1000);
	lcd_cls(0);
	display_list_char(0, 0, "LCD INIT OK!", 0);
	HAL_SPI_Transmit_DMA(Lcd_Spi.hspi, disp_buf, 1536);  
	HAL_Delay(500);
	lcd_cls(0);
	HAL_SPI_Transmit_DMA(Lcd_Spi.hspi, disp_buf, 1536);  
	display_list_char(0,0,"nowtmp:    C",0);
	display_list_char(96,0,"destmp:    C",0);
	display_list_char(0,32,"nowspeed:    ",0);
	display_list_char(96,32,"desspeed:    ",0);
	HAL_SPI_Transmit_DMA(Lcd_Spi.hspi, disp_buf, 1536);  
}
