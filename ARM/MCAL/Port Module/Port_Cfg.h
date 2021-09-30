	/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Header file for Port Configuration Module.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/


#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)


#define PORT_DEV_ERROR_DETECT				  STD_OFF
#define PORT_SET_PIN_MODE_API				  STD_ON
#define PORT_SET_PIN_DIRECTION_API			  STD_ON
#define PORT_VERSION_INFO_API				  STD_OFF

#define PORT_PIN_CONFIGURED					  (42U)

#endif /* PORT_CFG_H_ */
