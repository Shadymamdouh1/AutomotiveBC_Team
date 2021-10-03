/*
 * Ext_INT.c
 *
 * Created: 7/27/2021 3:02:47 PM
 *  Author: Ahmed Nabil
 */ 
#include "Ext_INT.h"
#include "IntCtrl.h"
#include "Port.h"
/*- GLOBAL STATIC VARIABLES
-------------------------------*/

//static pfExtINT_CallBack_t ExtIntCallback[EXT_INTERRUPT_PINS]={NULL_PTR};

/*- Function Definitions
-------------------------------*/
Std_ReturnType ExtINT_Enable(uint8_t ExtINT_ID, uint8_t senseControl)
{
    uint8 portNum = ExtINT_ID/10;
    uint8 pinNum = ExtINT_ID%10;

    switch(senseControl)
    {
        case LOW_LEVEL:
        {
            PORT(portNum)->IS  |=  (1<<pinNum);
            PORT(portNum)->IEV &= ~(1<<pinNum);
            break;
        }
        case HIGH_LEVEL:
        {
            PORT(portNum)->IS  |= (1<<pinNum);
            PORT(portNum)->IEV |= (1<<pinNum);
            break;
        }
        case FALLING_EDGE:
        {
            PORT(portNum)->IS  &= ~(1<<pinNum);
            PORT(portNum)->IEV &= ~(1<<pinNum);
            break;
        }
        case RISING_EDGE:
        {
            PORT(portNum)->IS  &= ~(1<<pinNum);
            PORT(portNum)->IEV |= (1<<pinNum);
            break;
        }
        case LOGIC_CHANGE:
        {
            PORT(portNum)->IS  &= ~(1<<pinNum);
            PORT(portNum)->IBE |=  (1<<pinNum);
            break;
        }
        default:
        {
            break;
        }
    }
    PORT(portNum)->IM |= 1<<0;
    return E_OK;
}

Std_ReturnType ExtINT_Disable(uint8_t ExtINT_ID)
{
    uint8 portNum = ExtINT_ID/10;
    uint8 pinNum = ExtINT_ID%10;
    PORT(portNum)->IM &= ~(1<<pinNum);
    return E_OK;
}

/*****************************************************************************************
* Parameters (in): pointer to function to be called from ISR
* Parameters (out): None
* Return value: None
* Description: sets the function to be called by external interrupt 0 ISR
******************************************************************************************/
Std_ReturnType ExtINT_setCallback(uint8_t ExtINT_ID, pfExtINT_CallBack_t FunToBeCalledInISR)
{
    uint8 portNum = ExtINT_ID/10;

    switch(portNum)
    {
        case PORT_A_ID:
        {
            Interrupt_install(GPIOA_vecID, FunToBeCalledInISR);
            break;
        }
        case PORT_B_ID:
        {
            Interrupt_install(GPIOB_vecID, FunToBeCalledInISR);
            break;
        }
        case PORT_C_ID:
        {
            Interrupt_install(GPIOC_vecID, FunToBeCalledInISR);
            break;
        }
        case PORT_D_ID:
        {
            Interrupt_install(GPIOD_vecID, FunToBeCalledInISR);
            break;
        }
        case PORT_E_ID:
        {
            Interrupt_install(GPIOE_vecID, FunToBeCalledInISR);
            break;
        }
        case PORT_F_ID:
        {
            Interrupt_install(GPIOF_vecID, FunToBeCalledInISR);
            break;
        }
        default:
        {
            return E_NOT_OK;
        }
    }
    return E_OK;
}
