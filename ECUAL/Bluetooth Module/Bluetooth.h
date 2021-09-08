/*
 * Bluetooth.h
 *
 * Created: 9/8/2021 1:58:48 PM
 *  Author: Ahmed Nabil
 */ 


#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "MCAL\Uart Module\Uart.h"
#include "MCAL\Dio Module\Dio.h"
#include "Bluetooth_Cfg.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/

#define BLTH_ROLE_SLAVE			0U
#define BLTH_ROLE_MASTER		1U


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*-*-*-*-*- Data Types -*-*-*-*-*-*-*-*-*/



/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*-*-*-*-*- FUNCTIONS PROTOTYPES -*-*-*-*-*-*-*-*-*/

Std_ReturnType Blth_init(void);

Std_ReturnType Blth_sendData(uint8_t *DataPtr, uint16_t DataSize);

Std_ReturnType Blth_readData(uint8_t *DataPtr);

Std_ReturnType Blth_sendCommand(uint8_t* CommandPtr, uint16_t CommandSize);

Std_ReturnType Blth_RenameDevice(uint8_t *newName);

Std_ReturnType Blth_setSlave(void);

Std_ReturnType Blth_setMaster(void);

Std_ReturnType Blth_setBaudRate(uint32_t newBaudRate);

Std_ReturnType Blth_getBaudRate(uint32_t *currentBaudRate);

Std_ReturnType Blth_testDevice(void);

Std_ReturnType Blth_getOwnMacAddress(uint8_t *ownMacAddress);

Std_ReturnType Blth_pairDevice(uint8_t *ownMacAddress);

Std_ReturnType Blth_setPassword(uint8_t *ownPassword);







#endif /* BLUETOOTH_H_ */