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

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*- FUNCTIONS IMPLEMENTATION -*-*-*-*-*-*/

#if 0
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: RobotApp_start
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: enuApp_Status_t - return the status of the function ERROR_OK or NOT_OK
* Description: Function to Start the Application.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
enuApp_Status_t RobotApp_start(void)
{
	/**************************************************************************************/
	/*								Function Implementation								  */
	/**************************************************************************************/
	/* Initialize the Car application */
	if(RobotApp_init() != APP_STATUS_ERROR_OK)
		return APP_STATUS_ERROR_NOK;
	EnableGlobalInterrupts();
	
	
	Robot_move(ROBOT_DIR_FRWRD, 20);
	/* Application Super Loop */
	while (1)
	{
		/* Update the car status */
		if(RobotApp_update() != APP_STATUS_ERROR_OK)
			return APP_STATUS_ERROR_NOK;
			
	}
}
#endif
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
	if (ObstclAvd_State == OBSTCLE_AVD_MOD_INITIALIZED)
	{
		return E_OK;
	}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/

	/* Call the Robot Module initializer */
	if(ROBOT_STATUS_ERROR_OK != RbtSteering_init())
		return E_NOT_OK;
		
	/* Call the LCD Module initializer */
	if(LCD_STATUS_ERROR_OK != Lcd_init())
		return E_NOT_OK;
	
	EnableGlobalInterrupts();
	
//	RbtSteering_move(ROBOT_DIR_FRWRD, 20);
	/* Call the Ultrasonic Module initializer */
//  	if(SRVC_STATUS_ERROR_OK != Ultrasonic_init())
//  		return APP_STATUS_ERROR_NOK;

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
	if (ObstclAvd_State != OBSTCLE_AVD_MOD_INITIALIZED)
	{
		return E_NOT_OK;
	}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	
/* Read Ultrasonic Distance */
	

/* Take Robot Action */
	/* If distance > 50 */
	
	/* If distance = 50 */
	
	/* If distance < 50 */
	
/* Print Distance on LCD */
	
/*******************************************************************************/
/*******************************************************************************/

	return E_OK;
}