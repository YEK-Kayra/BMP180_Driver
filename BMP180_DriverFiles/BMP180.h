/*!
 *  @file : BMP180.c
 *  @date : 8-09-2023
 *  @version : v1.0.0
 *
 *      Author: Yunus Emre KAYRA (https://github.com/YEK-Kayra)
 ******************************************************************************
 * 	@attention
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2023 TAISAT Turkish Artificial Intelligence Supported Autonomous Technologies
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef INC_BMP180_H_
#define INC_BMP180_H_

#include "main.h"

/****************************************************************/
/*		      General Macro Definitions             */
/****************************************************************/
/**I2C WRITE&READ ADDRESS*/
#define BMP180_DEVICE_I2C_WRITE_ADDRESS 0xEE
#define BMP180_DEVICE_I2C_READ_ADDRESS  0xEF

/**BMP180 CALIBRATION DATAS*/
#define CalibrationCoefficient_Lenght 22
#define Calibration_Reg_Start_Address 0xAA

/**SAMPLING SETTINGS*/
/**
 *   Modes..................| Ultra Low Power | Standard | High Resolation | Ultra High Resolation |
 *   Number of Mode.........|        0        |     1    |        2        |          3            |
 */
#define OverSamplingSetting 3 //Number of Mode

/**Definations Constant Altitude Parameters*/
#define SeaLevelTemp   288.15
#define GradientTemp   0.0065
#define SeaLevelPress  101325
#define GravityAccel   9.80665
#define GasCoefficient 287.05



/******************************************************************************/
/*         			BMP180 Function prototypes            				*/
/******************************************************************************/


/**
 * @fn     HAL_StatusTypeDef BMP180_Init(I2C_HandleTypeDef *hi2c)
 * @brief  This function provide to check the I2C bus is suitable to communicate. If not Warning Led is HIGH									@arg "3" 64 Byte Operations
 * @retval HAL Status
 */
HAL_StatusTypeDef BMP180_Init(I2C_HandleTypeDef *hi2c);


/**
 * @fn     HAL_StatusTypeDef BMP180_Get_And_Check_CalibrationDatas(void)
 * @brief  This function provide to check the Calibration Datas after read from sensor's EEPROM. If any value is 0x00 or 0xFF Warning Led is HIGH
 * @retval HAL Status
 */
HAL_StatusTypeDef BMP180_Get_And_Check_CalibrationDatas(void);


/**
 * @fn     long BMP180_Get_TempatureDatas(void)
 * @brief  This function provide to get Real Temperature Values by using Uncompensated Temperature Values
 * @retval Real_Temperature
 */
float BMP180_Get_TempatureDatas(void);


/**
 * @fn     long BMP180_Get_PressureDatas()
 * @brief  This function provide to get Real Pressure Values by using Uncompensated Pressure Values
 * @retval Real_Pressure
 */
float BMP180_Get_PressureDatas(void);


/**
 * @fn     float BMP180_Get_SeaAltitudeDatas(void)
 * @brief  This function provide to calculate Real SeaLevelAltitude values by using  Real_Pressure Values
 * @retval Real SeaLevel Altitudes
 */
float BMP180_Get_AltitudeDatas(void);


#endif /* INC_BMP180_H_ */
