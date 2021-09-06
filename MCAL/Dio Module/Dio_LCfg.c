/*
 * Dio_Cfg.c
 *
 * Created: 7/13/2021 7:55:09 PM
 *  Author: Ahmed Nabil
 */ 

#include "Dio_LCfg.h"
#include "Dio.h"

strDio_Config_t strDio_pins[DIO_USED_PINS_NUM]=
{
	{DioConf_BTN_1_PORT_NUM, DioConf_BTN_1_PIN_NUM, DIO_PIN_DIR_INPUT, PIN_PUR},
	{DioConf_BTN_2_PORT_NUM, DioConf_BTN_2_PIN_NUM, DIO_PIN_DIR_INPUT, PIN_PUR},
	{DioConf_LED_1_PORT_NUM, DioConf_LED_1_PIN_NUM, DIO_PIN_DIR_OUTPUT, PIN_LOW},
	{DioConf_LED_2_PORT_NUM, DioConf_LED_2_PIN_NUM, DIO_PIN_DIR_OUTPUT, PIN_LOW}
};

