/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  SysTick.c
 *        \brief  SysTick Timer Driver
 *
 *      \details  The Driver Configure SysTick Timer peripheral of Cortex M4 uP
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "SysTick.h"
#include "Common_Macros.h"

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
STATIC SysTick_pfCallBack_t SysTickCallBack;
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
SysTick_InitStatus_t SysTick_InitStatus = SYSTICK_NOT_INITIALIZED;
SysTick_Status_t SysTick_Status = SYSTICK_IDLE;

SysTick_Mode_t Continous_Or_OneShot_Flag;

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/******************************************************************************
* \Syntax          : Std_ReturnType SysTick_Init(void)                                      
* \Description     : Initializes SysTick Module using Cfg Header File.                                                                                                 
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : E_OK or E_NOT_OK
*******************************************************************************/
Std_ReturnType SysTick_Init(void)
{
    if(SysTick_InitStatus == SYSTICK_INITIALIZED)
    {
        return E_OK;
    }
    switch (SYSTICK_CLK_SRC)
    {
        case(SYSTICK_PIOSC_DIV4):
        {
            CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Pos);
            break;
        }
        case(SYSTIC_SYS_CLK):
        {
            SET_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Pos);
            break;
        }        
        default:
            break;
    }

    SysTick_InitStatus = SYSTICK_INITIALIZED;
    return E_OK;
}

/******************************************************************************
* \Syntax          : Std_ReturnType SysTick_SyncStart(void)                                      
* \Description     : Stars Timer                                                                                                    
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : SysTick_Ticks_t Ticks                     
* \Parameters (out): None                                                      
* \Return value:   : E_OK or E_NOT_OK
*******************************************************************************/
Std_ReturnType SysTick_SyncStart(SysTick_Ticks_t Ticks)
{
    if(SysTick_InitStatus == SYSTICK_NOT_INITIALIZED)
    {
        return E_OK;
    }   

    if(SysTick_Status == SYSTICK_RUNNING)
    {
        return E_OK;
    }

    SysTick->LOAD = Ticks;                                                    /* Delay Reload Value                                       */
	SysTick->VAL  = INITIAL_VALUE;                                            /* Initialize Counter Current Value to 0                    */
    SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Pos);                          /* Enable SysTick Peripheral                                */

    while(BIT_IS_CLEAR(SysTick->CTRL, SysTick_CTRL_COUNTFLAG_Pos) == 1);      /* Wait Till Timer Underflow is Reached                     */

    SysTick->VAL  = INITIAL_VALUE;                                            /* Initialize Counter Current Value to 0 To Clear INT Bit   */

    return E_OK;
}

/******************************************************************************
* \Syntax          : Std_ReturnType SysTick_AsyncStart(void)                                      
* \Description     : Stops Timer                                                                                                    
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : SysTick_Ticks_t Ticks, SysTick_pfCallBack_t FunToBeCalledInISR, 
*                    SysTick_Mode_t Continous_Or_OneShot                    
* \Parameters (out): None                                                      
* \Return value:   : E_OK or E_NOT_OK
*******************************************************************************/
Std_ReturnType SysTick_AsyncStart(SysTick_Ticks_t Ticks, SysTick_pfCallBack_t FunToBeCalledInISR, 
                                  SysTick_Mode_t Continous_Or_OneShot)
{
    if(SysTick_InitStatus == SYSTICK_NOT_INITIALIZED)
    {
        return E_OK;
    }

    if(SysTick_Status == SYSTICK_RUNNING)
    {
        return E_OK;
    }

    SysTick_Status = SYSTICK_RUNNING;                                         /* Change SysTick State To RUNNING */
    SysTickCallBack = FunToBeCalledInISR;                                     /* Set CallBack Function           */
    Continous_Or_OneShot_Flag = Continous_Or_OneShot;                         /* Set Mode Flag to be used in ISR */

    SysTick->LOAD = Ticks;                                                    /* Delay Reload Value                      */
	SysTick->VAL  = INITIAL_VALUE;                                            /* Initialize Counter Current Value to 0   */
    SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Pos);                         /* Enable SysTick Interrutp                */ 
    SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Pos);                          /* Enable SysTick Peripheral               */ 

    return E_OK; 
}

/******************************************************************************
* \Syntax          : Std_ReturnType SysTick_StopTimer(void)                                      
* \Description     : Stops Timer                                                                                                    
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : E_OK or E_NOT_OK
*******************************************************************************/
Std_ReturnType SysTick_StopTimer(void)
{
    if(SysTick_InitStatus == SYSTICK_NOT_INITIALIZED)
    {
        return E_OK;
    }

    CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Pos);                     /* Disable SysTick Peripheral                  */
    SysTick->LOAD = INITIAL_VALUE;                                         /* Reset  Reload Value                         */
	SysTick->VAL  = INITIAL_VALUE;                                         /* Reset Counter Current Value to 0            */

    return E_OK;    
}

/******************************************************************************
* \Syntax          : void SysTick_Handler(void)                                   
* \Description     : SysTick ISR                                                                                                   
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void SysTick_Handler(void)
{
    if(Continous_Or_OneShot_Flag == SYSTICK_ONESHOT)
    {
        SysTick_Status = SYSTICK_IDLE;
        SysTick_StopTimer();
        SysTickCallBack();
    }
    else if(Continous_Or_OneShot_Flag == SYSTICK_CONTINOUS)
    {
       SysTickCallBack();      
    }
    else
    {

    }
}

/**********************************************************************************************************************
 *  END OF FILE: SysTick.c
 *********************************************************************************************************************/
