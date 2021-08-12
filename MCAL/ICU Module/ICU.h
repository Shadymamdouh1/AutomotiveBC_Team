/*
 * ICU.h
 *
 * Created: 8/9/2021 1:12:21 AM
 *  Author: HP
 */ 


#ifndef ICU_H_
#define ICU_H_
#include "types.h"
typedef enum ICU_State_t
{
	rising_mode,
	falling_mode,
	OFF
	
	}ICU_State_t;

typedef enum ICUError_t
{
	ERROR_OK,
	ERROR_NOK
	}ICUError_t;
typedef enum ICUChannels_t
{
	CH0,
	CH1,
	INVALIDCH
}ICUChannels_t;
typedef enum ICUEdgeSelect_t
{
	rising,
	falling,
	INVALIDEdge
}ICUEdgeSelect_t;
typedef enum ICU_Mode_t
{
	NORMAL,
	INVALIDMode
	}ICU_Mode_t;

typedef enum ICUFreqPreScal_t
{
	ICU_OFF,
	NO_prescal,
	clock_8,
	clock_64,
	clock_256,
	clock_1024,
	ExtT1falling,
	ExtT1Rising,
	INVLAIDPre
	
	}ICUFreqPreScal_t;

typedef struct S_ICUConfig_t
{
	ICUChannels_t ICU_CH;
	ICUFreqPreScal_t ICU_precsal;
	ICU_Mode_t ICU_OperationMode;
	}S_ICUConfig_t;

S_ICUConfig_t gS_ICUConfig;
/*******PINS**************/
#define WGM10 0
#define WGM11 1
#define WGM12 3
#define WGM13 4
#define ICES1 6
#define ICNC1 7
#define CS10  0
#define CS11  1
#define CS12  2
#define ICF1  5	

ICUError_t ICU_Init(S_ICUConfig_t const *SICU_config);
//ICUError_t ICU_Start(uint8_t u8_channel,uint8_t u8_edgeType , uint16_t *ICU_Counts);
ICUError_t ICU_MeasureONDuration(uint8_t u8_channel, uint16_t *ICU_Counts);
#endif /* ICU_H_ */