/*****************************************************************************
* Module: Led Module
* File Name: Led.c
* Description: Source file for LED Module
* Author: Mohamed Magdy
* Date: 20-July-2021
******************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "Led.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
enuLed_Status_t Led_Status = LED_STATUS_ERROR_OK;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuLed_Status_t
* Description: initialize the leds module 
******************************************************************************************/
enuLed_Status_t Led_init(void)
{
	Dio_init(strDio_pins);
	
	return LED_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): led ID
* Parameters (out): Error Status
* Return value: enuLed_Status_t
* Description: turns on a given led
******************************************************************************************/
enuLed_Status_t LedOn(uint8_t u8_LedId)
{
	Dio_writePin(strLed_Config[u8_LedId].u8_LedDioId, STD_HIGH);
	return LED_STATUS_ERROR_OK;

}


/*****************************************************************************************
* Parameters (in): led ID
* Parameters (out): Error Status
* Return value: enuLed_Status_t
* Description:turns off a given led
******************************************************************************************/
enuLed_Status_t LedOff(uint8_t u8_LedId)
{
	Dio_writePin(strLed_Config[u8_LedId].u8_LedDioId, STD_LOW);
	return LED_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): led ID
* Parameters (out): Error Status
* Return value: enuLed_Status_t
* Description: toggles a given led
******************************************************************************************/
enuLed_Status_t LedToggle(uint8_t u8_LedId)
{
	Dio_togglePin(strLed_Config[u8_LedId].u8_LedDioId);
	
	return LED_STATUS_ERROR_OK;
}

