 /******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt.h
 *
 * Description: Header file for Gpt Module.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/


#ifndef GPT_H_
#define GPT_H_


/* Id for the company in the AUTOSAR
 * for example Ahmed Nabil's ID = 2910 */
#define GPT_VENDOR_ID		(2910U)

/* GPT Module ID */
#define GPT_MODULE_ID		(100U)

/* GPT Instance ID */
#define GPT_INSTANCE_ID		(0U)

/*
 * Module Version 1.0.0
 */
#define GPT_SW_MAJOR_VERSION           (1U)
#define GPT_SW_MINOR_VERSION           (0U)
#define GPT_SW_PATCH_VERSION           (0U)

/*
 * AutoSAR Version 4.0.3
 */
#define GPT_AR_RELEASE_MAJOR_VERSION   (4U)
#define GPT_AR_RELEASE_MINOR_VERSION   (0U)
#define GPT_AR_RELEASE_PATCH_VERSION   (3U)

#define GPT_INIT			(1U)
#define GPT_UNINIT			(0U)

/* Standard Types */
#include "Std_Types.h"
/* AUTOSAR checking between Std Types and GPT Modules */
//#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
//||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
//||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
//#error "The AR version of Std_Types.h does not match the expected version"
//#endif

/* GPT Pre-Compile Configuration Header file */
#include "Gpt_Cfg.h"

/* AUTOSAR Version checking between GPT_Cfg.h and Dio.h files */
#if ((GPT_CFG_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
||  (GPT_CFG_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
||  (GPT_CFG_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Dio_Cfg.h and Dio.h files */
#if ((GPT_CFG_SW_MAJOR_VERSION != GPT_SW_MAJOR_VERSION)\
||  (GPT_CFG_SW_MINOR_VERSION != GPT_SW_MINOR_VERSION)\
||  (GPT_CFG_SW_PATCH_VERSION != GPT_SW_PATCH_VERSION))
#error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Including non AutoSAR files */
#include "Common_Macros.h"
//#include "Gpt_Symbols.h"
//#include "Gpt_Irq.h"

/******************************************************************************
 *                        API Service Id Macros                               *
 ******************************************************************************/
/* Service ID for Gpt_GetVersionInfo API */
#define GPT_GET_VERSION_INFO_SID				(uint8)0x00

/* Service ID for Gpt_Init API */
#define GPT_INIT_SID							(uint8)0x01

/* Service ID for Gpt_DeInit API */
#define GPT_DEINIT_SID							(uint8)0x02

/* Service ID for Gpt_GetTimeElapsed API */
#define GPT_GET_TIME_ELAPSED_SID				(uint8)0x03

/* Service ID for Gpt_GetTimeRemaining API */
#define GPT_GET_TIME_REMAINING_SID				(uint8)0x04

/* Service ID for Gpt_StartTimer API */
#define GPT_START_TIMER_SID						(uint8)0x05

/* Service ID for Gpt_StopTimer API */
#define GPT_STOP_TIMER_SID						(uint8)0x06

/* Service ID for Gpt_EnableNotification API */
#define GPT_ENABLE_NOTIFICATION_SID				(uint8)0x07

/* Service ID for Gpt_DisableNotification API */
#define GPT_DISABLE_NOTIFICATION_SID			(uint8)0x08

/* Service ID for Gpt_SetMode API */
#define GPT_SET_MODE_SID						(uint8)0x09

/* Service ID for Gpt_DisableWakeup API */
#define GPT_DISABLE_WAKEUP_SID					(uint8)0x0A

/* Service ID for Gpt_EnableWakeup API */
#define GPT_ENABLE_WAKEUP_SID					(uint8)0x0B

/* Service ID for Gpt_CheckWakeup API */
#define GPT_CHECK_WAKEUP_SID					(uint8)0x0C

/*******************************************************************************
 *                          DET Error Codes                                    *
 *******************************************************************************/
/* DET code for calling API service when module is uninitialized */
#define GPT_E_UNINIT							(uint8)0x0A

/* DET code for calling API servide when timer channel is still busy */
#define GPT_E_BUSY								(uint8)0x0B

/* DET code for calling API servide when timer channel is stopped */
#define GPT_E_STOPPED							(uint8)0x0C

/* DET code for calling Gpt_Init while the timer has already been initialized before*/
#define GPT_E_ALREADY_INITIALIZED				(uint8)0x0D

/* DET code for calling API servide when timer channel is expired */
#define GPT_E_EXPIRED							(uint8)0x0E

/* DET code for passing an invalid channel as a parameter to an API */
#define GPT_E_PARAM_CHANNEL						(uint8)0x14

/* DET code for passing an invalid target value as a parameter to an API */
#define GPT_E_PARAM_VALUE						(uint8)0x15

/* DET code for passing a NULL pointer as a parameter to Gpt_Init */
#define GPT_E_PARAM_POINTER						(uint8)0x16

/* DET code for passing an invalid mode as a parameter to an API */
#define GPT_E_PARAM_MODE						(uint8)0x1F

/* DET code for passing an invalid mode as a parameter to an API */
#define GPT_E_PARAM_WIDTH                       (uint8)0x2F

/*******************************************************************************
 *                          Module Data Types                                  *
 *******************************************************************************/

/*
 * Data Type for Port initialization state
 */
typedef enum
{
	Gpt_Uninitialized = 0,
	Gpt_Initialized,
	Gpt_Running,
	Gpt_Stopped,
	Gpt_Expired
}Gpt_StateType;

/*
 * Data Type for Notification State for a channel
 */
typedef enum
{
	Gpt_Notification_Disabled = 0,
	Gpt_Notification_Enabled
}Gpt_NotificationStateType;

/*
 * Data Type for a pointer to notification call back function
 * Parameter (In) : None
 * Parameter (Out): None
 * Return Values : None
 */
typedef void (*Gpt_Notification)(void);

/* 
 * Data Type for the timer value (in number of ticks) 
 */
typedef uint64 Gpt_ValueType;

/*
 * Data Type for the numeric ID for a GPT Channel 
 */
typedef uint8 Gpt_ChannelType;

/* 
 * Data Type for the Counter Width
 */
typedef uint16 Gpt_CounterWidthType;

/*
 * Data Type for the prescaler state
 */
typedef enum
{
    GPT_PRESCALER_OFF=0,
    GPT_PRESCALER_8BITS,
    GPT_PRESCALER_16BITS
}Gpt_PrescalerStateType;

/* 
 * Data Type for the power modes of the timer 
 */
typedef enum
{
	GPT_MODE_NORMAL = 0,
	GPT_MODE_SLEEP
}Gpt_ModeType;

typedef enum
{
	GPT_CH_MODE_ONESHOT=1,
	GPT_CH_MODE_CONTINUOUS
}Gpt_ChannelModeType;
/*
 * Data Type for configurations of a timer's channel
 * Member 1. The timer channel's id in the mcu
 * Member 2. The clock source and prescaler selection
 */
typedef struct
{
	Gpt_ChannelType Timer_Id;
	Gpt_CounterWidthType Timer_Width;
	Gpt_ChannelModeType	RunMode;
	Gpt_Notification notification_func_ptr;
}Gpt_ChannelConfigType;

typedef struct
{
	Gpt_ChannelConfigType Timer_Channels[GPT_CONFIGURED_CHANNELS];
}Gpt_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Returns the version information of the Gpt module */
#if (GPT_VERSION_INFO_API == STD_ON)
void Gpt_GetVersionInfo( Std_VersionInfoType* VersionInfoPtr );
#endif

/* Initializes hardware timer modules configured in PBCfg.c */
void Gpt_Init( const Gpt_ConfigType* ConfigPtr );

/* DeInitializes all hardware timer modules configured in PBCfg.c */
#if (GPT_DEINIT_API == STD_ON)
void Gpt_DeInit( void );
#endif

/* Returns the elapsed time from the current period */
#if (GPT_TIME_ELAPSED_API == STD_ON)
Gpt_ValueType Gpt_GetTimeElapsed( Gpt_ChannelType Channel );
#endif

/* Returns the remaining time until the target time is reached */
#if (GPT_TIME_REAMAINING_API == STD_ON)
Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType Channel );
#endif

/* Make this timer channel starts counting */
void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value );

/* Stop this timer channel from counting */
void Gpt_StopTimer( Gpt_ChannelType Channel );

/* Enables the interrupt notification for a channel (relevant in normal mode) */
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
void Gpt_EnableNotification( Gpt_ChannelType Channel );

/* Disables the interrupt notification for a channel (relevant in normal mode) */
void Gpt_DisableNotification( Gpt_ChannelType Channel );
#endif

/* Sets the operation mode of the GPT (NORMAL or SLEEP) */
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
void Gpt_SetMode( Gpt_ModeType Mode );

/* Disables the wakeup interrupt of a channel (relevant in sleep mode) */
void Gpt_DisableWakeup( Gpt_ChannelType Channel );

/* Enables the wakeup interrupt of a channel (relevant in sleep mode) */
void Gpt_EnableWakeup( Gpt_ChannelType Channel );
/*
 * Checks if a wakeup capable GPT channel is the source for a wakeup event
 * and calls the ECU state manager service EcuM_SetWakeupEvent 
 * in case of a valid GPT channel wakeup event
 */
#ifdef ECUM_H_
void Gpt_CheckWakeup( EcuM_WakeupSourceType WakeupSource );
#endif
#endif
#endif

/* Changes the state of the timer channel */
void Gpt_StateChange(Gpt_ChannelType Channel, Gpt_StateType State);
/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
extern const Gpt_ConfigType Timers_Configurations ;

/*******************************************************************************
 *                                 MACROS                                      *
 *******************************************************************************/

#define GPT_MAX_VALUE_16BIT		(Gpt_ValueType)0xFFFF
#define GPT_MAX_VALUE_24BIT     (Gpt_ValueType)0xFFFFFF
#define GPT_MAX_VALUE_32BIT		(Gpt_ValueType)0xFFFFFFFF
#define GPT_MAX_VALUE_48BIT     (Gpt_ValueType)0xFFFFFFFFFFFF
#define GPT_MAX_VALUE_64BIT     (Gpt_ValueType)0xFFFFFFFFFFFFFFFF

#endif
