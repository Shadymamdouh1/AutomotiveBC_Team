/*
 * ICU.c
 *
 * Created: 8/9/2021 1:11:58 AM
 *  Author: Shady Mamoduh
 */ 
#include "types.h"
#include "register.h"
#include "ICU.h"
static uint8_t gu8_Clockselect =0;
ICUError_t ICU_Init(S_ICUConfig_t const *SICU_config)
{
	/*************************************************
				    ERROR Handling 
	************************************************/
	/* check pointer */
	if (SICU_config==0)
	{
		return ERROR_NOK;
	}
	/* check ranges */
	/* Wrong channel ID */
	if (SICU_config->ICU_CH < CH0 || SICU_config->ICU_CH >=INVALIDCH )
	{
		return ERROR_NOK;
	}
	/* wrong pre-scal value */
	if (SICU_config->ICU_precsal < ICU_OFF || SICU_config->ICU_precsal >= INVLAIDPre )
	{
		return ERROR_NOK;
	}
	/* wrong operation mode */
	if (SICU_config->ICU_OperationMode < NORMAL || SICU_config->ICU_OperationMode >= INVALIDMode )
	{
		return ERROR_NOK;
	}
  /*************************************************************************/
	switch(SICU_config->ICU_CH)
	{  
		/* in our case Timer 1 represents CH0 */
		case CH0 : 
		{
			if (SICU_config->ICU_OperationMode == NORMAL)
			{   
				/* clear WGM10 and WGM11 */
				TCCR1A &=~(0b11<<WGM10);
				
				/* clear WGM12 and WGM13 */
				TCCR1B &=~(0b11<<WGM12);
				
			}
			else
			{
				/* for future use */
			}
			break;
		}
	}
	/* assigning clock source to global variable to be used by start function */
	/* ICU will start once the clock source is assigned so it will be handled later*/
	
	gu8_Clockselect = SICU_config->ICU_precsal;
}
//static uint16_t RisingCounts;
static uint16_t FalligCounts ;
static uint8_t ICU_State=OFF;
ICUError_t ICU_MeasureONDuration(uint8_t u8_channel, uint16_t *ICU_Counts)
{
	
	/*************************************************
				    ERROR Handling 
	************************************************/
	if (ICU_Counts==0)
	{
		/* NULL Pointer */
		return ERROR_NOK;
	}
	if ( u8_channel >=INVALIDCH )
	{
		return ERROR_NOK;
	}
	
	/***********************************/
	if (ICU_State == OFF)
	{ 
		
		
		
		
		/* enable rising edge mode */
		TCCR1B |=(1<<ICES1);
		ICU_State =rising_mode;
		
		/* Start the counter */
		/*start ICU by assigning the clock */
		/* clear CS12:10 */
		TCCR1B &=~(0b111<<CS10);
		
		/* set clock */
		TCCR1B |=(gu8_Clockselect<<CS10);
		
	}
	/* if ICU flag is high */
	if ( ( (TIFR &(1<<ICF1))>>ICF1 ) ==1 )
	{
		if (ICU_State==rising_mode)
		{
			/* get ICU counts */
			//RisingCounts =ICR1;
			TCNT1 =0;
			/* clear flag */
			TIFR |=(1<<ICF1);
			
			ICU_State =falling_mode;
			
			/* enable falling edge */
			TCCR1B &=~(1<<ICES1);
			
			
			
		}
		else //if (ICU_State == falling_mode)
		{
			   FalligCounts = ICR1;
			   /* clear flag */
			   TIFR |=(1<<ICF1);
			   
			   /* update state to off */
			   ICU_State = OFF;
			   
			   //* clear counter */
			   TCNT1 =0;
			   
			   /* disable the ICU */
			   
			   /* set clock to 0*/
			   TCCR1B &=~(0b111<<CS10);
			   
			   /* update the difference in counts */
			  *ICU_Counts = FalligCounts;
			  
			  
			  
			  return ERROR_OK;
		}
		
		
		
		
		
	}
	return ERROR_NOK;
}