 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio_PBcfg.c
 *
 * Description: Post Build Configuration Source file for Dio Module.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/

#include "Dio.h"

/*
 * Module Version 1.0.0
 */
#define DIO_PBCFG_SW_MAJOR_VERSION              (1U)
#define DIO_PBCFG_SW_MINOR_VERSION              (0U)
#define DIO_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define DIO_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define DIO_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Dio_PBcfg.c and Dio.h files */
#if ((DIO_PBCFG_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 ||  (DIO_PBCFG_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 ||  (DIO_PBCFG_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Dio_PBcfg.c and Dio.h files */
#if ((DIO_PBCFG_SW_MAJOR_VERSION != DIO_SW_MAJOR_VERSION)\
 ||  (DIO_PBCFG_SW_MINOR_VERSION != DIO_SW_MINOR_VERSION)\
 ||  (DIO_PBCFG_SW_PATCH_VERSION != DIO_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif


/* PB structure used with Dio_Init API */
const Dio_ConfigType Dio_Configuration =
                                   {
									{
                                    {DioConf_RED_PORT_NUM,DioConf_RED_CHANNEL_NUM},
									{DioConf_BLUE_PORT_NUM,DioConf_BLUE_CHANNEL_NUM},
									{DioConf_GREEN_PORT_NUM,DioConf_GREEN_CHANNEL_NUM},
									{DioConf_BUTTON1_PORT_NUM, DioConf_BUTTON1_CHANNEL_NUM},
									{DioConf_BUTTON2_PORT_NUM, DioConf_BUTTON2_CHANNEL_NUM}
									},
									{
									{(0x7<<1),DIO_CHANNEL_F_1,DIO_PORT_F},
									{(0x11),DIO_CHANNEL_F_0,DIO_PORT_F}
									}
								   };
