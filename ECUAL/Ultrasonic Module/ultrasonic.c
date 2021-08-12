/*
 * ultrasonic.c
 *
 * Created: 8/10/2021 10:45:56 AM
 *  Author: Shady Mamdouh
 */ 
#include "types.h"
#include "..\MCAL\ICU\ICU.h"
#include "register.h"
#include "ultrasonic.h"

static uint8_t u8_USchannel ;
US_Status_t UltrSonic_Init(uint8_t u8_channel)
{
	gS_ICUConfig.ICU_CH=u8_channel;
	gS_ICUConfig.ICU_OperationMode=NORMAL;
	gS_ICUConfig.ICU_precsal=clock_8;
    ICU_Init(&gS_ICUConfig);
	
	
	u8_USchannel = u8_channel;
}

static int Func_state = Stoped;
US_Status_t UltrSonic_GetDistance(uint16_t *u16_Distance)
{
	volatile uint16_t u16_counts =0;
	uint32_t counter =0;
	/*****************************************
					Error handling
	*****************************************/
	/* NULL Pointer check */
	if (u16_Distance == 0)
	{
		return US_ERROR_NOK;
	}
	/*****************************************/
	/* if first use of the function */
	/* triggering ultrasonic */
	if (Func_state==Stoped)
	{
		PORTB |=(1<<0);
		for(counter=0;counter<50;counter++);
		PORTB &=~(1<<0);
		/* update state to Running */
		Func_state = Running;
	}
	if (Func_state == Running)
	{
		
		if(ICU_MeasureONDuration(u8_USchannel,&u16_counts)==ERROR_OK)
		{
			
			/*Distance calculation */
			*u16_Distance=(SOUNDVEOSITY*u16_counts)/(2*Factor);
			
			/* update function state */
			Func_state = Stoped;
			
			
			return US_ERROR_OK;
			
			
		}
		
		else{
			return US_ERROR_NOK;
		   }
	}
	
	
	
	
	
}