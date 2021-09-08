/*****************************************************************************
* Module: Keypad Module
* File Name: Keypad.h
* Description: Header file for Keypad Module
* Author: Mohamed Magdy
* Date: 24-July-2021
******************************************************************************/


#ifndef KEYPAD_H_
#define KEYPAD_H_


/* INCLUDES */

#include "Std_Types.h"
#include "Common_Macros.h"
#include "Dio.h"
#include "Keypad_Cfg.h"
#include "Delay.h"

/* CONSTANTS */
#define NO_KEY_PRESSED			(0xFFU)
#define KEY_PRESSED				(10U)

#define KEYPAD_BUTTONS_NUM		(ROWS_NUM * COLS_NUM)

/*- STRUCTS --------------------------------------------------*/
typedef struct
{
	uint8_t au8_keysPressed[ROWS_NUM][COLS_NUM];
	uint8_t u8_numberOfPressedKeys;
}strKeypadOutput_t;
/*************************/
/*- FUNCTION DECLARATIONS ----------------------------------*/


Std_ReturnType Keypad_init(void);
Std_ReturnType KeypadScan(void);

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern strKeypadOutput_t keyPadOutput;

#endif /* KEYPAD_H_ */