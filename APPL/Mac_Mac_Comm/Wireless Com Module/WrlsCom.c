/*
 * WrlsCom.c
 *
 * Created: 9/8/2021 1:58:23 PM
 *  Author: Ahmed Nabil
 */ 
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "WrlsCom.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/
#define MAX_POSSIBLE_BR					5U

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- GLOBAL STATIC VARIABLES *-*-*-*-*-*/
static uint32_t WrlsCom_PossibleBaudRates[MAX_POSSIBLE_BR] = {9600, 19200, 38400, 57600, 115200};
static uint8_t WrlsCom_State = WRLSCOM_STATE_UNINIT;
/*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*/
/*-*-*-*-*- FUNCTIONS LIKE MACROS -*-*-*-*-*-*/


/*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- FUNCTIONS IMPLEMENTATION -*-*-*-*-*-*/

Std_ReturnType WrlsCom_init(void)
{
	uint32_t currentBaudRate = WrlsCom_BlthDevice_constConfig.Device_BaudRate;
	uint8_t BR_index=0;
	
	if(Blth_testDevice() == E_NOT_OK)	/* If the test failed */
	{
		/* Test the communication with bluetooth to check baudrate */
		while(1)
		{
			currentBaudRate = WrlsCom_PossibleBaudRates[BR_index];
			Uart_setBaudRate(currentBaudRate);
			/* If the current baudrate is working */
			if(Blth_testDevice() == E_OK)
			{
				/* Set the bluetooth to the required baudrate */
				Blth_setBaudRate(WrlsCom_BlthDevice_constConfig.Device_BaudRate);
				/* Set the Uart to the required baudrate */
				Uart_setBaudRate(WrlsCom_BlthDevice_constConfig.Device_BaudRate);
				/* Exit the loop */
				break;
			}
			else
			{
				BR_index++;
			}
			
			if(BR_index == MAX_POSSIBLE_BR)
			{
				/* If all baud rates failed */
				/* Raise state to MALFUNCTION */
				WrlsCom_State = WRLSCOM_STATE_MALFUNCTION;
				return E_NOT_OK;
			}
		}
	}
	else
	{
		/* Check the device's latest configurations */
		uint8_t DeviceRole=0
		/* Get the current role of the device */
		Blth_getRole(&DeviceRole);
		if(DeviceRole != WrlsCom_BlthDevice_constConfig.Device_Role)
		{
			Blth_setRole(WrlsCom_BlthDevice_constConfig.Device_Role);
		}
		else
		{
			/* Successful */
		}
		
		/* Check the name of the device */
		uint8_t currentName[WRLS_COM_MAX_NAME_SIZE] = {0};
		Blth_getName(currentName);
		if(stringCmp(currentName, WrlsCom_BlthDevice_constConfig.Device_Name) == FALSE)
		{
			/* If the name is not equal */
			/* Set the device with the new name */
			Blth_RenameDevice(WrlsCom_BlthDevice_constConfig.Device_Name);
		}
		else
		{
			/* Successful */
		}
		
		/* Check the name of the device */
		uint8_t currentPass[WRLS_COM_MAX_PSWRD_SIZE] = {0};
		Blth_getPassword(currentPass);
		if(stringCmp(currentPass, WrlsCom_BlthDevice_constConfig.Device_Pswrd) == FALSE)
		{
			/* If the password is not equal */
			/* Set the device with the new password */
			Blth_setPassword(WrlsCom_BlthDevice_constConfig.Device_Pswrd);
		}
		else
		{
			/* Successful */
		}
	}
	WrlsCom_State = WRLSCOM_STATE_DEVICE_SEARCH;
	return E_OK;
}

Std_ReturnType WrlsCom_mainFunction(void)
{
	while (1)
	{
		switch(WrlsCom_State)
		{
			case WRLSCOM_STATE_IDLE:
			{
				/* Waiting for Orders after connection is successful */
				break;
			}
			case WRLSCOM_STATE_DEVICE_SEARCH:
			{
				/* Search for MAC Address in EEPROM */
				break;
			}
			case WRLSCOM_STATE_MALFUNCTION:
			{
				/* Notify with MALFUNTION Pattern */
				break;
			}
			case WRLSCOM_STATE_VERIFICATION:
			{
				/* Verify the device connection by sending Handshake */
				break;
			}
			case WRLSCOM_STATE_CONNECTED:
			{
				/* Send Device Data Packet to the device */
				break;
			}
			case WRLSCOM_STATE_UNINIT:
			{
				return E_NOT_OK;
			}
			default:
			{
				return E_NOT_OK;
			}
		}
		
		/* FreeRTOS vTaskDelay Function */
		//vTaskDelay()
	}
}

Std_ReturnType WrlsCom_getState(uint8_t *DeviceState)
{
	*DeviceState = WrlsCom_State;
	
	return E_OK;
}