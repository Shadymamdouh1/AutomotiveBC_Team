/*
 * App.h
 *
 * Created: 7/16/2021 1:22:44 PM
 *  Author: Ahmed Nabil
 */ 


#ifndef OBSTCL_AVD_RBT_H_
#define OBSTCL_AVD_RBT_H_


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "../Robot Steering Module/Rbt_Steering.h"
#include "../Sensing Module/Sensing.h"
#include "../../../ECUAL/Lcd Module/Lcd.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/
#define OBSTCLE_AVD_MOD_UNINITIALIZED			0U
#define OBSTCLE_AVD_MOD_INITIALIZED				1U
#define OB_AVD_DISTANCE_UNDER_50				2U
#define OB_AVD_DISTANCE_EQUAL_50				3U
#define OB_AVD_DISTANCE_OVER_50					4U
/*******************************************************************************
 *                          Module Data Types                                  *
 *******************************************************************************/
/*
* Data Type for App return status
*/
typedef uint8_t ModuleState_t;


/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function to initialize the Obstacle Avoidance Module */
Std_ReturnType ObstacleAvoidance_init(void);

/* Periodic Function of the Obstacle Avoidance Module */
Std_ReturnType ObstacleAvoidance_mainFunction(void);



#endif /* OBSTCL_AVD_RBT_H_ */