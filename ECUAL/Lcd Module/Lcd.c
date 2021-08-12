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
uint8_t LCD_SENDING_CHAR = FALSE;
#endif

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

enuLcd_Status_t Lcd_init(void)
{
	if(Lcd_Init == LCD_INITIALIZED) return LCD_STATUS_ERROR_NOK;
	
	Lcd_Init = LCD_INITIALIZED;
	
	Dio_init(strDio_pins);
	#if (AsyncMode == TRUE)
	GptInit();
	#endif
	
	//Activate 4 bit mode
	Lcd_sendCommand(0x33);
	Lcd_sendCommand(0x32);
	
	//Function Set (2 lines & 5x8 font)
	Lcd_sendCommand(0x28);
	
	//Display OFF
	Lcd_sendCommand(0x08);
	
	//Clear Display
	Lcd_sendCommand(0x01);
	
	//Entry Mode Set
	Lcd_sendCommand(0x06);
	
	//Display ON
	Lcd_sendCommand(0x0C);
	
	return LCD_STATUS_ERROR_OK;
}


enuLcd_Status_t Lcd_toggleEnable(void)
{
	Dio_writePin(EN_DIO_ID, STD_HIGH);		//set enable ON
	Delay_ms(1);
	Dio_writePin(EN_DIO_ID, STD_LOW);		//set enable OFF
	
	return LCD_STATUS_ERROR_OK;
}


enuLcd_Status_t Lcd_sendCommand(uint8_t u8_command)
{

	Dio_writePin(RS_DIO_ID, STD_LOW);			//activate command mode
	
	Lcd_sendData_4bitMode(u8_command);
	
	return LCD_STATUS_ERROR_OK;
}


enuLcd_Status_t Lcd_sendData_4bitMode(uint8_t u8_data)
{
	Lcd_sendHigherNibble(u8_data);							//send higher nibble
	Lcd_toggleEnable();		//toggle enable

	Lcd_sendLowerNibble(u8_data);							//send lower nibble
	Lcd_toggleEnable();		//toggle enable
	
	#if (AsyncMode == TRUE)
	GptStart_aSync(TIMER_USED_ID, DelayTicks, LcdDelayFinished);
	#elif (AsyncMode == FALSE)
	Delay_ms(2);
	#else
	return LCD_STATUS_ERROR_NOK;
	#endif
	
	return LCD_STATUS_ERROR_OK;
}


enuLcd_Status_t Lcd_sendCharacter(uint8_t u8_char)
{
	Dio_writePin(RS_DIO_ID, STD_HIGH);		//activate DATA mode
	Lcd_sendData_4bitMode(u8_char);
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



enuLcd_Status_t Lcd_sendVariableInt(uint16_t u16_number, uint8_t u8_base)
{
	uint8_t pu8_String[6];

	integerToString(u16_number, pu8_String, u8_base);

	Lcd_sendString(pu8_String);
	
	return LCD_STATUS_ERROR_OK;
}


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


#if (AsyncMode == TRUE)
enuLcd_Status_t Lcd_asyncCursorPosition(uint8_t u8_xAxis, uint8_t u8_yAxis)
{
	if(LCD_CLEAR_DISPLAY_STATE == RUNNING || LCD_SEND_STRING_STATE == RUNNING)
	{
		if(LCD_NEXT_STATE == IDLE)
		{
			LCD_NEXT_STATE = SET_CURSOR_PENDING;
		}
		return LCD_STATUS_ERROR_NOK;
	}
	else if(LCD_NEXT_STATE == SET_CURSOR_PENDING || LCD_NEXT_STATE == IDLE)
	{
		LCD_SET_CURSOR_STATE = RUNNING;
		LCD_NEXT_STATE = IDLE;
	}
	else
	{
		return LCD_STATUS_ERROR_NOK;
	}
	
	Lcd_cursorPosition(u8_xAxis, u8_yAxis);
	return LCD_STATUS_ERROR_OK;
}

enuLcd_Status_t Lcd_asyncClearDisplay(void)
{
	if(LCD_SEND_STRING_STATE == RUNNING || LCD_SET_CURSOR_STATE == RUNNING)
	{
		if(LCD_NEXT_STATE == IDLE)
		{
			LCD_NEXT_STATE = CLEAR_DISPLAY_PENDING;
		}
		return LCD_STATUS_ERROR_NOK;
	}
	else if(LCD_NEXT_STATE == CLEAR_DISPLAY_PENDING || LCD_NEXT_STATE == IDLE)
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

enuLcd_Status_t Lcd_asyncSendString(uint8_t* au8_string)
{
	if(LCD_SENDING_CHAR == TRUE) return LCD_STATUS_ERROR_NOK;
	LCD_SENDING_CHAR = TRUE;

	if(LCD_CLEAR_DISPLAY_STATE == RUNNING || LCD_SET_CURSOR_STATE == RUNNING)
	{
		if(LCD_NEXT_STATE == IDLE)
		{
			LCD_NEXT_STATE = SEND_STRING_PENDING;
		}
		return LCD_STATUS_ERROR_NOK;
	}
	else if(LCD_NEXT_STATE == SEND_STRING_PENDING || LCD_NEXT_STATE == IDLE)
	{
		LCD_SEND_STRING_STATE = RUNNING;
		LCD_NEXT_STATE = SEND_STRING_PENDING;
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
		LCD_SENDING_CHAR = FALSE;
	}

	return LCD_STATUS_ERROR_OK;
}


void LcdDelayFinished(void)
{
	if(LCD_SET_CURSOR_STATE == RUNNING)
	{
		LCD_SET_CURSOR_STATE = IDLE;
	}
	else if(LCD_CLEAR_DISPLAY_STATE == RUNNING)
	{
		LCD_CLEAR_DISPLAY_STATE = IDLE;
	}
	else if(LCD_SEND_STRING_STATE == RUNNING)
	{
		LCD_SENDING_CHAR = FALSE;
	}
}
#endif