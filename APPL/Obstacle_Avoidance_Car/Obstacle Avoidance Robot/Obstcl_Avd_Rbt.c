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
uint16_t distance_u16 = 63;
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
	EnableGlobalInterrupts();
	/* Call the Robot Module initializer */
	if(ROBOT_STATUS_ERROR_OK != RbtSteering_init())
		return E_NOT_OK;
		
	/* Call the LCD Module initializer */
	Lcd_init();
	Lcd_sendString((uint8_t*)"    Distance");
	/* Call the Sensing Module initializer */
	Sensing_init();

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
	/* Check if the Module was already initialized */
	if (ObstclAvd_State == OBSTCLE_AVD_MOD_UNINITIALIZED)
	{
		return E_NOT_OK;
	}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/
// 	Lcd_init();
// 	Lcd_sendString((uint8_t*)"    Distance");
/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/

/* Get the distance to the nearest obstacle */
	Sensing_getObstcleDistance(&distance_u16);
/* Take Robot Action */
	/* If distance > 50 */
	if(distance_u16 > 50)
	{
		if (ObstclAvd_State != OB_AVD_DISTANCE_OVER_50)
		{
			ObstclAvd_State = OB_AVD_DISTANCE_OVER_50;
			RbtSteering_move(ROBOT_DIR_FRWRD, 20);
		}
	}
	/* If distance = 50 */
	else if(distance_u16 == 50)
	{
		if (ObstclAvd_State != OB_AVD_DISTANCE_EQUAL_50)
		{
			ObstclAvd_State = OB_AVD_DISTANCE_EQUAL_50;
			RbtSteering_move(ROBOT_DIR_RIGHT, 15);
		}
	}
	/* If distance < 50 */
	else
	{
		if (ObstclAvd_State != OB_AVD_DISTANCE_UNDER_50)
		{
			ObstclAvd_State = OB_AVD_DISTANCE_OVER_50;
			RbtSteering_move(ROBOT_DIR_BKWRD, 20);
		}
	}
/* Print Distance on LCD */
#if 1
	integerToString((uint16_t)distance_u16, distance_au8, DEC);
	Lcd_cursorPosition(2,8);
	Lcd_sendString(distance_au8);
#endif
/*******************************************************************************/
/*******************************************************************************/

	return E_OK;
}