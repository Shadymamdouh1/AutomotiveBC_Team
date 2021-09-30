 /******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt_PBCfg.c
 *
 * Description: Source file for Gpt Module Post Build Configurations.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/
 
#include "Gpt.h"
#include "Gpt_Symbols.h"

/*
 * Module Version 1.0.0
 */
#define GPT_PBCFG_SW_MAJOR_VERSION              (1U)
#define GPT_PBCFG_SW_MINOR_VERSION              (0U)
#define GPT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define GPT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define GPT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between GPT_PBcfg.c and GPT.h files */
#if ((GPT_PBCFG_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||  (GPT_PBCFG_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (GPT_PBCFG_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the AR version of GPT.h"
#endif

/* Software Version checking between GPT_PBcfg.c and GPT.h files */
#if ((GPT_PBCFG_SW_MAJOR_VERSION != GPT_SW_MAJOR_VERSION)\
 ||  (GPT_PBCFG_SW_MINOR_VERSION != GPT_SW_MINOR_VERSION)\
 ||  (GPT_PBCFG_SW_PATCH_VERSION != GPT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the SW version of GPT.h"
#endif

extern void Gpt_Notification_CH_0(void);

/* PB structure used with GPT_Init API */
const Gpt_ConfigType Timers_Configurations =
{
	{
	{GPT_TIMER_0_A, GPT_WIDTH_TIM_A_24BITS,GPT_CH_MODE_CONTINUOUS,NULL_PTR},
	{GPT_WTIMER_5_B, GPT_WIDTH_WTIM_B_32BITS,GPT_CH_MODE_CONTINUOUS,&Gpt_Notification_CH_0},
	{GPT_TIMER_5_AB, GPT_WIDTH_TIM_AB_32BITS,GPT_CH_MODE_CONTINUOUS,NULL_PTR},
	{GPT_WTIMER_4_AB, GPT_WIDTH_WTIM_AB_64BITS,GPT_CH_MODE_CONTINUOUS,NULL_PTR}
	}
};








