/*** 
 * @Author: yrjz yrjz04@outlook.com
 * @Date: 2026-01-05 09:12:07
 * @LastEditors: yrjz yrjz04@outlook.com
 * @LastEditTime: 2026-01-05 16:01:50
 * @FilePath: \Controller\Src\Hardware\Drv_Sensor\Drv_Sensor.c
 * @Description: 
 * @
 * @Copyright (c) 2026 by yrjz04@outlook.com, All Rights Reserved. 
 */
#include "Drv_Sensor.h"
#include "max6675.h"
#include "System/System_DataPool.h"
extern ThermoCouple thermo;
void Drv_Sensor_Update(void)
{
    ReadThermoCouple(&thermo);
    NowTempture = thermo.Thx_celcius;
	//NowTempture = 250;
}
