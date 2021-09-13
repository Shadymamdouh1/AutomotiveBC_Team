/*
 * WrlsCom_LCfg.c
 *
 * Created: 9/8/2021 1:58:23 PM
 *  Author: Ahmed Nabil
 */ 
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "WrlsCom.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANT CONFIGURATIONS -*-*-*-*-*-*/
const WrlsCom_Config WrlsCom_BlthDevice_constConfig = 
{	/* Baud Rate*/		  /* Role */		/* Name */		/* Password*/
	     38400,			WRLS_COM_ROLE,	 "CU1 - 4",		  "228989"
};

const uint8_t WrlsCom_BlthDevice_Handshake_Packet[6] = {0x01, 0x03, 0x41, 0x45, 0x48, '\0'};