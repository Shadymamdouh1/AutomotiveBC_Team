/*
 * Bluetooth_Cfg.h
 *
 * Created: 9/8/2021 1:58:59 PM
 *  Author: Ahmed Nabil
 */ 


#ifndef BLUETOOTH_CFG_H_
#define BLUETOOTH_CFG_H_


/*
 * ROLE of the bluetooth device
 * @Options: BLTH_ROLE_MASTER or BLTH_ROLE_SLAVE
 */

#define BLTH_ROLE_MODE			BLTH_ROLE_MASTER


#define BLTH_ENABLE_PIN			DIO_PORTD2_CHANNEL_ID


#define BLTH_UART_CHANNEL		UART_CHANNEL_0

#define BLTH_BUFFER_SIZE		50U

#endif /* BLUETOOTH_CFG_H_ */