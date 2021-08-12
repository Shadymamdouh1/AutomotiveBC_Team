/*
 * App.h
 *
 * Created: 7/16/2021 1:22:44 PM
 *  Author: Ahmed Nabil
 */ 


#ifndef APP_H_
#define APP_H_


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "../Robot Module/Robot.h"
#include "../../../ECUAL/Lcd Module/Lcd.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/

/*******************************************************************************
 *                          Module Data Types                                  *
 *******************************************************************************/
/*
 * Data Type for App return status
 */
typedef enum
{
	APP_STATUS_ERROR_NOK,
	APP_STATUS_ERROR_OK,
	APP_STATUS_ERROR_ID_INVALID,
	APP_STATUS_ERROR_NULL,
	APP_STATUS_INITIALIZED,
	APP_STATUS_UNINITIALIZED
}enuApp_Status_t;

/*
 * Data Type for Car Action state
 */
typedef enum
{
	ROBOT_ACTION_STOP,
	ROBOT_ACTION_FRWRD,
	ROBOT_ACTION_BKWRD,
	ROBOT_ACTION_RIGHT
}enuRobotAction_t;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function to Start the application */
enuApp_Status_t RobotApp_start(void);

/* Function to initialize the Application */
enuApp_Status_t RobotApp_init(void);

/* Function to update the application */
enuApp_Status_t RobotApp_update(void);



#endif /* APP_H_ */