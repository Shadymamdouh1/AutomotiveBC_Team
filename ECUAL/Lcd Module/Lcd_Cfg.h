/*****************************************************************************
* Module: Lcd Module
* File Name: Lcd_Cfg.h
* Description: Header file for Lcd Module
* Author: Mohamed Magdy
* Date: 24-July-2021
******************************************************************************/

#ifndef LCD_CFG_H_
#define LCD_CFG_H_

 /* Async Cfg */
#define AsyncMode			TRUE
#define	DelayTicks			325
#define TIMER_USED_ID		TIMER_0
/*********************************************/
#define Lcd_Rows			2
#define Lcd_Columns			16

#define RS_DIO_ID			PORTA_PIN1_ID	
#define RW_DIO_ID			PORTA_PIN2_ID	
#define EN_DIO_ID			PORTA_PIN3_ID
								
#define D4_DIO_ID			PORTA_PIN4_ID
#define D5_DIO_ID			PORTA_PIN5_ID
#define D6_DIO_ID			PORTA_PIN6_ID
#define D7_DIO_ID			PORTA_PIN7_ID

#endif /* LCD_CFG_H_ */