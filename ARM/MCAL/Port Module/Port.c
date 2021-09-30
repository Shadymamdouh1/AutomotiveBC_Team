 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for Port Module.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"

/* AUTOSAR checking between Std Types and Dio Modules */
#if (PORT_DEV_ERROR_DETECT == STD_ON)
//#include "Det.h"
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||	 (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
	#error "The AR version of Det.h does not match the AR version of Port.h"
#endif

#endif

STATIC Port_PinConfig* PinConfig_Ptr = NULL_PTR;
volatile STATIC Port_InitState Port_state = Port_Uninitialized;

/*******************************************************************************
 *                      Function Definitions                                   *
 *******************************************************************************/

/************************************************************************************
* Service Name: setPCTL
* Service ID[hex]: Non AutoSAR function
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): port - the port id
*                  pin  - index of the pin in the port
*                  mode - the alternate functionality needed (CAN, SPI, ..)
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set the pin to the required mode of operation if it's set to AFSEL
************************************************************************************/
STATIC void setPCTL(Port_PortType port, Port_PinType pin, Port_PinModeType mode)
{

}

/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Port module.
************************************************************************************/
void Port_Init(const Port_ConfigType* ConfigPtr)
{
	uint8 config_index = 0;
	boolean error = FALSE;
	Port_PortType port;
	Port_PinType pin;

    /**************************************************************************************/
    /*                              Start of Error Checking                               */
    /**************************************************************************************/
/* 
 * Error Detection and reporting to Det Module is enabled by 
 * assigning STD_ON to PORT_DEV_ERROR_DETECT in Port_Cfg.h 
 */
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the input parameter is NULL */
	if (NULL_PTR == ConfigPtr)
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_POINTER);
		error = TRUE;
	}else{/*Nothing to here*/}
		
#endif	
    /**************************************************************************************/
    /*                              End of Error Checking                                 */
    /**************************************************************************************/

    /**************************************************************************************/
    /*                              Function Implementation                               */
    /**************************************************************************************/
	if(FALSE == error)
	{
		for(config_index=0;config_index<PORT_PIN_CONFIGURED;config_index++)
		{
	        /* Point to the Configuration Struct in Port_PBCfg.c */
	        PinConfig_Ptr = (Port_PinConfig*) ConfigPtr->pin_config;

			pin = getPIN_NUM(PinConfig_Ptr[config_index].pin_id);
			port = getPORT_NUM(PinConfig_Ptr[config_index].pin_id);
			
			/*******************************************/
			/*     This Partition should be in MCU     */
			 /* Set the clock for the appropriate Port */
            RCGCGPIO_REG |= 1<<port;
             /* Enter the unlock value for the Port */
            PORT(port)->LOCK = GPIO_PORT_UNLOCK_VALUE;
            /* Set the Committed bit for the appropriate Port Pin */
            PORT(port)->CR |= 1<<pin;
            /*******************************************/
            PORT(port)->AFSEL &= ~(1<<pin);
            PORT(port)->PCTL &= ~(1<<(4*pin));
            /* Set the direction of the pin */
			PORT(port)->DIR &= ~(1<<pin);
			PORT(port)->DIR |= ((PinConfig_Ptr[config_index].direction)<<pin);


            /* Set the Current Drive value for the pin */
            switch(PinConfig_Ptr[config_index].pin_current_value)
            {
            case PORT_PIN_CURRENT_2mA:
                PORT(port)->DR2R |= 1<<pin;
                break;
            case PORT_PIN_CURRENT_4mA:
                PORT(port)->DR4R |= 1<<pin;
                break;
            case PORT_PIN_CURRENT_8mA:
                PORT(port)->DR8R |= 1<<pin;
                break;
            default:
                break;
            }

            /* Enable or disable open drain functionality for the pin */
            PORT(port)->ODR &= ~(1<<pin);
            PORT(port)->ODR |= ((PinConfig_Ptr[config_index].pin_open_drain)<<pin);

            /* Set the Digital or Analog operation for the pin */
            PORT(port)->DEN &= ~(1<<pin);
            PORT(port)->DEN |= ((PinConfig_Ptr[config_index].pin_digital_enable)<<pin);

            /* Enable or disable AMSEL functionality for the pin */
            PORT(port)->AMSEL &= ~(1<<pin);
            PORT(port)->AMSEL |= ((PinConfig_Ptr[config_index].pin_AMSEL)<<pin);

            /* Enable or disable SlewRate functionality for the pin */
            PORT(port)->SLR &= ~(1<<pin);
            PORT(port)->SLR |= ((PinConfig_Ptr[config_index].pin_slew_rate)<<pin);

            /* Set the Port Control Register according to the mode of the pin */
            if(PORT_PIN_MODE_DIO != (PinConfig_Ptr[config_index].pin_mode))
            {
                PORT(port)->AFSEL |= (1<<pin);
                PORT(port)->PCTL |= ((PinConfig_Ptr[config_index].pin_mode)<<pin*4);
//                setPCTL(port, pin, PinConfig_Ptr[config_index].pin_mode);
                if(PULL_DOWN == PinConfig_Ptr[config_index].initial_lvl)
                {
                    PORT(port)->PDR |= (1<<pin);
                }else if(PULL_UP == PinConfig_Ptr[config_index].initial_lvl)
                {
                    PORT(port)->PUR |= (1<<pin);
                }else{ /* Nothing to do here */ }
            }else
            {
                /* This condition if the mode is set to DIO which is the default mode for the pin */
                PORT(port)->AFSEL &= ~(1<<pin);

                PORT(port)->DATA &= ~(1<<pin);
                /* Set the initial state of the pin
                 * if Pin is Output >> (STD_LOW or STD_HIGH)
                 * if Pin is Input >> (PULL_DOWN or PULL_UP)
                 */
                if(PORT_PIN_OUT == PinConfig_Ptr[config_index].direction)
                {
                    PORT(port)->DATA &= ~(1<<pin);
                    PORT(port)->DATA |= ((PinConfig_Ptr[config_index].initial_lvl)<<pin);
                }else if(PORT_PIN_IN == PinConfig_Ptr[config_index].direction)
                {
                    if(PULL_DOWN == PinConfig_Ptr[config_index].initial_lvl)
                    {
                        PORT(port)->PDR |= (1<<pin);
                    }else if(PULL_UP == PinConfig_Ptr[config_index].initial_lvl)
                    {
                        PORT(port)->PUR |= (1<<pin);
                    }else{ /* Nothing to do here */ }
                }else{ /* Nothing to do here */ }
            }
		}
		/* Update the Port status to initialized */
		Port_state = Port_Initialized;
	}else
	{
		/* Nothing to de here yet */
	}
	
}

/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin - Number of the Pin
*				   Direction - The direction of the pin needed to be set
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to change the direction of the pin in the runtime.
*			   This function only enabled when PORT_PIN_DIRECTION_CHANGEABLE in Port_Cfg.h is STD_ON
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin, 
					   Port_PinDirectionType Direction)
{
	boolean error = FALSE;
	Port_PortType port;
	Port_PinType pin;
/**************************************************************************************/
/*                              Start of Error Checking                               */
/**************************************************************************************/
/* 
 * Error Detection and reporting to Det Module is enabled by 
 * assigning STD_ON to PORT_DEV_ERROR_DETECT in Port_Cfg.h 
 */
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Port is not initialized before */
	if (Port_Uninitialized == Port_state)
	{
		/* Report uninitialized error to the Det Module */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID, PORT_E_UNINIT);
		error = TRUE;
	}else{/*Nothing to here*/}
		
	/* Check if the parameter Pin is out of range */
	if (PORT_PIN_CONFIGURED <= Pin)
	{
		/* Report configuration parameter error to the Det Module */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID, PORT_E_PARAM_CONFIG);
		error = TRUE;
	}else{/*Nothing to here*/}
		
	/* Check if the pin is direction unchangeable */
	if(PORT_PIN_DIRECTION_UNCHANGEABLE == (PinConfig_Ptr[Pin].pin_dir_changeable))
	{
		/* Report direction unchangeable error to the Det Module */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID, PORT_E_DIRECTION_UNCHANGEABLE);
		error = TRUE;
	}else{/*Nothing to here*/}
		
	/* Check if the Pin is invalid in the MCU */
	if(PORT_PIN_NUM <= (getPIN_NUM(PinConfig_Ptr[Pin].pin_id)))
	{
		/* Report Invalid Pin error to the Det Module */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID, PORT_E_PARAM_PIN);
		error = TRUE;
	}else{/*Nothing to here*/}
		
#endif	
/**************************************************************************************/
/*                              End of Error Checking                                 */
/**************************************************************************************/

/**************************************************************************************/
/*                              Function Implementation                               */
/**************************************************************************************/
	/* In case there are no errors */
	if (FALSE == error)
	{
        port = getPORT_NUM(Pin);
        pin = getPIN_NUM(Pin);
	    PORT(port)->DIR &= ~(1<<pin);
	    PORT(port)->DIR |= (Direction<<pin);
	}else
	{
		/* Nothing to do here yet */
	}
}
#endif

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to refresh the port's direction
************************************************************************************/
void Port_RefreshPortDirection(void)
{
	boolean error = FALSE;
	uint8 config_index = 0;
	Port_PortType port;
	Port_PinType pin;
/**************************************************************************************/
/*                              Start of Error Checking                               */
/**************************************************************************************/
/* 
 * Error Detection and reporting to Det Module is enabled by 
 * assigning STD_ON to PORT_DEV_ERROR_DETECT in Port_Cfg.h 
 */	
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Port is not initialized before */
	if (Port_Uninitialized == Port_state)
	{
		/* Report uninitialized error to the Det Module */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIR_SID, PORT_E_UNINIT);
		error = TRUE;
	}else
	{
		/* Nothing to do here */
	}
#endif
/**************************************************************************************/
/*                              End of Error Checking                                 */
/**************************************************************************************/

/**************************************************************************************/
/*                              Function Implementation                               */
/**************************************************************************************/
	/* In case there are no errors */
	if (FALSE == error)
	{
		for(config_index=0;config_index<PORT_PIN_CONFIGURED;config_index++)
		{
			port = getPORT_NUM(PinConfig_Ptr[config_index].pin_id);
			pin = getPIN_NUM(PinConfig_Ptr[config_index].pin_id);

			if(PORT_PIN_DIRECTION_UNCHANGEABLE == (PinConfig_Ptr[config_index].pin_dir_changeable))
			{
			    PORT(port)->DIR |= (PinConfig_Ptr[config_index].direction)<<pin;
			}else
			{
			    /* If the pin is direction changeable, no refresh for it */
			}
		}
	}else
	{
		/* Nothing to do here yet */
	}
}

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo - Structure type with the version's parameters (major, minor, patch)
* Return value: None
* Description: Function to return the version information of the port module
************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
	boolean error = FALSE;
/**************************************************************************************/
/*                              Start of Error Checking                               */
/**************************************************************************************/
/* 
 * Error Detection and reporting to Det Module is enabled by 
 * assigning STD_ON to PORT_DEV_ERROR_DETECT in Port_Cfg.h 
 */
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
		error = TRUE;
	}
#endif	
/**************************************************************************************/
/*                              End of Error Checking                                 */
/**************************************************************************************/

/**************************************************************************************/
/*                              Function Implementation                               */
/**************************************************************************************/
	if(FALSE == error)
	{
		/* Send the Port Module ID */
		versioninfo->moduleID         = (uint16)PORT_MODULE_ID;
		/* Send the Port Module Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Send the Port Module Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Send the Port Module Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
		/* Send the Port Module Vendor ID */
		versioninfo->vendorID		  = (uint16)PORT_VENDOR_ID;
	}else
	{
		/* Nothing to do here yet */
	}
}
#endif

/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin - Number of the Pin
*				   Mode - The mode of the pin needed to be set
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to change the mode of the pin in the runtime.
*			   This function only enabled when PORT_PIN_MODE_CHANGEABLE in Port_Cfg.h is STD_ON
************************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin,
					 Port_PinModeType Mode)
{
    boolean error = FALSE;
    Port_PortType port;
    Port_PinType pin;
/**************************************************************************************/
/*                              Start of Error Checking                               */
/**************************************************************************************/
/* 
 * Error Detection and reporting to Det Module is enabled by 
 * assigning STD_ON to PORT_DEV_ERROR_DETECT in Port_Cfg.h 
 */			
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Port is not initialized before */
	if (Port_Uninitialized == Port_state)
	{
		/* Report uninitialized error to the Det Module */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
		error = TRUE;
	}else{/*Nothing to here*/}
	
	/* Check if the parameter Pin is out of range */
	if (PORT_PIN_CONFIGURED <= Pin)
	{
		/* Report configuration parameter error to the Det Module */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_CONFIG);
		error = TRUE;
	}else{/*Nothing to here*/}
			
	/* Check if the Pin is invalid in the MCU */
	if(PORT_PIN_NUM <= (getPIN_NUM(PinConfig_Ptr[Pin].pin_id)))
	{
		/* Report Invalid Pin error to the Det Module */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
		error = TRUE;
	}else{/*Nothing to here*/}

    /* Check if the pin is mode unchangeable */
    if(PORT_PIN_MODE_UNCHANGEABLE == (PinConfig_Ptr[Pin].pin_mode_changeable))
    {
        /* Report direction unchangeable error to the Det Module */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
        error = TRUE;
    }else{/*Nothing to here*/}
				
#endif 
/**************************************************************************************/
/*                              End of Error Checking                                 */
/**************************************************************************************/

/**************************************************************************************/
/*                              Function Implementation                               */
/**************************************************************************************/
	if(FALSE == error)
	{
        port = getPORT_NUM(Pin);
        pin = getPIN_NUM(Pin);
	    if(PORT_PIN_MODE_DIO != Mode)
	    {
	        PORT(port)->AFSEL |= 1<<pin;
	        setPCTL(port, pin, Mode);
	    }else
	    {
	        /* This condition if the mode is set to DIO which is the default mode for the pin */
            PORT(port)->AFSEL &= ~(1<<pin);
	    }
	}else
	{
	    /* Nothing to do here yet */
	}
}
#endif


