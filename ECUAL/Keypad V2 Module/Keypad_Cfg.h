/*****************************************************************************
* Module: Keypad Module
* File Name: Keypad_Cfg.h
* Description: Header file for Keypad Module
* Author: Mohamed Magdy
* Date: 24-July-2021
******************************************************************************/

#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

#include "Keypad.h"

#define ROWS_NUM				3
#define COLS_NUM				3


									
#define COLUMN_1_DIO_ID				DIO_COL_1_CHANNEL_ID
#define COLUMN_2_DIO_ID				DIO_COL_2_CHANNEL_ID
#define COLUMN_3_DIO_ID				DIO_COL_3_CHANNEL_ID


#define ROW_1_DIO_ID				DIO_ROW_1_CHANNEL_ID
#define ROW_2_DIO_ID				DIO_ROW_2_CHANNEL_ID
#define ROW_3_DIO_ID				DIO_ROW_3_CHANNEL_ID
//#define ROW_4_DIO_ID				DIO_ROW_4_CHANNEL_ID


#define COLUMN_1_BUTTON_ID			BUTTON_1_ID
#define COLUMN_2_BUTTON_ID			BUTTON_2_ID
#define COLUMN_3_BUTTON_ID			BUTTON_3_ID

#define DEBOUNCE_DELAY_MS			(50U)

#endif /* KEYPAD_CFG_H_ */