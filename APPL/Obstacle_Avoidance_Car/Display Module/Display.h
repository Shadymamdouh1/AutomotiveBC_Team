/*
 * Display.h
 *
 * Created: 13/8/2021 11:16:10 AM
 *  Author: Ahmed Nabil
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "../../../ECUAL/Lcd Module/Lcd.h"
#include "Display_LCfg.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/
#define DISPLAY_LCD_16x2_ID					0U
#define DISPLAY_ID_INVALID					1U

/*******************************************************************************
 *                          Module Data Types                                  *
 *******************************************************************************/

/*
 * Data Type for Display module state
 */
typedef uint8_t Display_State_t;

/*
 * Data Type for Display Module configurations
 */
typedef struct  
{
	
}Display_Config_t;
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function to initialize the module */
Std_ReturnType Display_init(void);

/* Function used to display an input from the application on a Display Screen with the given ID */
Std_ReturnType Display_printString(uint8_t DisplayID_u8, uint8_t *StringToPrint_pu8);

/* Function used to display an input from the application on a Display Screen with the given ID */
Std_ReturnType Display_printInteger(uint8_t DisplayID_u8, uint16_t u16_number);
/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
extern const Display_Config_t Display_Configuratons;

#endif /* DISPLAY_H_ */