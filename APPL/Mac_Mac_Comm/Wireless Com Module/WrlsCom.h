/*
 * WrlsCom.h
 *
 * Created: 9/8/2021 1:58:48 PM
 *  Author: Ahmed Nabil
 */ 


#ifndef WRLSCOM_H_
#define WRLSCOM_H_


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "ECUAL/Bluetooth Module/Bluetooth.h"
#include "WrlsCom_LCfg.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/

#define WRLSCOM_STATE_UNINIT				0U
#define WRLSCOM_STATE_MALFUNCTION			1U
#define WRLSCOM_STATE_DEVICE_SEARCH			2U
#define WRLSCOM_STATE_IDLE					3U
#define WRLSCOM_STATE_VERIFICATION			4U
#define WRLSCOM_STATE_CONNECTED				5U

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*-*-*-*-*- Data Types -*-*-*-*-*-*-*-*-*/

typedef struct
{
	uint32_t Device_BaudRate; 
	uint8_t Device_Role;
	uint8_t Device_Name[WRLS_COM_MAX_NAME_SIZE];
	uint8_t Device_Pswrd[WRLS_COM_MAX_PSWRD_SIZE];
}WrlsCom_Config;


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*-*-*-*-*- FUNCTIONS PROTOTYPES -*-*-*-*-*-*-*-*-*/

Std_ReturnType WrlsCom_init(void);

Std_ReturnType WrlsCom_mainFunction(void);

Std_ReturnType WrlsCom_getState(uint8_t *DeviceState);


extern const WrlsCom_Config WrlsCom_BlthDevice_constConfig;

#endif /* WRLSCOM_H_ */