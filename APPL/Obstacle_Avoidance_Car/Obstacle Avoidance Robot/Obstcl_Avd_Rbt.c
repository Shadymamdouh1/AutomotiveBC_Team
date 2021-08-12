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
uint8_t distance_u8 = 199;
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
// 	if(LCD_STATUS_ERROR_OK != Lcd_init())
// 		return E_NOT_OK;
	
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
	uint8_t btn_state=PIN_LOW;
	static uint8_t btn_flag=PIN_LOW;
/* Read Ultrasonic Distance */
	/* Read button as for testing */
	Dio_readPin(DIO_BTN1_CHANNEL_ID, &btn_state);
	if((btn_state == PIN_HIGH) && (btn_flag == PIN_LOW))
	{
		btn_flag = PIN_HIGH;
		distance_u8-=50;
	}else if(btn_state == PIN_LOW)
	{
		btn_flag = PIN_LOW;
	}
/* Take Robot Action */
	/* If distance > 50 */
	if(distance_u8 > 50)
	{
		if (ObstclAvd_State != OB_AVD_DISTANCE_UNDER_50)
		{
			ObstclAvd_State = OB_AVD_DISTANCE_UNDER_50;
			RbtSteering_move(ROBOT_DIR_FRWRD, 60);
		}
	}
	/* If distance = 50 */
	else if(distance_u8 == 50)
	{
		if (ObstclAvd_State != OB_AVD_DISTANCE_EQUAL_50)
		{
			ObstclAvd_State = OB_AVD_DISTANCE_EQUAL_50;
			RbtSteering_move(ROBOT_DIR_RIGHT, 60);
		}
	}
	/* If distance < 50 */
	else
	{
		if (ObstclAvd_State != OB_AVD_DISTANCE_OVER_50)
		{
			ObstclAvd_State = OB_AVD_DISTANCE_OVER_50;
			RbtSteering_move(ROBOT_DIR_BKWRD, 60);
		}
	}
/* Print Distance on LCD */
#if 0
	integerToString((uint16_t)distance_u8, distance_au8, DEC);
	Lcd_cursorPosition(1,1);
	Lcd_sendString(distance_au8);
#endif
/*******************************************************************************/
/*******************************************************************************/

	return E_OK;
}