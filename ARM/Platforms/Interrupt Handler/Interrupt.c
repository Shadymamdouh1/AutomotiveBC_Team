/*****************************************************************************
* Module: Interrupt Handler Module
* File Name: Interrupt.c
* Description: Source file for Interrupt Handler
* Author: Ahnmed Nabil
* Date: 19-August-2021
******************************************************************************/
#include "Interrupt.h"
#include "Interrupt_Interface.h"
#include "Std_Types.h"
#include "Common_Macros.h"
#include "TM4C123GH6PM.h"

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
pf_Vector old_Vectors[VECTORS_NUM] = 
{
    IntDefaultHandler,          /** External Interrupt Request 0 **/
    IntDefaultHandler,          /** External Interrupt Request 1 **/
    IntDefaultHandler,          /** External Interrupt Request 2 **/
    IntDefaultHandler,          /** Timer/Counter2 Compare Match **/
    IntDefaultHandler,          /** Timer/Counter2 Overflow **/
    IntDefaultHandler,          /** Timer/Counter1 Capture Event **/
    IntDefaultHandler,          /** Timer/Counter1 Compare Match A **/
    IntDefaultHandler,          /** Timer/Counter1 Compare Match B **/
    IntDefaultHandler,          /** Timer/Counter1 Overflow **/
    IntDefaultHandler,          /** Timer/Counter0 Compare Match **/
    IntDefaultHandler,          /** Timer/Counter0 Overflow **/
    IntDefaultHandler,          /** SPI Serial Transfer Complete **/
    IntDefaultHandler,          /** USART, Rx Complete **/
    IntDefaultHandler,          /** USART Data Register Empty **/
    IntDefaultHandler,          /** USART, Tx Complete **/
    IntDefaultHandler,          /** ADC Conversion Complete **/
    IntDefaultHandler,          /** EEPROM Ready **/
    IntDefaultHandler,          /** Analog Comparator **/
    IntDefaultHandler,          /** Two-wire Serial Interface **/
    IntDefaultHandler           /** Store Program Memory Ready **/
};

void EnableGlobalInterrupts(void)
{
	SET_BIT(SREG_R, GLOBAL_INT);
}

void DisableGlobalInterrupts(void)
{
	CLEAR_BIT(SREG_R, GLOBAL_INT);
}

/*- Function Definitions
-------------------------------*/
void IntDefaultHandler(void)
{
    while (1)
    {
    }
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out):None
* Return value: None
* Description: interrupt service routine for external interrupt 2 ISR
******************************************************************************************/

