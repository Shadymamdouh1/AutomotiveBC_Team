/*****************************************************************************
* Module: Ultrasonic Module
* File Name: Ultrasonic.c
* Description: Source file for Ultrasonic sensor Module
* Author: Shady Mamdouh
* Date: 8/12/2021
******************************************************************************/
#include "..\..\MCAL\ICU Module\ICU.h"
//#include "..\..\MCAL\Dio Module\Dio.h"
#include "..\..\Microcontroller\Platform_Types.h"
#include "Ultrasonic.h"
/******************************/     //    Attention will be removed !!!!!!!!!!!!!!!!!!!!!!
#include "..\..\Microcontroller\Atmega32 Registers\Dio_regs.h"
/*****************************/


/********************************Global variables &	Constants ******************************/
#define SOUND_VELOCITY 343UL
static uint32_t  US_CH1_CPU_FREQ_g= 0;
static uint16_t US_CH1_Prescaler_g= 0;

#define US_CH1_Stoped			0UL
#define US_CH1_Running			1UL
#define US_MeterToCM			100UL
#define US_DistanceDivision	    2UL
uint8_t  var=0 ;
US_Status_t Ultrsonic_Init(void)
{    
	//var =
	ICU_Init();
	uint8_t u8_counter =0;
	
	for(u8_counter=0;u8_counter<US_USED_CHANNELS ;u8_counter++)
      {
		  switch(US_Channels[u8_counter].US_ChannedID)
		  {
			  case US_CH_1 :
			  {
				  /******************************* ERROR HANDLING ***************************************/
				 if ( ((US_Channels[u8_counter].CPU_FREQ ) > CPU_FREQ_16M ) || ( (US_Channels[u8_counter].CPU_FREQ) <CPU_FREQ_1M ) )
				 {
					 break;
				 }
				 if (US_Channels[u8_counter].US_CHPreScaler > CPU_FREQ_16M)
				 {
					 break;
				 }
				/*********************************************************************************************/
				
				  /* Update channel frequency */
				  US_CH1_CPU_FREQ_g = US_Channels[u8_counter].CPU_FREQ;
				  
				  /* Update Channel PreScaler */
				  US_CH1_Prescaler_g = US_Channels[u8_counter].US_CHPreScaler;
				 
				  
				  break;
	          }
			  
			  default :
			  {
					return US_ERROR_NOK;
			  }
		  }
		   
	  }
	  return US_ERROR_OK;
}


void US_Ch1Trigger(void)
{
	uint8_t u8_counter=0;
	/*********will be removed *****************/
	DIO_PORTA_DIR |=(1<<0);                                        // attention !!!!!!
	/*******************************************/
	//Dio_writePin(PIN_0,PIN_HIGH);
	DIO_PORTA_DATA |=(1<<0);
	/* delay */
	//for(u8_counter=0;u8_counter<100;u8_counter++);
	GptStart_Sync(TIMER_1, 2);
	//Dio_writePin(PIN_0,PIN_LOW);
	DIO_PORTA_DATA &=~(1<<0);
}


static uint8_t US_CH1_state = US_CH1_Stoped;


uint16_t US_CH1_CalDistance(uint32_t u32_counts)
{
	uint16_t u16_Disance=0;
	float32_t TIME ;
	TIME = (u32_counts *((float32_t)US_CH1_Prescaler_g/US_CH1_CPU_FREQ_g));
	
	u16_Disance=( ((SOUND_VELOCITY*TIME)/US_DistanceDivision) *US_MeterToCM );
	
	return u16_Disance;
}


US_Status_t Ultrsonic_GetDistance(uint8_t US_Channel ,  uint16_t *u16_Distance)
{
	uint32_t US_CH1_Counts=0;
	uint16_t u16_DistanceVal=0;
	/***************************************************************
						Error handling
	**************************************************************/
	/* NULL Pointer check */
	if (u16_Distance == 0)
	{
		return US_ERROR_NOK;
	}
	/************************************************************/
	switch(US_Channel)
	{
		case US_CH_1 :
		{
			/* check state */
			if(US_CH1_state==US_CH1_Stoped)
			{
				/* Update State */
				US_CH1_state =US_CH1_Running;
				
				/* trigger On PORTA PIN 0 */
				US_Ch1Trigger();
				//ICU_GetONPeriod_Counts(US_CH_1,&US_CH1_Counts);
				
				return US_ERROR_NOK;
			}
			else if (US_CH1_state==US_CH1_Running)
			{
				if (ICU_GetONPeriod_Counts(US_CH_1,&US_CH1_Counts)==ERROR_OK)
				{
					
					/* Get distance */
					u16_DistanceVal =US_CH1_CalDistance(US_CH1_Counts);
					
					/* return the distance */
					*u16_Distance = u16_DistanceVal;
					/* Update State */
					US_CH1_state = US_CH1_Stoped;
					
					return US_ERROR_OK;
				}
				else
				{
					return US_ERROR_NOK;
				}
			}
			
			
			break;
		}
		default  :  
		{
			return US_ERROR_NOK;
		}
		
	}
	
	
}