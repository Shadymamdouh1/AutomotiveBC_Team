/*****************************************************************************
* Module: Lcd Module
* File Name: Lcd.c
* Description: Source file for Lcd Module
* Author: Mohamed Magdy
* Date: 24-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "Lcd.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
enuLcd_Status_t Lcd_Status = LCD_STATUS_ERROR_OK;
enuLcd_initStatus_t Lcd_Init = LCD_NOT_INITIALIZED;

/* states */
#if (AsyncMode == TRUE)
uint8_t LCD_NEXT_STATE = IDLE;
uint8_t LCD_SEND_STRING_STATE = IDLE;
uint8_t LCD_CLEAR_DISPLAY_STATE = IDLE;
uint8_t LCD_SET_CURSOR_STATE = IDLE;
uint8_t LCD_SENDING_CHAR = IDLE;
uint8_t LCD_SEND_COMMAND_STATE = IDLE;

uint8_t Lcd_Init_DoneFlag = FALSE;

#define LCD_INIT_4BITS_COMMAND_1_ID			1
#define LCD_INIT_4BITS_COMMAND_2_ID			2
#define LCD_LINES_2_FONT_5x8_COMMAND_ID		3		
#define LCD_DISPLAY_OFF_COMMAND_ID			4
#define LCD_CLEAR_COMMAND_ID				5
#define LCD_ENTRY_MODE_COMMAND_ID			6
#define LCD_DISPLAY_ON_COMMAND_ID			7

uint8_t gu8_currentlyRunningCommand = LCD_INIT_4BITS_COMMAND_1_ID;
 


#endif

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/************************************************************************************************************************/
/*********************************************** BLOCKING APIS **********************************************************/
/************************************************************************************************************************/

#if (AsyncMode == FALSE)
	enuLcd_Status_t Lcd_init(void)
	{
		if(Lcd_Init == LCD_INITIALIZED) return LCD_STATUS_ERROR_NOK;
		
		Dio_init(strDio_pins);
	
		//Activate 4 bit mode
		Lcd_sendCommand(INIT_4BITS_COMMAND_1);
		Lcd_sendCommand(INIT_4BITS_COMMAND_2);
		
		//Function Set (2 lines & 5x8 font)
		Lcd_sendCommand(LINES_2_FONT_5x8);
		
		//Display OFF
		Lcd_sendCommand(DISPLAY_OFF);
		
		//Clear Display
		Lcd_sendCommand(CLEAR);
		
		//Entry Mode Set
		Lcd_sendCommand(ENTRY_MODE);
		
		//Display ON
		Lcd_sendCommand(DISPLAY_ON);
		
		Lcd_Init = LCD_INITIALIZED;
		return LCD_STATUS_ERROR_OK;
	}
	
	enuLcd_Status_t Lcd_sendData_4bitMode(uint8_t u8_data)
	{
		Lcd_sendHigherNibble(u8_data);							//send higher nibble
		Lcd_toggleEnable();		//toggle enable
	
		Lcd_sendLowerNibble(u8_data);							//send lower nibble
		Lcd_toggleEnable();		//toggle enable
	
		Delay_ms(2);
		
		return LCD_STATUS_ERROR_OK;
	}
	
	enuLcd_Status_t Lcd_cursorPosition(uint8_t u8_xAxis, uint8_t u8_yAxis)
	{
		uint8_t au8_positions[4] = {0, 64, Lcd_Columns, Lcd_Columns+64};
		
		Lcd_sendCommand(0x80+au8_positions[u8_xAxis-1]+(u8_yAxis-1));
		
		return LCD_STATUS_ERROR_OK;
	}
	
	
	enuLcd_Status_t Lcd_clearDisplay(void)
	{
		Lcd_sendCommand(CLEAR);
		return LCD_STATUS_ERROR_OK;
	}
	
	
	enuLcd_Status_t Lcd_sendString(uint8_t* au8_string)
	{
		uint8_t u8_loopCounter = Initial_Value;
		for (u8_loopCounter=Initial_Value;au8_string[u8_loopCounter]!='\0';u8_loopCounter++)
		{
			Lcd_sendCharacter(au8_string[u8_loopCounter]);
		}
		
		return LCD_STATUS_ERROR_OK;
	}

	enuLcd_Status_t Lcd_sendCommand(uint8_t u8_command)
	{
	
		Dio_writePin(RS_DIO_ID, STD_LOW);			//activate command mode
		
		Lcd_sendData_4bitMode(u8_command);
		
		return LCD_STATUS_ERROR_OK;
	}	
#endif



enuLcd_Status_t Lcd_toggleEnable(void)
{
	Dio_writePin(EN_DIO_ID, STD_HIGH);		//set enable ON
	Delay_ms(1);
	Dio_writePin(EN_DIO_ID, STD_LOW);		//set enable OFF
	
	return LCD_STATUS_ERROR_OK;
}


enuLcd_Status_t Lcd_sendCharacter(uint8_t u8_char)
{
	Dio_writePin(RS_DIO_ID, STD_HIGH);		//activate DATA mode
	Lcd_sendData_4bitMode(u8_char);
	return LCD_STATUS_ERROR_OK;
}


enuLcd_Status_t Lcd_sendVariableInt(uint16_t u16_number, uint8_t u8_base)
{
	uint8_t pu8_String[6];

	integerToString(u16_number, pu8_String, u8_base);

	Lcd_sendString(pu8_String);
	
	return LCD_STATUS_ERROR_OK;
}



/************************************************************************************************************************/
/*********************************************** NON BLOCKING APIS ******************************************************/
/************************************************************************************************************************/

#if (AsyncMode == TRUE)
	enuLcd_Status_t Lcd_init(void)
	{
		if(Lcd_Init == LCD_INITIALIZED || LCD_SEND_COMMAND_STATE == RUNNING) return LCD_STATUS_ERROR_NOK;
		
		if(Lcd_Init_DoneFlag == TRUE)
		{
			Lcd_Init = LCD_INITIALIZED;
			return LCD_STATUS_ERROR_OK;
		}
		
		Dio_init(strDio_pins);
		GptInit();
		
		//Delay_ms(20);
		
		switch(gu8_currentlyRunningCommand)
		{
			case(LCD_INIT_4BITS_COMMAND_1_ID):
			{
				//Activate 4 bit mode
				Lcd_sendCommand(INIT_4BITS_COMMAND_1);
				break;
			}
			case(LCD_INIT_4BITS_COMMAND_2_ID):
			{
				//Activate 4 bit mode
				Lcd_sendCommand(INIT_4BITS_COMMAND_2);
				break;
			}
			case(LCD_LINES_2_FONT_5x8_COMMAND_ID):
			{
				//Function Set (2 lines & 5x8 font)
				Lcd_sendCommand(LINES_2_FONT_5x8);
				break;
			}
			case(LCD_DISPLAY_OFF_COMMAND_ID):
			{
				//Display OFF
				Lcd_sendCommand(DISPLAY_OFF);
				break;
			}
			case(LCD_CLEAR_COMMAND_ID):
			{
				//Clear Display
				Lcd_sendCommand(CLEAR);
				break;
			}
			case(LCD_ENTRY_MODE_COMMAND_ID):
			{
				//Entry Mode Set
				Lcd_sendCommand(ENTRY_MODE);
				break;
			}
			case(LCD_DISPLAY_ON_COMMAND_ID):
			{
				//Display ON
				Lcd_sendCommand(DISPLAY_ON);
				break;
			}
			default: return LCD_STATUS_ERROR_NOK;									
		}

		return LCD_STATUS_ERROR_OK;
	}

	enuLcd_Status_t Lcd_cursorPosition(uint8_t u8_xAxis, uint8_t u8_yAxis)
	{
		if(Lcd_Init != LCD_INITIALIZED) return LCD_STATUS_ERROR_NOK;
		
		if(LCD_CLEAR_DISPLAY_STATE == RUNNING || LCD_SEND_STRING_STATE == RUNNING)
		{
			if(LCD_NEXT_STATE == IDLE)
			{
				LCD_NEXT_STATE = SET_CURSOR_PENDING;
			}
			return LCD_STATUS_ERROR_NOK;
		}
		else if(LCD_NEXT_STATE == SET_CURSOR_PENDING)
		{
			LCD_SET_CURSOR_STATE = RUNNING;
			LCD_NEXT_STATE = IDLE;
		}
		else if(LCD_NEXT_STATE == SEND_STRING_PENDING || LCD_NEXT_STATE == CLEAR_DISPLAY_PENDING)
		{
			return LCD_STATUS_ERROR_NOK;
		}
		else if(LCD_NEXT_STATE == IDLE)
		{
			LCD_SET_CURSOR_STATE = RUNNING;
			LCD_NEXT_STATE = IDLE;
		}
		else
		{
			return LCD_STATUS_ERROR_NOK;
		}
		
		uint8_t au8_positions[4] = {0, 64, Lcd_Columns, Lcd_Columns+64};
		Lcd_sendCommand(0x80+au8_positions[u8_xAxis-1]+(u8_yAxis-1));
		
		return LCD_STATUS_ERROR_OK;
	}
	
	enuLcd_Status_t Lcd_clearDisplay(void)
	{
		if(Lcd_Init != LCD_INITIALIZED) return LCD_STATUS_ERROR_NOK;
		
		if(LCD_SEND_STRING_STATE == RUNNING || LCD_SET_CURSOR_STATE == RUNNING)
		{
			if(LCD_NEXT_STATE == IDLE)
			{
				LCD_NEXT_STATE = CLEAR_DISPLAY_PENDING;
			}
			return LCD_STATUS_ERROR_NOK;
		}
		else if(LCD_NEXT_STATE == CLEAR_DISPLAY_PENDING)
		{
			LCD_CLEAR_DISPLAY_STATE = RUNNING;
			LCD_NEXT_STATE = IDLE;
		}
		else if(LCD_NEXT_STATE == SEND_STRING_PENDING || LCD_NEXT_STATE == SET_CURSOR_PENDING)
		{
			return LCD_STATUS_ERROR_NOK;
		}
		else if( LCD_NEXT_STATE == IDLE)
		{
			LCD_CLEAR_DISPLAY_STATE = RUNNING;
			LCD_NEXT_STATE = IDLE;
		}
		else
		{
			return LCD_STATUS_ERROR_NOK;
		}
		
		Lcd_sendCommand(CLEAR);
		return LCD_STATUS_ERROR_OK;
	}
	
	enuLcd_Status_t Lcd_sendString(uint8_t* au8_string)
	{
		if(Lcd_Init != LCD_INITIALIZED || LCD_SENDING_CHAR == RUNNING) return LCD_STATUS_ERROR_NOK;
		
		if(LCD_CLEAR_DISPLAY_STATE == RUNNING || LCD_SET_CURSOR_STATE == RUNNING)
		{
			if(LCD_NEXT_STATE == IDLE)
			{
				LCD_NEXT_STATE = SEND_STRING_PENDING;
			}
			return LCD_STATUS_ERROR_NOK;
		}
		else if(LCD_NEXT_STATE == SEND_STRING_PENDING)
		{
			LCD_SEND_STRING_STATE = RUNNING;
			LCD_NEXT_STATE = SEND_STRING_PENDING;
			LCD_SENDING_CHAR = RUNNING;
		}
		else if(LCD_NEXT_STATE == SET_CURSOR_PENDING || LCD_NEXT_STATE == CLEAR_DISPLAY_PENDING)
		{
			return LCD_STATUS_ERROR_NOK;
		}
		else if(LCD_NEXT_STATE == IDLE)
		{
			LCD_SEND_STRING_STATE = RUNNING;
			LCD_NEXT_STATE = SEND_STRING_PENDING;
			LCD_SENDING_CHAR = RUNNING;
		}
		else
		{
			return LCD_STATUS_ERROR_NOK;
		}
		
		
		static uint8_t u8_stringIndexCounter = Initial_Value;
		
		if(au8_string[u8_stringIndexCounter]!='\0')
		{
			Lcd_sendCharacter(au8_string[u8_stringIndexCounter]);
			u8_stringIndexCounter++;
		}
		else
		{
			u8_stringIndexCounter = Initial_Value;
			LCD_SEND_STRING_STATE = IDLE;
			LCD_NEXT_STATE = IDLE;
			LCD_SENDING_CHAR = IDLE;
		}
	
		return LCD_STATUS_ERROR_OK;
	}
	
	enuLcd_Status_t Lcd_sendData_4bitMode(uint8_t u8_data)
	{
		Lcd_sendHigherNibble(u8_data);							//send higher nibble
		Lcd_toggleEnable();		//toggle enable
	
		Lcd_sendLowerNibble(u8_data);							//send lower nibble
		Lcd_toggleEnable();		//toggle enable
		
		/* delay after byte sent */
		GptStart_aSync(TIMER_USED_ID, DelayTicks, LcdDelayFinished);
		
		return LCD_STATUS_ERROR_OK;
	}

	enuLcd_Status_t Lcd_sendCommand(uint8_t u8_command)
	{
		if(LCD_SEND_COMMAND_STATE == RUNNING) return LCD_STATUS_ERROR_NOK;
		LCD_SEND_COMMAND_STATE = RUNNING;
		
		Dio_writePin(RS_DIO_ID, STD_LOW);			//activate command mode
		
		Lcd_sendData_4bitMode(u8_command);
		
		return LCD_STATUS_ERROR_OK;
	}
			
	void LcdDelayFinished(void)
	{
		if(Lcd_Init == LCD_NOT_INITIALIZED)
		{
			if(gu8_currentlyRunningCommand == LCD_DISPLAY_ON_COMMAND_ID)
			{
				/* if all commands done state module as initialized */
				Lcd_Init_DoneFlag = TRUE;
				LCD_SEND_COMMAND_STATE = IDLE;			
			}
			else
			{
				gu8_currentlyRunningCommand++;
				LCD_SEND_COMMAND_STATE = IDLE;				
			}
		}
		else
		{
			if(LCD_SET_CURSOR_STATE == RUNNING)
			{
				LCD_SET_CURSOR_STATE = IDLE;
				LCD_SEND_COMMAND_STATE = IDLE;
			}
			else if(LCD_CLEAR_DISPLAY_STATE == RUNNING)
			{
				LCD_CLEAR_DISPLAY_STATE = IDLE;
				LCD_SEND_COMMAND_STATE = IDLE;
			}
			else if(LCD_SEND_STRING_STATE == RUNNING)
			{
				LCD_SENDING_CHAR = IDLE;
			}			
		}

	}
#endif











enuLcd_Status_t Lcd_sendLowerNibble(uint8_t u8_data)
{
	if((u8_data & 0x01) != 0)
	{
		Dio_writePin(D4_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D4_DIO_ID, STD_LOW);
	}

	if((u8_data & 0x02) != 0)
	{
		Dio_writePin(D5_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D5_DIO_ID, STD_LOW);
	}
	
	if((u8_data & 0x04) != 0)
	{
		Dio_writePin(D6_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D6_DIO_ID, STD_LOW);
	}
	
	if((u8_data & 0x08) != 0)
	{
		Dio_writePin(D7_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D7_DIO_ID, STD_LOW);
	}
	
	return LCD_STATUS_ERROR_OK;
}

enuLcd_Status_t Lcd_sendHigherNibble(uint8_t u8_data)
{
	if((u8_data & 0x10) != 0)
	{
		Dio_writePin(D4_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D4_DIO_ID, STD_LOW);
	}

	if((u8_data & 0x20) != 0)
	{
		Dio_writePin(D5_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D5_DIO_ID, STD_LOW);
	}
	
	if((u8_data & 0x40) != 0)
	{
		Dio_writePin(D6_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D6_DIO_ID, STD_LOW);
	}
	
	if((u8_data & 0x80) != 0)
	{
		Dio_writePin(D7_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D7_DIO_ID, STD_LOW);
	}
	
	return LCD_STATUS_ERROR_OK;
}












enuLcd_Status_t Lcd_init_test(void)
{
	if(Lcd_Init == LCD_INITIALIZED) return LCD_STATUS_ERROR_NOK;
	
	Dio_init(strDio_pins);
	
	// start up delay
	Delay_ms(20);
	//Activate 4 bit mode
	Lcd_sendCommand_test(INIT_4BITS_COMMAND_1);
	Lcd_sendCommand_test(INIT_4BITS_COMMAND_2);
	
	//Function Set (2 lines & 5x8 font)
	Lcd_sendCommand_test(LINES_2_FONT_5x8);
	
	//Display OFF
	Lcd_sendCommand_test(DISPLAY_OFF);
	
	//Clear Display
	Lcd_sendCommand_test(CLEAR);
	
	//Entry Mode Set
	Lcd_sendCommand_test(ENTRY_MODE);
	
	//Display ON
	Lcd_sendCommand_test(DISPLAY_ON);
	
	Lcd_Init = LCD_INITIALIZED;
	return LCD_STATUS_ERROR_OK;
}
	
enuLcd_Status_t Lcd_sendCommand_test(uint8_t u8_command)
{
	
	Dio_writePin(RS_DIO_ID, STD_LOW);			//activate command mode
	
	Lcd_sendData_4bitMode_test(u8_command);
	
	return LCD_STATUS_ERROR_OK;
}
		
		
		
enuLcd_Status_t Lcd_sendData_4bitMode_test(uint8_t u8_data)
{
	Lcd_sendHigherNibble(u8_data);							//send higher nibble
	Lcd_toggleEnable();		//toggle enable
	
	Lcd_sendLowerNibble(u8_data);							//send lower nibble
	Lcd_toggleEnable();		//toggle enable
	
	Delay_ms(2);
	
	return LCD_STATUS_ERROR_OK;
}