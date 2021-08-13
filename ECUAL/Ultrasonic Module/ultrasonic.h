/*****************************************************************************
* Module: Ultrasonic Module
* File Name: Ultrasonic.h
* Description: Header file for Ultrasonic sensor Module
* Author: Shady Mamdouh
* Date: 8/12/2021
******************************************************************************/


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include "..\..\Microcontroller\Platform_Types.h"
#include "Ultrasonic_Cfg.h"
typedef enum US_Status_t
{
	US_ERROR_OK,
	US_ERROR_NOK
}US_Status_t;

typedef struct US_Config_t
{
	uint8_t US_ChannedID;
	uint32_t CPU_FREQ ;
	uint32_t US_CHPreScaler;
	}US_Config_t;

/************************************************************
				        APIs
************************************************************/
US_Status_t Ultrsonic_Init(void);
US_Status_t Ultrsonic_GetDistance(uint8_t US_Channel ,  uint16_t *u16_Distance);
/*- EXTERN VARIABLE DECLARATIONS */
extern US_Config_t US_Channels[US_USED_CHANNELS] ;

#endif /* ULTRASONIC_H_ */
