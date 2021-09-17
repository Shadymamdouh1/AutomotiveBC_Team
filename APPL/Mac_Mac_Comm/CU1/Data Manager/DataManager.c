/*****************************************************************************
* Module: Data Manager Module
* File Name: DataManager.c
* Description:Source file for Data Manager Module
* Author: Shady Mamdouh
* Date: 12/9/2021
******************************************************************************/
/**************************************INCLUDES*********************************************/
#include "..\..\..\Microcontroller\Platform_Types.h"
#include "..\..\..\Microcontroller\Std_types.h"
#include "..\Animation Module\Animation.h"
#include "..\Kpd_Input Module\KpdInput.h"
/******************************************************************************************/
/************************************Global variables****************************************/
/* wireless Communication module states */
#define WRLSCOM_STATE_UNINIT				0U
#define WRLSCOM_STATE_MALFUNCTION			1U
#define WRLSCOM_STATE_DEVICE_SEARCH			2U
#define WRLSCOM_STATE_IDLE					3U
#define WRLSCOM_STATE_VERIFICATION			4U
#define WRLSCOM_STATE_CONNECTED			    5U
#define WRLSCOM_STATE_DATA_READY			6U
#define WRLSCOM_STATE_DEVICE_ERASE          7U


#define FIXED_PACKET_HEADER				0xAA
#define KEYPAD_DATA_REQ_TYPE			0x03
#define KEYPAD_DATA_LENGTH				0x01
#define KEYPAD_DATA_PACKET_SIZE			0x04

#define KEYPAD_PASS_CHANGE_REQ_TYPE     0x04
#define KEYPAD_PASS_CHANGE_LENGTH       0x00
#define KEYPAD_PASS_CHANGE_PACKET_SIZE  0x03






uint8_t WrlsCom_OldState ;
uint8_t WrlsCom_CurrentState ;

#define MAX_PACKET_SIZE  50U
uint8_t PacketBuffer[MAX_PACKET_SIZE];
/*Pointer to struct of Keypad input */
KpdInput_strInputModuleDataInfo_t *KeyPadDataInfo ;
/*****************************************************************************************/
/***************************************States*******************************************/
uint8_t OldState ;
uint8_t CurrentState ;
/***************************************************************************************/
void GetState(void)
{
	/* Get wireless comm state */
	uint8_t State;
	uint8_t *KeypadData ;
	WrlsCom_getState(&State);
	WrlsCom_CurrentState =State;
	
	/*Get keypad input state */
	KeypadInputModule_getDataInfo(KeyPadDataInfo);
	
}
void UpdateState(void)
{
	switch(WrlsCom_CurrentState)
	{
		case WRLSCOM_STATE_MALFUNCTION :
		{
			if (WrlsCom_CurrentState==WrlsCom_OldState)
			{
				break;
			}
			else
			{
				/* Animate LED with MALFunction Pattern */
				ANI_Start(LED_DEVICE_ID,0,MAL_FUN_PATTERN);
				/* Update old state to current state to avoid execute the same line every time */
				WrlsCom_CurrentState=WrlsCom_OldState;
				break;
			}
			 
			
		}
		case WRLSCOM_STATE_DEVICE_SEARCH :
		{
			if (WrlsCom_CurrentState==WrlsCom_OldState)
			{
				break;
			}
			else
			{
				/* Animate LED with Device search pattern Pattern */
				ANI_Start(LED_DEVICE_ID,0,DEVICE_SEARCH_PATTERN);
				
				/* Update old state to current state to avoid execute the same line every time */
				WrlsCom_CurrentState=WrlsCom_OldState;
				break;
			}
		}
		case WRLSCOM_STATE_VERIFICATION :
		{
			if (WrlsCom_CurrentState==WrlsCom_OldState)
			{
				break;
			}
			else
			{
				/* Animate LED with Device Verification pattern  */
				ANI_Start(LED_DEVICE_ID,0,VER_SEARCH_PATTERN);
				
				/* Update old state to current state to avoid execute the same line every time */
				WrlsCom_CurrentState=WrlsCom_OldState;
				break;
			}
		}
		case WRLSCOM_STATE_CONNECTED :
		{
			if (WrlsCom_CurrentState==WrlsCom_OldState)
			{
				break;
			}
			else
			{
				/* Animate LED with Device Connection ON pattern  */
				ANI_Start(LED_DEVICE_ID,0,CONNECTION_ON_PATTERN);
				
				/* Update old state to current state to avoid execute the same line every time */
				WrlsCom_CurrentState=WrlsCom_OldState;
				break;
			}
		}
		case WRLSCOM_STATE_IDLE :
		{
			
			
				WrlsCom_CurrentState=WrlsCom_OldState;
				/* Check if Data need to be Transmitted */
				switch(KeyPadDataInfo->KeypadScanState)
				{
					case KPDINPUT_IDLE :
					{
						/*No Data */
						break;
					}
					case KPDINPUT_ERASE_DEVICE :
					{
						/*Set wireless Comm in Erase device to switch to advertising mode */
						WrlsCom_setState(WRLSCOM_STATE_DEVICE_ERASE);
						
						/*Update current state to Searching */
						WrlsCom_CurrentState = WRLSCOM_STATE_DEVICE_SEARCH;
						break;
					}
					case KPDINPUT_PASS_RESET :
					{
						DataTransmit(KPDINPUT_PASS_RESET);
						break;
					}
					case KPDINPUT_DATA :
					{
						DataTransmit(KPDINPUT_DATA);
						break;
					}
					
				}
				
		
				break;
			
		}
		
	}
}
/**********************************************************************************************************
* Parameters (in): DataType
* Parameters (out): None
* Return value: LEDReturn_t
* Description: This function used to transmit packet using wireless comm
***********************************************************************************************************/
void DataTransmit(uint8_t DataType)
{
	switch(DataType)
	{
		case KPDINPUT_DATA :
		{
			/* Data frame*/
			
			/*Fixed Packet Header */
			PacketBuffer[0] = FIXED_PACKET_HEADER;
			/*Request type */
			PacketBuffer[1] = KEYPAD_DATA_REQ_TYPE;
			/*Request length */
			PacketBuffer[2] = KEYPAD_DATA_LENGTH;
			/*Data */
			PacketBuffer[3]= KeyPadDataInfo->InputModuleData;
			
			/* Set data to be transmitted */
			WrlsCom_TransmitData(PacketBuffer,KEYPAD_DATA_PACKET_SIZE);
			break;
		}
		case KPDINPUT_PASS_RESET :
		{
			/* Data framming */
			
			/*Fixed Packet Header */
			PacketBuffer[0] = FIXED_PACKET_HEADER;
			/*Request type */
			PacketBuffer[1] = KEYPAD_PASS_CHANGE_REQ_TYPE;
			/*Request length */
			PacketBuffer[2] = KEYPAD_PASS_CHANGE_LENGTH;
			/* Set data to be transmitted */
			WrlsCom_TransmitData(PacketBuffer,KEYPAD_PASS_CHANGE_PACKET_SIZE);
			
			break;
		}
	}
}

/**********************************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: LEDReturn_t
* Description: This function is the module main function 
***********************************************************************************************************/
void DataMangerMainFunction(void)
{
	GetState();
	UpdateState();
}
