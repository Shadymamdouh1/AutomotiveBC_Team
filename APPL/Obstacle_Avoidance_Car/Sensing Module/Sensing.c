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
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOK
* Description: Function used to get distance between the sensor and the facing obstacle
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType Sensing_getObstcleDistance(uint16_t *Sensing_distanceCM_pu16)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the module is already initialized */
	if(SensingModuleStatus_gu8 != SENSING_STATUS_INIT)
	{
		return E_NOT_OK;
	}else{/*Nothing to here*/}
		
	/* Check if the pointer variable is NULL */
	if (NULL_PTR == Sensing_distanceCM_pu16)
	{
		return E_NOT_OK;
	}else{/*Nothing to here*/}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	
	/* Read Ultrasonic Distance */
	Ultrasonic_GetDistance(1, Sensing_distanceCM_pu16);
	return E_OK;
}