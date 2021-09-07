/*****************************************************************************
* Module: Led Module
* File Name: Led_Cfg.c
* Description: Source file for LED Module
* Author: Mohamed Magdy
* Date: 20-July-2021
******************************************************************************/


/*- INCLUDES
----------------------------------------------*/
#include "Led.h"

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/* configuration of leds to be used */
strLed_Config_t strLed_Config[USED_LEDS]=
{
	   /*Led Dio Id*/		   
	{  LED_1_DIO_ID },
	{  LED_2_DIO_ID },
	{  LED_3_DIO_ID }
};