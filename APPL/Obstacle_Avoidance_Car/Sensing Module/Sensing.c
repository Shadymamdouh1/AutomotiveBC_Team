/*
 * Sensing.c
 *
 * Created: 13/8/2021 11:15:40 AM
 *  Author: Ahmed Nabil
 */ 

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "Sensing.h"


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/

/*
 * MACROs to determine the state of the Module
 */
#define SENSING_STATUS_UNINIT		0U
#define SENSING_STATUS_INIT			1U

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- GLOBAL STATIC VARIABLES *-*-*-*-*-*/

/* Holds the status of the Sensing Module */
Sensing_State_t SensingModuleStatus_gu8 = SENSING_STATUS_UNINIT;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*- FUNCTIONS IMPLEMENTATION -*-*-*-*-*-*/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Sensing_init
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOK
* Description: Function to Initialize the Sensing module.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Function to initialize the Sensing module */
Std_ReturnType Sensing_init(void)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the module is already initialized */
	if(SensingModuleStatus_gu8 == SENSING_STATUS_INIT)
	{
		return E_OK;
	}else{/*Nothing to here*/}
		
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/
/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/* Initialize the Ultrasonic Module */
	Ultrasonic_Init();
	
	/* Change the state of the module to initialized */
	SensingModuleStatus_gu8 = SENSING_STATUS_INIT;
	return E_OK;
}


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Sensing_getObstcleDistance
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): DistanceID_u8 - ID for the distance to be read.
* Parameters (inout): None
* Parameters (out): Sensing_distanceCM_pu16 - pointer to a variable to hold the returned distance
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOK
* Description: Function used to get distance as given in the ID
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType Sensing_getDistance(uint8_t DistanceID_u8, uint16_t *Sensing_distanceCM_pu16)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the module is already initialized */
	if(SensingModuleStatus_gu8 != SENSING_STATUS_INIT)
	{
		return E_NOT_OK;
	}else{/*Nothing to do here*/}
		
	/* Check if the pointer variable is NULL */
	if (NULL_PTR == Sensing_distanceCM_pu16)
	{
		return E_NOT_OK;
	}else{/*Nothing to do here*/}
		
	if(DistanceID_u8 >= SENSING_DISTANCE_INVALID)
	{
		return E_NOT_OK;
	}else{/* Nothing to do here*/}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	uint16_t tempDistance_u16 = 0;
	
	/* Read Ultrasonic Distance */
	if(Ultrasonic_GetDistance(US_CHANNEL_FRONT, &tempDistance_u16) == E_OK)
	{
		if(tempDistance_u16 > ULTRASONIC_MAX_DISTANCE_RANGE)
		{
			*Sensing_distanceCM_pu16 = ULTRASONIC_MAX_DISTANCE_RANGE;
		}else
		{
			*Sensing_distanceCM_pu16 = tempDistance_u16;
		}
		return E_OK;
	}else
	{
		return E_NOT_OK;
	}
	return E_NOT_OK;
}