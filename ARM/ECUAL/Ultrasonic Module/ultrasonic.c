/*****************************************************************************
* Module: Ultrasonic Module
* File Name: Ultrasonic.c
* Description: Source file for Ultrasonic sensor Module
* Author: Shady Mamdouh
* Date: 8/12/2021
******************************************************************************/
#include "Ultrasonic.h"
/*****************************/

/************************** Constants ***********************************/
#define US_STOPPED					0UL
#define US_RUNNING					1UL
#define US_METER_CM_FACTOR			100UL
#define US_DISTANCE_DIVISION	    2UL
#define SOUND_VELOCITY				343UL
#define TOGGLE_DELAY_COUNTS			100U
/********************************Global variables******************************/

static uint8 US_State[US_USED_CHANNELS] = {US_STOPPED};
    

Std_ReturnType Ultrasonic_Init(void)
{    
	
	Dio_init(strDio_pins);
	ICU_Init();
	
	return E_OK;
}


void US_Trigger(US_Channel_t US_ChannelID)
{
	uint8 u8_counter=0;
	Dio_WriteChannel(US_Configurations[US_ChannelID].Trigger_Pin ,PIN_HIGH);
	/* delay */
	for(u8_counter=0 ;u8_counter<TOGGLE_DELAY_COUNTS ;u8_counter++);
	
	Dio_WriteChannel(US_Configurations[US_ChannelID].Trigger_Pin ,PIN_LOW);
}


uint16 US_CalDistance(US_Channel_t US_ChannelID, uint32 u32_counts)
{
	uint16 u16_Disance=0;
	float32 time_f32 ;
	//time_f32 = (u32_counts *((float32)(strGpt_Channels[ ICU_Configurations[ US_Configurations[US_ChannelID].ICU_ChannedID ].Gpt_Channel ].u8_Prescaler)\
		//							/SYS_CLOCK_FREQUENCY));

	
	time_f32 = u32_counts /1000.0;  // divide by 1000 to convert from msec to seconds
	u16_Disance=( ((SOUND_VELOCITY*time_f32)/US_DISTANCE_DIVISION) *US_METER_CM_FACTOR );
	
	return u16_Disance;
}


Std_ReturnType Ultrasonic_GetDistance(US_Channel_t US_ChannelID ,  uint16 *u16_Distance)
{
	uint32 US_Counts=0;
	uint16 u16_DistanceVal=0;
	/***************************************************************
						Error handling
	**************************************************************/
	/* NULL Pointer check */
	if (u16_Distance == 0)
	{
		return E_NOT_OK;
	}
	/************************************************************/
	/* check state */
	if(US_State[US_ChannelID] == US_STOPPED)
	{
		/* Update State */
		US_State[US_ChannelID] = US_RUNNING;
				
		/* trigger On PORTA PIN 0 */
		US_Trigger(US_ChannelID);
		ICU_GetONPeriod_Counts(US_Configurations[US_ChannelID].ICU_ChannedID ,&US_Counts);
				
		return E_NOT_OK;
	}
	else if (US_State[US_ChannelID] == US_RUNNING)
	{
		if (ICU_GetONPeriod_Counts(US_Configurations[US_ChannelID].ICU_ChannedID ,&US_Counts) == E_OK)
		{	
			/* Get distance */
			u16_DistanceVal =US_CalDistance(US_ChannelID, US_Counts);
						
			/* return the distance */
			*u16_Distance = u16_DistanceVal;
			/* Update State */
			US_State[US_ChannelID] = US_STOPPED;
						
			return E_OK;
		}
	}
	return E_NOT_OK;
}
