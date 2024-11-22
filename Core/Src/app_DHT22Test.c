/*
 * app_DHT22Test.c
 *
 *  Created on: Nov 15, 2024
 *      Author: tylermiller
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "stm32l4xx_hal.h"
#include "app.h"
#include "lcd.h"
#include "dht.h"
#include "delayMicroseconds.h"

void App_Init(void) {

	initLCD();

}

void App_MainLoop(void) {

	uint8_t Presence = 0;
	uint8_t Rh_byte1 = 0;
	uint8_t Rh_byte2 = 0;
	uint8_t Temp_byte1 = 0;
	uint8_t Temp_byte2 = 0;
	uint16_t SUM = 0;
	uint16_t TEMP = 0;
	uint16_t RH = 0;
	float Temperature = 0;
	float Humidity = 0;

	DHT22_Start();
	Presence = DHT22_Check_Response();
	Rh_byte1 = DHT22_Read ();
	Rh_byte2 = DHT22_Read ();
	Temp_byte1 = DHT22_Read ();
	Temp_byte2 = DHT22_Read ();
	SUM = DHT22_Read();

	if (Presence == 1) {

	}

	else {

		clearLCD();
		char *message = "DHT Error";
		writeLCD(message);
		return;

	}

	if (SUM != (Rh_byte1+Rh_byte2+Temp_byte1+Temp_byte2)) {

		clearLCD();
		char *message = "DHT Checksum Error";
		writeLCD(message);
		return;

	}

	TEMP = ((Temp_byte1<<8)|Temp_byte2);
	RH = ((Rh_byte1<<8)|Rh_byte2);

	Temperature = (float) (TEMP/10.0);
	Humidity = (float) (RH/10.0);

	Temperature = (float) (Temperature*(9.0/5.0)+32.0);

	char TempStr[16];
	char HumStr[16];

	sprintf(TempStr,"Temp: %.2f",Temperature);
	sprintf(HumStr,"Hum: %.2f",Humidity);
    clearLCD();
	writeLCD(TempStr);
	setCursor(0,1);
	writeLCD(HumStr);

	HAL_Delay(2000);

}
