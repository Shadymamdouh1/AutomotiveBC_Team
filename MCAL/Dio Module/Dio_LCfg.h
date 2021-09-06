/*
 * Dio_Cfg.h
 *
 * Created: 7/13/2021 7:54:56 PM
 *  Author: Ahmed Nabil
 */ 


#ifndef DIO_CFG_H_
#define DIO_CFG_H_

#include "Dio_Regs.h"

#define DIO_USED_PINS_NUM		4

/* DIO Configured Port ID's  */
#define DioConf_BTN_1_PORT_NUM				PORT_D
#define DioConf_BTN_2_PORT_NUM				PORT_A
#define DioConf_LED_1_PORT_NUM				PORT_C
#define DioConf_LED_2_PORT_NUM				PORT_A



/* DIO Configured Channel ID's */
#define DioConf_BTN_1_PIN_NUM				PIN_2
#define DioConf_BTN_2_PIN_NUM				PIN_0
#define DioConf_LED_1_PIN_NUM				PIN_3
#define DioConf_LED_2_PIN_NUM				PIN_6



/* Channel Index in the array of structures in Dio_Cfg.c */
#define DIO_BTN_1_CHANNEL_ID				0
#define DIO_BTN_2_CHANNEL_ID				1
#define DIO_LED_1_CHANNEL_ID				2
#define DIO_LED_2_CHANNEL_ID				3

#endif /* DIO_CFG_H_ */