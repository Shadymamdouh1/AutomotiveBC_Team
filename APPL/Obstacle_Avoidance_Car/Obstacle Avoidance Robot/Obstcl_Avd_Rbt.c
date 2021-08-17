/*
 * App.c
 *
 * Created: 7/16/2021 1:22:50 PM
 *  Author: Ahmed Nabil
 */ 

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "Obstcl_Avd_Rbt.h"
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- GLOBAL STATIC VARIABLES *-*-*-*-*-*/

ModuleState_t ObstclAvd_State = OBSTCLE_AVD_MOD_UNINITIALIZED;
uint16_t distance_u16 = 0;
uint8_t distance_au8[4] = {0};

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*- FUNCTIONS IMPLEMENTATION -*-*-*-*-*-*/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: ObstacleAvoidance_init
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOT_OK
* Description: Function to Initialize the Obstacle Avoidance Module.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType ObstacleAvoidance_init(void)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the Module was already initialized */
	if (ObstclAvd_State != OBSTCLE_AVD_MOD_UNINITIALIZED)
	{
		return E_OK;
	}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/* Call the Sensing Module initializer */
	if(E_OK != Sensing_init())
	{
		return E_NOT_OK;		
	}

	/* Update ObstclAvd_State to initialized */
	ObstclAvd_State = OBSTCLE_AVD_MOD_INITIALIZED;
	return E_OK;
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: ObstacleAvoidance_mainFunction
* Sync/Async: ASynchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOT_OK
* Description: Periodic function/task of the module.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType ObstacleAvoidance_mainFunction(void)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the Module is not initialized yet */
	if (ObstclAvd_State == OBSTCLE_AVD_MOD_UNINITIALIZED)
	{
		return E_NOT_OK;
	}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/
/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/

	uint16_t tempDistance_u16 = 0;
	
	
	/* Distance Getter from Sensing Module */
/* Get the distance to the nearest obstacle */
	if(Sensing_getReading(SENSING_FRONT_OBSTACLE_DISTANCE, &tempDistance_u16) == E_OK)
	{
		distance_u16 = tempDistance_u16;
	}
	
/* Take Robot Action */
	/* If distance > OB_AVD_HIGH_THRESHOLD */
	if(distance_u16 > OB_AVD_HIGH_THRESHOLD)
	{
		if (ObstclAvd_State != OB_AVD_DISTANCE_OVER_THRSHOLD)
		{
			ObstclAvd_State = OB_AVD_DISTANCE_OVER_THRSHOLD;
			
			/* Action Setter for Robot Steering Module */
			RbtSteering_Dir_Spd_Setter(ROBOT_DIR_FRWRD, OB_RBT_FRWRD_SPEED);
		}
	}
	/* If distance within threshold range */
	else if((distance_u16 < OB_AVD_HIGH_THRESHOLD) && (distance_u16 > OB_AVD_LOW_THRESHOLD))
	{
		if (ObstclAvd_State != OB_AVD_DISTANCE_EQUAL_THRSHOLD)
		{
			ObstclAvd_State = OB_AVD_DISTANCE_EQUAL_THRSHOLD;
			
			/* Action Setter for Robot Steering Module */
			RbtSteering_Dir_Spd_Setter(ROBOT_DIR_RIGHT, OB_RBT_RIGHT_SPEED);
		}
	}
	/* If distance < OB_AVD_LOW_THRESHOLD */
	else if(distance_u16 < OB_AVD_LOW_THRESHOLD)
	{
		if (ObstclAvd_State != OB_AVD_DISTANCE_UNDER_THRSHOLD)
		{
			ObstclAvd_State = OB_AVD_DISTANCE_UNDER_THRSHOLD;
			
			/* Action Setter for Robot Steering Module */
			RbtSteering_Dir_Spd_Setter(ROBOT_DIR_BKWRD, OB_RBT_BKWRD_SPEED);
		}
	}
	else
	{
		/* All cases are covered */
	}
	
	set_DisplayInteger(DISPLAY_LCD_16x2_ID, distance_u16);
/*******************************************************************************/
/*******************************************************************************/

	return E_OK;
}