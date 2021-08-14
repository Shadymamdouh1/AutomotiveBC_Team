/*****************************************************************************
* Module: SW_ICU Module
* File Name: ICU_Cfg.c
* Description: Source file for SW_ICU Module
* Author: Shady Mamdouh
* Date: 8/12/2021
******************************************************************************/

/**************************INCLUDES***************************************/
#include "ICU.h"
#include "..\Interrupt Driver\ISR_Cfg.h"
#include "..\Interrupt Driver\ISR.h"


/************************************************************************/
/**********************States types************************************/
#define ICU_Stoped   0
#define ICU_Rising   1
#define ICU_Falling  2
#define ICU_ReadyToReturnVal 3
/***********************************************************************/

/**************************Global variables*******************************/
static uint8_t ICU_CH1_STATE =ICU_Stoped ;
static uint32_t ICU_CH1_Counts =0;
/*********************************************************************/
void ICU_CH1CallBackFunction(void)
{
	
	if (ICU_CH1_STATE==ICU_Rising)
	{
		/* start  counter */
		Gpt_StartTimer(ICU_1);
		/* update function state */
		ICU_CH1_STATE =ICU_Falling;
		
		
		/* Reverse the external interrupt polarity */
		EnableExternalInterrupts_INT2(FALLING_EDGE);
		
	}
	else if (ICU_CH1_STATE==ICU_Falling)
	{
		
		/* Get the counter value */
		Gpt_ReturnCounterVal(TIMER_1,&ICU_CH1_Counts);
		
		/* Stop the counter */
		GptStop(ICU_1);
		
		/* Update function state */
		ICU_CH1_STATE = ICU_ReadyToReturnVal;
		/* Enable interrupt */
		
		/* disable interrupt */
		DisableExternalInterrupts_INT2();
		//EnableExternalInterrupts_INT0(RISING_EDGE);
	}
	
}
void ICU_Init(void)
{
	GptInit();
	/* update function state */
	ICU_CH1_STATE =ICU_Rising;
	setExtINT2Callback(ICU_CH1CallBackFunction);
	EnableExternalInterrupts_INT2(RISING_EDGE);
}

ICUError_t ICU_GetONPeriod_Counts(uint8_t ChannelId , uint32_t *u32_Counts)
{
	/************** Error Handling **********************/
	if(ChannelId<0 || ChannelId >4)
	{
		return ERROR_NOK;
	}
	if (u32_Counts==0)  //NULL pointer
	{
		return ERROR_NOK;
	}
	/***************************************************/
	
	switch(ChannelId)
	{
		
		case ICU_1 :
		{
			if (ICU_CH1_STATE==ICU_ReadyToReturnVal)
			{
				*u32_Counts = ICU_CH1_Counts;
				
				ICU_CH1_STATE =ICU_Rising;
				/* set call back function */
				setExtINT2Callback(ICU_CH1CallBackFunction);
				/* Enable interrupt */
				EnableExternalInterrupts_INT2(RISING_EDGE);
				return ERROR_OK;
			}
			break;
		}
	}
	
	return ERROR_NOK;
}





