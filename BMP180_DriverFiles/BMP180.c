/*!
 * BMP180.h
 *
 * Author: Yunus Emre KAYRA (github.com/YEK-Kayra)
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2023 TAISAT Turkish Artificial Intelligence Supported Autonomous Technologies
 *
 */


/**Include Header Files*/
#include "BMP180.h"
#include "math.h"


extern I2C_HandleTypeDef hi2c1;


/**Constant Calibration Variables*/
short  AC1;
short  AC2;
short  AC3;
unsigned short AC4;
unsigned short AC5;
unsigned short AC6;
short  B1;
short  B2;
short  MB;
short  MC;
short  MD;

/**Temperatures Variables*/
long X1;
long X2;
long B5;
long Uncompensated_Temperature;
float Real_Temperature;

/**Pressure Variables*/
unsigned long B4;
unsigned long B7;
long  X3;
long  B3;
long  B6;
long Uncompensated_Pressure;
float Real_Presssure;

/**Altitude Variable*/
float SeaLevel_Altitude;
float Pressure;
float SeaLevelPressure;



/**
 * @fn     HAL_StatusTypeDef BMP180_Init(I2C_HandleTypeDef *hi2c)
 * @brief  This function provide to check the I2C bus is suitable to communicate. If not Warning Led is HIGH
 * @arg "3" 64 Byte Operations
 * @retval HAL Status
 */
HAL_StatusTypeDef BMP180_Init(I2C_HandleTypeDef *hi2c){

	if(HAL_I2C_IsDeviceReady(&hi2c1, BMP180_DEVICE_I2C_WRITE_ADDRESS, 5, 10000) != HAL_OK){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
		return HAL_ERROR;
		while(1);
	}
	BMP180_Get_And_Check_CalibrationDatas();
	return HAL_OK;
}


/**
 * @fn     HAL_StatusTypeDef BMP180_Get_And_Check_CalibrationDatas(void)
 * @brief  This function provide to check the Calibration Datas after read from sensor's EEPROM. If any value is 0x00 or 0xFF Warning Led is HIGH
 * @retval HAL Status
 */
HAL_StatusTypeDef BMP180_Get_And_Check_CalibrationDatas(void){

uint8_t Array_CalibrationData[CalibrationCoefficient_Lenght] = {0};
uint8_t cnt = 0;

HAL_I2C_Mem_Read(&hi2c1, BMP180_DEVICE_I2C_READ_ADDRESS, Calibration_Reg_Start_Address, 1, Array_CalibrationData, CalibrationCoefficient_Lenght, 10000);

AC1 =  (int16_t)((Array_CalibrationData[cnt]<<8) | Array_CalibrationData[cnt+1]); cnt+=2;
AC2 =  (int16_t)((Array_CalibrationData[cnt]<<8) | Array_CalibrationData[cnt+1]); cnt+=2;
AC3 =  (int16_t)((Array_CalibrationData[cnt]<<8) | Array_CalibrationData[cnt+1]); cnt+=2;
AC4 = (uint16_t)((Array_CalibrationData[cnt]<<8) | Array_CalibrationData[cnt+1]); cnt+=2;
AC5 = (uint16_t)((Array_CalibrationData[cnt]<<8) | Array_CalibrationData[cnt+1]); cnt+=2;
AC6 = (uint16_t)((Array_CalibrationData[cnt]<<8) | Array_CalibrationData[cnt+1]); cnt+=2;
B1  =  (int16_t)((Array_CalibrationData[cnt]<<8) | Array_CalibrationData[cnt+1]); cnt+=2;
B2  =  (int16_t)((Array_CalibrationData[cnt]<<8) | Array_CalibrationData[cnt+1]); cnt+=2;
MB  =  (int16_t)((Array_CalibrationData[cnt]<<8) | Array_CalibrationData[cnt+1]); cnt+=2;
MC  =  (int16_t)((Array_CalibrationData[cnt]<<8) | Array_CalibrationData[cnt+1]); cnt+=2;
MD  =  (int16_t)((Array_CalibrationData[cnt]<<8) | Array_CalibrationData[cnt+1]); cnt+=2;

if(AC1 == 0x00 || AC1 == 0xFF){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	while(1);
}
else if(AC2 == 0x00 || AC2 == 0xFF){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	while(1);
}
else if(AC3 == 0x00 || AC3 == 0xFF){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	while(1);
}
else if(AC4 == 0x00 || AC4 == 0xFF){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	while(1);
}
else if(AC5 == 0x00 || AC5 == 0xFF){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	while(1);
}
else if(AC6 == 0x00 || AC6 == 0xFF){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	while(1);
}
else if(B1 == 0x00 || B1 == 0xFF){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	while(1);
}
else if(B2 == 0x00 || B2 == 0xFF){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	while(1);
}
else if(MB == 0x00 || MB == 0xFF){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	while(1);
}
else if(MC == 0x00 || MC == 0xFF){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	while(1);
}
else if(MD == 0x00 || MD == 0xFF){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	while(1);
}
return HAL_OK;

}


/**
 * @fn     long BMP180_Get_TempatureDatas()
 * @brief  This function provide to get Real Temperature Values by using Uncompensated Temperature Values
 * @retval Real_Temperature
 */
float BMP180_Get_TempatureDatas(void){


	uint8_t UTemperature_MSB_LSB[2] = {0};
	uint8_t UTemperature_ConstantVal[1] = {0x2E};


	HAL_I2C_Mem_Write(&hi2c1, BMP180_DEVICE_I2C_WRITE_ADDRESS, 0xF4, 1, UTemperature_ConstantVal, 1, 10000);

	HAL_Delay(5);

	HAL_I2C_Mem_Read(&hi2c1, BMP180_DEVICE_I2C_READ_ADDRESS, 0xF6, 1, UTemperature_MSB_LSB, 2, 10000);

	Uncompensated_Temperature = (uint32_t)(UTemperature_MSB_LSB[0]<<8 | UTemperature_MSB_LSB[1]);


	X1  = ((Uncompensated_Temperature - AC6) * AC5) / 32768;
	X2  = ((MC * 2048) / (X1 + MD));
	B5  = (X1 + X2);
	Real_Temperature = (float)((B5 + 8) / 16) / 10 ;
	return Real_Temperature;

}


/**
 * @fn     long BMP180_Get_PressureDatas()
 * @brief  This function provide to get Real Pressure Values by using Uncompensated Pressure Values
 * @retval Real_Pressure
 */
float BMP180_Get_PressureDatas(void){

	uint8_t UPressure_MSB_LSB_XLSB[3] = {0};
	uint8_t UPressure_ConstantVal[1] = {0xF4};

	HAL_I2C_Mem_Write(&hi2c1, BMP180_DEVICE_I2C_WRITE_ADDRESS, 0xF4, 1, UPressure_ConstantVal, 1, 10000);

	HAL_Delay(80);

	HAL_I2C_Mem_Read(&hi2c1, BMP180_DEVICE_I2C_READ_ADDRESS, 0xF6, 1, UPressure_MSB_LSB_XLSB, 3, 10000);

	Uncompensated_Pressure = (((UPressure_MSB_LSB_XLSB[0]<<16) | (UPressure_MSB_LSB_XLSB[1]<<8) | (UPressure_MSB_LSB_XLSB[2])) >> (8-OverSamplingSetting));


	B6  = (B5 - 4000);
	X1  = ((B2 * (B6 * B6 / pow(2,12))) / pow(2,11));
	X2  = (AC2 * B6 / pow(2,11));
	X3  = (X1 + X2);
	B3  = ((((AC1 * 4 + X3) << OverSamplingSetting) +2) / 4);
	X1  = (AC3 * B6 / pow(2,13));
	X2  = ((B1*(B6 * B6 / pow(2,12))) / pow(2,16));
	X3  = (((X1 + X2) + 2) / 4);
	B4  = (AC4 * (X3 + 32768)/pow(2,15));
	B7  = (((Uncompensated_Pressure - B3)) * (50000 >> OverSamplingSetting));

	if(B7 < 0x80000000){
		Real_Presssure = ((B7 * 2) / B4);
	}
	else{
		Real_Presssure = ((B7 / B4) * 2);
	}

	X1 = (Real_Presssure / pow(2,8)) * (Real_Presssure / pow(2,8));
	X1 = ((X1 * 3038) / pow(2,16));
	X2 = (((-7357) * Real_Presssure) / pow(2,16));
	Real_Presssure = (Real_Presssure + (X1 + X2 + 3791) / pow(2,4));
	return Real_Presssure;

}


/**
 * @fn     float BMP180_Get_SeaAltitudeDatas(void)
 * @brief  This function provide to calculate Real SeaLevelAltitude values by using  Real_Pressure Values
 * @retval Real SeaLevel Altitudes
 */
float BMP180_Get_AltitudeDatas(void){

	Pressure = BMP180_Get_PressureDatas();

	SeaLevel_Altitude = (SeaLevelTemp / GradientTemp) * (1 - pow((Pressure/ SeaLevelPress),((GasCoefficient * GradientTemp)/GravityAccel)));

	return SeaLevel_Altitude;
}


