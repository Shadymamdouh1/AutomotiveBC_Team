/*
 * Ext_INT.h
 *
 * Created: 7/27/2021 3:03:04 PM
 *  Author: Ahmed Nabil
 */ 


#ifndef EXT_INT_H_
#define EXT_INT_H_


#include "TM4C123GH6PM.h"
#include "Ext_INT_Cfg.h"
#include "Std_Types.h"
#include "Common_Macros.h"

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef void (*pfExtINT_CallBack_t)(void);

typedef struct
{
    uint8 portID;
    uint8 pinID;
    uint8 senseCtrl;
}Ext_INT_Config_t;

/* CONSTANTS */

#define LOW_LEVEL			0			//The low level of INT0 generates an interrupt request.
#define HIGH_LEVEL          1           //The High level of INT0 generates an interrupt request.
#define LOGIC_CHANGE		2			//Any logical change on INT0 generates an interrupt request.
#define FALLING_EDGE		3			//The falling edge of INT0 generates an interrupt request.
#define RISING_EDGE			4   		//The rising edge of INT0 generates an interrupt request.
/*************************************************************************************/


/*************************************************************************************/
/*- Function Declarations
-------------------------------*/

Std_ReturnType ExtINT_Disable(uint8_t ExtINT_ID);
Std_ReturnType ExtINT_Enable(uint8_t ExtINT_ID, uint8_t senseControl);
Std_ReturnType ExtINT_setCallback(uint8_t ExtINT_ID, pfExtINT_CallBack_t FunToBeCalledInISR);


#endif /* EXT_INT_H_ */
