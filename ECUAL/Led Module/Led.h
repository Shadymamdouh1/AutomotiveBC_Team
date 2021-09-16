/*****************************************************************************
* Module: Led Module
* File Name: Led.h
* Description: Header file for Led Module
* Author: Mohamed Magdy
* Date: 20-July-2021
******************************************************************************/ 

#ifndef LED_H_
#define LED_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "Led_Cfg.h"
#include "Dio.h"
#include "Std_Types.h"
#include "Common_Macros.h"

/*******************************************************************************
 *                          Module Data Types                                  *
 *******************************************************************************/
/*
 * Data Type for Button return status
 */
typedef enum
{
	LED_STATUS_ERROR_NOK,
	LED_STATUS_ERROR_OK,
	LED_STATUS_ERROR_INVALID
}enuLed_Status_t;

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct
{
	uint8_t u8_LedDioId;
}strLed_Config_t;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
enuLed_Status_t Led_init(void);

enuLed_Status_t LedOn(uint8_t u8_LedId);

enuLed_Status_t LedOff(uint8_t u8_LedId);

enuLed_Status_t LedToggle(uint8_t u8_LedId);

/* configuration variable */
extern strLed_Config_t strLed_Config[USED_LEDS];
#endif /* LED_H_ */