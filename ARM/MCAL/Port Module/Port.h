 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for Port Module.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example Ahmed Nabil's ID = 2910 */
#define PORT_VENDOR_ID		(2910U)

/* Port Module ID */
#define PORT_MODULE_ID		(124U)

/* Port Instance ID */
#define PORT_INSTANCE_ID	 (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AutoSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

#define PORT_INIT			(1U)
#define PORT_UNINIT			(0U)

/* Standard Types */
#include "Std_Types.h"
///* AUTOSAR checking between Std Types and Port Modules */
//#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
//||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
//||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
//#error "The AR version of Std_Types.h does not match the expected version"
//#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Dio.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Dio_Cfg.h and Dio.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Including non AutoSAR files */
#include "Common_Macros.h"
#include "Port_Symbols.h"
#include "Port_Regs.h"

#define PORT_NUM		(6U)
#define PORT_PIN_NUM	(8U)

#define PULL_UP			STD_HIGH
#define PULL_DOWN		STD_LOW
#define PULL_NONE       0x0A

#define PORT_PIN_DIRECTION_CHANGEABLE		TRUE
#define PORT_PIN_DIRECTION_UNCHANGEABLE     FALSE

#define PORT_PIN_MODE_CHANGEABLE			TRUE
#define PORT_PIN_MODE_UNCHANGEABLE    		FALSE


/******************************************************************************
 *                        API Service Id Macros                               *
 ******************************************************************************/
/* Service ID for Port_Init API */
#define PORT_INIT_SID						(uint8)0x00

/* Service ID for Port_SetPinDirection API */
#define PORT_SET_PIN_DIR_SID				(uint8)0x01

/* Service ID for Port_RefreshPortDirection API */
#define PORT_REFRESH_PORT_DIR_SID			(uint8)0x02

/* Service ID for Port_GetVersionInfo API */
#define PORT_GET_VERSION_INFO_SID			(uint8)0X03

/* Service ID for Port_SetPinMode API */
#define PORT_SET_PIN_MODE_SID				(uint8)0x04

/*******************************************************************************
 *                          DET Error Codes                                    *
 *******************************************************************************/
/* DET code for Invalid Port Pin ID passed */
#define PORT_E_PARAM_PIN					(uint8)0x0A

/* DET code for Port Pin not configured as Changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE		(uint8)0x0B

/* DET code for Port_Init is called with wrong parameter */
#define PORT_E_PARAM_CONFIG					(uint8)0x0C

/* DET code for Port_SetPinMode is called with invalid mode */
#define PORT_E_PARAM_INVALID_MODE			(uint8)0x0D

/* DET code for Port_SetPinMode is called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE			(uint8)0x0E

/* DET code for calling any API service when module is uninitialized */
#define PORT_E_UNINIT				    	(uint8)0x0F

/* DET code for calling an API with a NULL_PTR */
#define PORT_E_PARAM_POINTER				(uint8)0x10

/*******************************************************************************
 *                          Module Data Types                                  *
 *******************************************************************************/

/* 
 * Data Type for the symbolic name of a Port
 */
typedef uint8 Port_PortType;

/*
 * Data Type for Port initialization state
 */
typedef enum
{
	Port_Uninitialized = 0,
	Port_Initialized
}Port_InitState;

/* 
 * Data Type for the symbolic name of a Port Pin
 */
typedef uint8 Port_PinType;

/*
 * Data Type for possible directions of Port Pin
 * PORT_PIN_IN >> Input = 0
 * PORT_PIN_OUT >> Output = 1
 */
typedef enum
{
	PORT_PIN_IN = 0,
	PORT_PIN_OUT
}Port_PinDirectionType;

/*
 * Data Type for different Port Pin Modes
 * Mode of the pin: GPIO, SPI, CAN,...
 */
typedef uint8 Port_PinModeType;

/*
 * Data Type for the initial logic level for the pin
 * Can be used for the two directions
 * Output: STD_HIGH or STD_LOW to determine the initial level for an output pin
 * Input: PULL_UP or PULL_DOWN for the internal resistor connection for an input pin
 */
typedef uint8 Port_PinInitLevel;

/*
 * Data Type for the Port Pin Digital State 
 * PORT_PIN_DIGITAL_ENABLE or PORT_PIN_DIGITAL_DISABLE
 */
typedef enum
{ 
	PORT_PIN_DIGITAL_DISABLE = 0,
	PORT_PIN_DIGITAL_ENABLE
}Port_PinDigitalType;


/*
 * Data Type for the Port Pin Drive Current
 * PORT_PIN_CURRENT_2mA or 
 * PORT_PIN_CURRENT_4mA or
 * PORT_PIN_CURRENT_8mA
 */
typedef enum
{
	PORT_PIN_CURRENT_2mA = 0,
	PORT_PIN_CURRENT_4mA,
	PORT_PIN_CURRENT_8mA
}Port_PinDriveCurrentType;

/*
 * Data Type for Port Pin Open Drain
 * ENABLE or DISABLE
 */
typedef enum
{
	PORT_OPENDRAIN_DISABLE = 0,
	PORT_OPENDRAIN_ENABLE
}Port_PinOpenDrainType;



/*
 * Data Type for Port Pin Slew Rate
 * ENABLE or DISABLE
 */
typedef enum
{
	PORT_SLEWRATE_DISABLE = 0,
	PORT_SLEWRATE_ENABLE
}Port_PinSlewRateType;


/*
 * Data Type for Port Pin AMSEL
 * ENABLE or DISABLE
 */
typedef enum
{
	PORT_AMSEL_DISABLE = 0,
	PORT_AMSEL_ENABLE
}Port_PinAMSELType;


/* 
 *  Description: Structure to describe each individual PIN contains:
 *	1. the number of the pin in the PORT.
 *  2. the direction of pin --> INPUT or OUTPUT
 *  3. is the direction of this pin changeable ?
 *  4. the initial level of the pin in output direction (STD_HIGH or STD_LOW)
 *     the internal resistor connection in input direction (PULL_UP or PULL_DOWN)
 *	5. the operation mode of the pin (GPIO, CAN, SPI,...)
 *	6. is the mode of the pin changeable? 
 *	7. is the pin operated for digital signal?
 *	8. the drive current of the pin (2mA,4mA,8mA)
 *	9. is the pin operated as open drain?
 *	10.is the pin operated in slew rate mode?
 *	11.is the pin operated in AMSEL mode?
 */
typedef struct 
{
	Port_PinType			 	pin_id; 
	Port_PinDirectionType   	direction;
	boolean					    pin_dir_changeable;
	Port_PinInitLevel		    initial_lvl;
	Port_PinModeType        	pin_mode;
	boolean					 	pin_mode_changeable;
	Port_PinDigitalType      	pin_digital_enable;
	Port_PinDriveCurrentType 	pin_current_value;
	Port_PinOpenDrainType    	pin_open_drain;
	Port_PinSlewRateType     	pin_slew_rate;
	Port_PinAMSELType        	pin_AMSEL;
}Port_PinConfig;

typedef struct
{
	Port_PinConfig pin_config[PORT_PIN_CONFIGURED];	
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Initialize all pins in all ports of the Target */
void Port_Init(const Port_ConfigType* ConfigPtr);

/* Configure the PIN to input or output pin */
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin, 
					   Port_PinDirectionType Direction);
#endif

/* Refreshes the direction of the port */
void Port_RefreshPortDirection(void);

/* Returns the version information of the port module */
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

/* Sets the port pin mode */
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin,
					 Port_PinModeType Mode);
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_PinsConfigurations;

/*******************************************************************************
 *                                 MACROS                                      *
 *******************************************************************************/
#define getPORT_NUM(PIN_ID)  (Port_PortType)(PIN_ID/10)
#define getPIN_NUM(PIN_ID)	 (Port_PinType)(PIN_ID%10)

#endif /* PORT_H */
