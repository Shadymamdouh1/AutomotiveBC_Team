/*
 * Robot.h
 *
 * Created: 9/8/2021 11:16:10 AM
 *  Author: Ahmed Nabil
 */ 


#ifndef ROBOT_H_
#define ROBOT_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "../../../ECUAL/Motor Module/Motor.h"
#include "Robot_Cfg.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/

/*
 * MACROs to determine the directions used by the Robot_move API
 */
#define ROBOT_DIR_FRWRD				0U
#define ROBOT_DIR_BKWRD				1U
#define ROBOT_DIR_LEFT				2U
#define ROBOT_DIR_RIGHT				3U
#define ROBOT_DIR_INVALID			4U


/*******************************************************************************
 *                          Module Data Types                                  *
 *******************************************************************************/

/*
 * Data Type for Robot state
 */
typedef uint8_t u8_RobotState_t;

/*
 * Data Type for Robot direction
 */
typedef uint8_t u8_RobotDir_t;

/*
 * Data Type for Robot Speed
 */
typedef uint8_t u8_RobotSpeed_t;

/*
 * Data Type for Robot return status
 */
typedef enum
{
	ROBOT_STATUS_ERROR_NOK,
	ROBOT_STATUS_ERROR_OK,
	ROBOT_STATUS_ERROR_ID_INVALID,
	ROBOT_STATUS_ERROR_SPD_INVALID,
	ROBOT_STATUS_ERROR_DIR_INVALID,
	ROBOT_STATUS_ERROR_RUNNING,
	ROBOT_STATUS_ERROR_STOPPED,
	ROBOT_STATUS_INIT,
	ROBOT_STATUS_UNINIT
}enuRobot_Status_t;

/*
 * Data Type for Robot configurations
 */
typedef struct  
{
	u8_MotorChannel_t u8_leftMotorID; //Variable holds the left motor index from the MOTOR Module
	u8_MotorChannel_t u8_rightMotorID; //Variable holds the right motor index from the MOTOR Module
}strRobot_Config_t;
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function to initialize the Robot module */
enuRobot_Status_t Robot_init(void);

/* Function to move the Robot a given direction with given speed in % */
enuRobot_Status_t Robot_move(u8_RobotDir_t u8_direction, u8_RobotSpeed_t u8_speed);

/* Function to stop Robot */
enuRobot_Status_t Robot_stop(void);

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
extern const strRobot_Config_t str_RobotsConfig;

#endif /* ROBOT_H_ */