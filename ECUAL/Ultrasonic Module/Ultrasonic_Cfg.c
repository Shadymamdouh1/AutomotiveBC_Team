/*****************************************************************************
* Module: Ultrasonic Module
* File Name: Ultrasonic_Cfg.c
* Description: Source file for Ultrasonic sensor Module
* Author: Shady Mamdouh
* Date: 8/12/2021
******************************************************************************/

#include "Ultrasonic.h"


US_Config_t US_Channels[US_USED_CHANNELS] =
{
	/* US_ChannedID */   /* CPU_FREQ */  /*US_CHPreScaler */
	{  US_CH_1     ,   CPU_FREQ_8M  , PreScaler_8 }
	
};
	