/*
 * App.c
 *
 * Created: 7/16/2021 1:22:50 PM
 *  Author: Ahmed Nabil
 */ 

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "App.h"
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- GLOBAL STATIC VARIABLES *-*-*-*-*-*/
static enuRobotAction_t enuCurrentAction = ROBOT_ACTION_STOP;
static enuApp_Status_t enuCurrentAppStatus = APP_STATUS_UNINITIALIZED;
uint8_t gau8_num[4] = {0};
uint16_t gu16_num = 0;
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*- FUNCTIONS IMPLEMENTATION -*-*-*-*-*-*/

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
	
	
	Robot_move(ROBOT_DIR_FRWRD, 5);
	/* Application Super Loop */
	while (1)
	{
		/* Update the car status */
		if(RobotApp_update() != APP_STATUS_ERROR_OK)
			return APP_STATUS_ERROR_NOK;
			
	}
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: RobotApp_init
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: enuApp_Status_t - return the status of the function ERROR_OK or NOT_OK
* Description: Function to Initialize the Application.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
enuApp_Status_t RobotApp_init(void)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the Application was already initialized */
	if (enuCurrentAppStatus == APP_STATUS_INITIALIZED)
	{
		return APP_STATUS_INITIALIZED;
	}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/

	/* Call the Robot Module initializer */
	if(ROBOT_STATUS_ERROR_OK != Robot_init())
		return APP_STATUS_ERROR_NOK;
		
	/* Call the LCD Module initializer */
	if(LCD_STATUS_ERROR_OK != Lcd_init())
		return APP_STATUS_ERROR_NOK;
		
	/* Call the Ultrasonic Module initializer */
// 	if(SRVC_STATUS_ERROR_OK != Ultrasonic_init())
// 		return APP_STATUS_ERROR_NOK;

	/* Update enuCurrentAppStatus to initialized */
	enuCurrentAppStatus = APP_STATUS_INITIALIZED;
	return APP_STATUS_ERROR_OK;
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: RobotApp_update
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: enuApp_Status_t - return the status of the function ERROR_OK or NOT_OK
* Description: Function to Update the state of the application.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
enuApp_Status_t RobotApp_update(void)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the Application was already initialized */
	if (enuCurrentAppStatus != APP_STATUS_INITIALIZED)
	{
		return APP_STATUS_UNINITIALIZED;
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

	return APP_STATUS_ERROR_OK;
}