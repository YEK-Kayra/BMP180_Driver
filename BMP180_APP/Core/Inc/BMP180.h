/*
 * BMP180.h
 *
 *  Created on: Jul 24, 2023
 *      Author: TAISAT MARM-99
 */

#ifndef INC_BMP180_H_
#define INC_BMP180_H_

#include "main.h"

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

extern I2C_HandleTypeDef hi2c1;

//**BMP180 STARTED FUNCTIONS*/


/**
 * @fn     HAL_StatusTypeDef BMP180_Init(void)
 * @brief  This function provide to check the I2C bus is suitable to communicate. If not Warning Led is HIGH									@arg "3" 64 Byte Operations
 * @retval HAL Status
 */
HAL_StatusTypeDef BMP180_Init(void);


/**
 * @fn     HAL_StatusTypeDef BMP180_Get_And_Check_CalibrationDatas(void)
 * @brief  This function provide to check the Calibration Datas after read from sensor's EEPROM. If any value is 0x00 or 0xFF Warning Led is HIGH
 * @retval HAL Status
 */
HAL_StatusTypeDef BMP180_Get_And_Check_CalibrationDatas(void);


//**BMP180 SENSOR DATAS FUNCTIONS*/
/**
 * @fn     long BMP180_Get_TempatureDatas()
 * @brief  This function provide to get Real Temperature Values by using Uncompensated Temperature Values
 * @retval Real_Temperature
 */
long BMP180_Get_TempatureDatas(void);


/**
 * @fn     long BMP180_Get_PressureDatas()
 * @brief  This function provide to get Real Pressure Values by using Uncompensated Pressure Values
 * @retval Real_Pressure
 */
long BMP180_Get_PressureDatas(void);


/**
 * @fn     long BMP180_Get_AltitudeDatas(void)
 * @brief  This function provide to calculate Real Altitude Values by using  Real_Pressure Values
 * @retval Real_Pressure
 */
long BMP180_Get_AltitudeDatas(void);








#endif /* INC_BMP180_H_ */
