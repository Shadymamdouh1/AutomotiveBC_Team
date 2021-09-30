 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio.c
 *
 * Description: Source file for Dio Module.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/

#include "Dio.h"
#include "Dio_Regs.h"

#if (DIO_DEV_ERROR_DETECT == STD_ON)

//#include "Det.h"
/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC Dio_ConfigType * Dio_Configuration_Ptr = NULL_PTR;
volatile STATIC uint8 Dio_Status = DIO_NOT_INITIALIZED;

/************************************************************************************
* Service Name: Dio_Init
* Service ID[hex]: 0x10
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Dio module.
************************************************************************************/
void Dio_Init(const Dio_ConfigType * ConfigPtr)
{
    /**************************************************************************************/
    /*                              Start of Error Checking                               */
    /**************************************************************************************/
#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_INIT_SID,
		     DIO_E_PARAM_CONFIG);
	}
	else
#endif
    /**************************************************************************************/
    /*                              End of Error Checking                                 */
    /**************************************************************************************/

    /**************************************************************************************/
    /*                              Function Implementation                               */
    /**************************************************************************************/
	{
		/*
		 * Set the module state to initialized and point to the PB configuration structure using a global pointer.
		 * This global pointer is global to be used by other functions to read the PB configuration structures
		 */
		Dio_Status       = DIO_INITIALIZED;
		Dio_Configuration_Ptr = (Dio_ConfigType *) &Dio_Configuration; /* Address of the first element of configuration struct in PBCfg.c*/
	}
}

/************************************************************************************
* Service Name: Dio_WriteChannel
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
*                  Level - Value to be written.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set a level of a channel.
************************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
	boolean error = FALSE;
	Dio_PortType port;
	Dio_ChannelType pin;
    /**************************************************************************************/
    /*                              Start of Error Checking                               */
    /**************************************************************************************/
#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_WRITE_CHANNEL_SID, DIO_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (DIO_CONFIGURED_CHANNLES <= ChannelId)
	{

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_WRITE_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
#endif
    /**************************************************************************************/
    /*                              End of Error Checking                                 */
    /**************************************************************************************/

    /**************************************************************************************/
    /*                              Function Implementation                               */
    /**************************************************************************************/
	/* In-case there are no errors */
	if(FALSE == error)
	{
	    port = Dio_Configuration_Ptr->Channels[ChannelId].Port_Num;
	    pin = Dio_Configuration_Ptr->Channels[ChannelId].Ch_Num;

	    DIO_PORT(port)->DATA &= ~(1<<pin);
	    DIO_PORT(port)->DATA |= (Level<<pin);
	}
	else
	{
		/* No Action Required */
	}

}

/************************************************************************************
* Service Name: Dio_ReadChannel
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_LevelType
* Description: Function to return the value of the specified DIO channel.
************************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    Dio_PortType port;
    Dio_ChannelType pin;
	boolean error = FALSE;
	Dio_LevelType pin_status = STD_LOW;
    /**************************************************************************************/
    /*                              Start of Error Checking                               */
    /**************************************************************************************/
#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
		DIO_READ_CHANNEL_SID, DIO_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (DIO_CONFIGURED_CHANNLES <= ChannelId)
	{

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
		DIO_READ_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
#endif
    /**************************************************************************************/
    /*                              End of Error Checking                                 */
    /**************************************************************************************/

    /**************************************************************************************/
    /*                              Function Implementation                               */
    /**************************************************************************************/
	/* In-case there are no errors */
	if(FALSE == error)
	{
	    port = Dio_Configuration_Ptr->Channels[ChannelId].Port_Num;
        pin = Dio_Configuration_Ptr->Channels[ChannelId].Ch_Num;
		
		if((DIO_PORT(port)->DATA) & (1<<pin))
		{
			/* Channel is Logic High */
			pin_status = STD_HIGH;
		}else
		{
			/* Channel is LOW */
			pin_status = STD_LOW;
		}
	}
	else
	{
		/* No Action Required */
	}
	return pin_status;
}

/************************************************************************************
* Service Name: Dio_GetVersionInfo
* Service ID[hex]: 0x12
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Function to get the version information of this module.
************************************************************************************/
#if (DIO_VERSION_INFO_API == STD_ON)
void Dio_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
    /**************************************************************************************/
    /*                              Start of Error Checking                               */
    /**************************************************************************************/
#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_GET_VERSION_INFO_SID, DIO_E_PARAM_POINTER);
	}
	else
#endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
    /**************************************************************************************/
    /*                              End of Error Checking                                 */
    /**************************************************************************************/

    /**************************************************************************************/
    /*                              Function Implementation                               */
    /**************************************************************************************/
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)DIO_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)DIO_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)DIO_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)DIO_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)DIO_SW_PATCH_VERSION;
	}
}
#endif

/************************************************************************************
* Service Name: Dio_FlipChannel
* Service ID[hex]: 0x11
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_LevelType
* Description: Function to flip the level of a channel and return the level of the channel after flip.
************************************************************************************/
#if (DIO_FLIP_CHANNEL_API == STD_ON)
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
    Dio_PortType port;
    Dio_ChannelType pin;
	boolean error = FALSE;
	Dio_LevelType pin_status = STD_LOW;
    /**************************************************************************************/
    /*                              Start of Error Checking                               */
    /**************************************************************************************/
#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
		DIO_FLIP_CHANNEL_SID, DIO_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (DIO_CONFIGURED_CHANNLES <= ChannelId)
	{

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
		DIO_FLIP_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
#endif
    /**************************************************************************************/
    /*                              End of Error Checking                                 */
    /**************************************************************************************/

    /**************************************************************************************/
    /*                              Function Implementation                               */
    /**************************************************************************************/
	/* In-case there are no errors */
	if(FALSE == error)
	{
	    port = Dio_Configuration_Ptr->Channels[ChannelId].Port_Num;
        pin = Dio_Configuration_Ptr->Channels[ChannelId].Ch_Num;
		
        if((DIO_PORT(port)->DATA) & (1<<pin))
        {
            /* Channel is Logic High */
            /* Write Logic Low */
            DIO_PORT(port)->DATA &= ~(1<<pin);
            pin_status = STD_LOW;
        }else
        {
            /* Channel is LOW */
            /* Write Logic High */
            DIO_PORT(port)->DATA |= (1<<pin);
            pin_status = STD_HIGH;
        }
	}
	else
	{
		/* No Action Required */
	}
	return pin_status;
}
#endif

/************************************************************************************
* Service Name: Dio_ReadPort
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): PortId - ID of DIO port.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_PortLevelType
* Description: Function to read the logic level of a whole port.
************************************************************************************/
#if (DIO_CONFIGURED_PORTS != 0)/***************/
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
	Dio_PortType port;
	boolean error = FALSE;
	Dio_PortLevelType port_status = STD_LOW;
    /**************************************************************************************/
    /*                              Start of Error Checking                               */
    /**************************************************************************************/
#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
		DIO_READ_PORT_SID, DIO_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	/* Check if the used port is within the valid range */
	if (DIO_CONFIGURED_PORTS <= PortId)
	{

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
		DIO_READ_PORT_SID, DIO_E_PARAM_INVALID_PORT_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
#endif
    /**************************************************************************************/
    /*                              End of Error Checking                                 */
    /**************************************************************************************/

    /**************************************************************************************/
    /*                              Function Implementation                               */
    /**************************************************************************************/
	/* In-case there are no errors */
	if(FALSE == error)
	{
	    port = Dio_Configuration_Ptr->Ports[PortId];

		port_status = DIO_PORT(port)->DATA;
	}
	else
	{
		/* No Action Required */
	}
	return port_status;	
}


/************************************************************************************
* Service Name: Dio_WritePort
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): PortID - ID of DIO port.
*				   Level - Logical High or Low.
* Parameters (inout): None
* Parameters (out): None
* Return value: void
* Description: Function to write a logical level on a whole port.
************************************************************************************/
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
	Dio_PortType port;
	boolean error = FALSE;
    /**************************************************************************************/
    /*                              Start of Error Checking                               */
    /**************************************************************************************/
#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
		DIO_WRITE_PORT_SID, DIO_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	/* Check if the used port is within the valid range */
	if (DIO_CONFIGURED_PORTS <= PortId)
	{

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
		DIO_WRITE_PORT_SID, DIO_E_PARAM_INVALID_PORT_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
#endif
    /**************************************************************************************/
    /*                              End of Error Checking                                 */
    /**************************************************************************************/

    /**************************************************************************************/
    /*                              Function Implementation                               */
    /**************************************************************************************/
	/* In-case there are no errors */
	if(FALSE == error)
	{
	    port = Dio_Configuration_Ptr->Ports[PortId];

	    DIO_PORT(port)->DATA = Level;
	}
	else
	{
		/* No Action Required */
	}	
}
#endif

/************************************************************************************
* Service Name: Dio_ReadChannelGroup
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelGroupIdPtr - Pointer to the channel group.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_PortLevelType
* Description: Function to read the logical level of channel group.
************************************************************************************/
#if (DIO_CONFIGURED_CHANNEL_GROUPS != 0)
Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType* ChannelGroupIdPtr )
{
	Dio_PortLevelType group_stat = 0x00;
	Dio_PortType port;
	boolean error = FALSE;
    /**************************************************************************************/
    /*                              Start of Error Checking                               */
    /**************************************************************************************/
#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
		DIO_READ_CHANNEL_GROUP_SID, DIO_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	/* Check if the used port is within the valid range */
	if (NULL_PTR == ChannelGroupIdPtr)
	{

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
		DIO_READ_CHANNEL_GROUP_SID, DIO_E_PARAM_INVALID_GROUP);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
#endif
    /**************************************************************************************/
    /*                              End of Error Checking                                 */
    /**************************************************************************************/

    /**************************************************************************************/
    /*                              Function Implementation                               */
    /**************************************************************************************/
	if (FALSE == error)
	{
	    port = ChannelGroupIdPtr->PortIndex;

		group_stat = ((DIO_PORT(port)->DATA) & ChannelGroupIdPtr->mask) >> (ChannelGroupIdPtr->offset);
	}
	return group_stat;
}


/************************************************************************************
* Service Name: Dio_WriteChannelGroup
* Service ID[hex]: 0x05
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelGroupIdPtr - Pointer to the channel group.
*				   Level - Logical High or Low.
* Parameters (inout): None
* Parameters (out): None
* Return value: void
* Description: Function to write a logical level on a channel group.
************************************************************************************/
void Dio_WriteChannelGroup( const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level )
{
	Dio_PortType port;
	Dio_PortLevelType temp_lvl = 0x00;
	boolean error = FALSE;
    /**************************************************************************************/
    /*                              Start of Error Checking                               */
    /**************************************************************************************/
#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
		DIO_WRITE_CHANNEL_GROUP_SID, DIO_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	/* Check if the used port is within the valid range */
	if (NULL_PTR == ChannelGroupIdPtr)
	{

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
		DIO_WRITE_CHANNEL_GROUP_SID, DIO_E_PARAM_INVALID_GROUP);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
#endif
    /**************************************************************************************/
    /*                              End of Error Checking                                 */
    /**************************************************************************************/

    /**************************************************************************************/
    /*                              Function Implementation                               */
    /**************************************************************************************/
	if (FALSE == error)
	{
	    port = ChannelGroupIdPtr->PortIndex;
		temp_lvl = DIO_PORT(port)->DATA;

		DIO_PORT(port)->DATA = (ChannelGroupIdPtr->mask) & (Level << (ChannelGroupIdPtr->offset));
		
		temp_lvl &= ~(ChannelGroupIdPtr->mask);
		DIO_PORT(port)->DATA |= temp_lvl;
	}
}
#endif
