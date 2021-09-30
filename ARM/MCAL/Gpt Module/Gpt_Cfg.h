 /******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt_Cfg.h
 *
 * Description: Header file for Gpt Module Configurations.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/


#ifndef GPT_CFG_H_
#define GPT_CFG_H_

/*
 * Module Version 1.0.0
 */
#define GPT_CFG_SW_MAJOR_VERSION              (1U)
#define GPT_CFG_SW_MINOR_VERSION              (0U)
#define GPT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define GPT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define GPT_CFG_AR_RELEASE_PATCH_VERSION     (3U)


#define GPT_DEV_ERROR_DETECT				  STD_OFF
#define GPT_STALL_DEBUGGER                    STD_ON
#define GPT_VERSION_INFO_API				  STD_OFF
#define GPT_DEINIT_API						  STD_ON
#define GPT_TIME_ELAPSED_API				  STD_ON
#define GPT_TIME_REAMAINING_API				  STD_ON
#define GPT_ENABLE_DISABLE_NOTIFICATION_API   STD_ON
#define GPT_WAKEUP_FUNCTIONALITY_API		  STD_OFF
#define GPT_REPORT_WAKEUP_SOURCE			  STD_OFF

#define GPT_CONFIGURED_CHANNELS				 (4U)

#define GPT_TIMER0A_CHANNEL_ID				 (0U)
#define GPT_WTIMER5B_CHANNEL_ID              (1U)
#define GPT_TIMER5AB_CHANNEL_ID              (2U)
#define GPT_WTIMER4AB_CHANNEL_ID             (3U)
#endif


