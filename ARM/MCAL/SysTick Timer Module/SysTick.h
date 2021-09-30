/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <SysTick.h>
 *       Module:  SysTick
 *
 *  Description:  Header File For SysTick Module     
 *  
 *********************************************************************************************************************/
#ifndef SYSTICK_H
#define SYSTICK_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "SysTick_Cfg.h"
#include "TM4C123GH6PM.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* These are SysTick Timer execution options to be chosen from */
#define SYSTICK_ONESHOT                   (0x00U)
#define SYSTICK_CONTINOUS                 (0x01U)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef uint32 SysTick_Ticks_t;
typedef void (*SysTick_pfCallBack_t)(void);
typedef uint8 SysTick_Mode_t;

typedef enum
{
	SYSTICK_INITIALIZED,
	SYSTICK_NOT_INITIALIZED
}SysTick_InitStatus_t;

typedef enum
{
    SYSTICK_RUNNING,
    SYSTICK_IDLE
}SysTick_Status_t;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
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
Std_ReturnType SysTick_Init(void);

/******************************************************************************
* \Syntax          : Std_ReturnType SysTick_SyncStart(void)                                      
* \Description     : Stars Timer                                                                                                    
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : SysTick_Ticks_t Ticks                     
* \Parameters (out): None                                                      
* \Return value:   : E_OK or E_NOT_OK
*******************************************************************************/
Std_ReturnType SysTick_SyncStart(SysTick_Ticks_t Ticks);

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
                                  SysTick_Mode_t Continous_Or_OneShot);

/******************************************************************************
* \Syntax          : Std_ReturnType SysTick_StopTimer(void)                                      
* \Description     : Stops Timer                                                                                                    
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : E_OK or E_NOT_OK
*******************************************************************************/
Std_ReturnType SysTick_StopTimer(void);

#endif  /* SYSTICK_H */

/**********************************************************************************************************************
 *  END OF FILE: SysTick.h
 *********************************************************************************************************************/
