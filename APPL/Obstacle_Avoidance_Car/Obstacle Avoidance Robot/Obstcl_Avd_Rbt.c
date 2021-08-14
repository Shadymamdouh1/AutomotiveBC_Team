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
	uint16_t tempDistance_u16 = 0;
	
/* Get the distance to the nearest obstacle */
	if(Sensing_getDistance(SENSING_FRONT_OBSTACLE_DISTANCE, &tempDistance_u16) == E_OK)
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
			RbtSteering_move(ROBOT_DIR_FRWRD, OB_RBT_FRWRD_SPEED);
		}
	}
	/* If distance within threshold range */
	if((distance_u16 < OB_AVD_HIGH_THRESHOLD) && (distance_u16 > OB_AVD_LOW_THRESHOLD))
	{
		if (ObstclAvd_State != OB_AVD_DISTANCE_EQUAL_THRSHOLD)
		{
			ObstclAvd_State = OB_AVD_DISTANCE_EQUAL_THRSHOLD;
			RbtSteering_move(ROBOT_DIR_RIGHT, OB_RBT_RIGHT_SPEED);
			Delay_ms(320);
		}
	}
	/* If distance < OB_AVD_LOW_THRESHOLD */
	if(distance_u16 < OB_AVD_LOW_THRESHOLD)
	{
		if (ObstclAvd_State != OB_AVD_DISTANCE_UNDER_THRSHOLD)
		{
			ObstclAvd_State = OB_AVD_DISTANCE_UNDER_THRSHOLD;
			RbtSteering_move(ROBOT_DIR_BKWRD, OB_RBT_BKWRD_SPEED);
		}
	}
	
/* Print Distance on LCD */
	integerToString((uint16_t)distance_u16, distance_au8, DEC);
	if(distance_u16 < 10)
	{
		distance_au8[1]=' ';
		distance_au8[2]=' ';
		distance_au8[3]='\0';
	}else if(distance_u16 < 100)
	{
		distance_au8[2]=' ';
		distance_au8[3]='\0';
	}
	Lcd_cursorPosition(2,8);
	Lcd_sendString(distance_au8);
/*******************************************************************************/
/*******************************************************************************/

	return E_OK;
}