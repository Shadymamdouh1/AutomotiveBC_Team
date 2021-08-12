/*
 * ultrasonic.h
 *
 * Created: 8/10/2021 10:46:09 AM
 *  Author: shady mamdouh
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_


#define SOUNDVEOSITY 343UL
#define Factor 10000UL

#define Channel 0 //CHANNEL_0

#define Stoped 0
#define Running 1

typedef enum US_Status_t
{
	US_ERROR_OK,
	US_ERROR_NOK
}US_Status_t;



/********************************************
				   APIs
********************************************/
US_Status_t UltrSonic_Init(uint8_t u8_channel);
US_Status_t UltrSonic_GetDistance(uint16_t *u16_Distance);
#endif /* ULTRASONIC_H_ */