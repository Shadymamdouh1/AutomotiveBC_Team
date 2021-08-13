/*****************************************************************************
* Module: ICU Module
* File Name: ICU.h
* Description: Header file for ICU Module
* Author: Shady Mamdouh
* Date: 8/12/2021
******************************************************************************/


#ifndef ICU_H_
#define ICU_H_
#include "..\..\Microcontroller\Platform_Types.h"
#include "ICU_Cfg.h"

#include "..\Gpt Module\Gpt.h"
typedef uint8_t ICU_channel_t;


typedef enum ICUError_t
{
	ERROR_OK,
	ERROR_NOK
	
}ICUError_t;

void ICU_Init(void);
ICUError_t ICU_GetONPeriod_Counts(uint8_t ChannelId , uint32_t *u32_Counts);

/*- EXTERN VARIABLE DECLARATIONS ----------------------------------*/
extern ICU_channel_t ICU_Channels[ICU_USED_CHANNELS];
#endif /* ICU_H_ */