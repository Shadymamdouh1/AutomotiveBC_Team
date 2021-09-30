 /******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt.c
 *
 * Description: Source file for Gpt Module.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/
 
 #include "Gpt.h"
 #include "Gpt_Regs.h"
 #include "Gpt_Irq.h"
 /* AUTOSAR checking between Det and GPT Modules */
 #if (GPT_DEV_ERROR_DETECT == STD_ON)
// #include "Det.h"
 #if ((DET_AR_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||	 (DET_AR_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (DET_AR_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
 #error "The AR version of Det.h does not match the AR version of Gpt.h"
 #endif

 #endif

/*******************************************************************************
 *                    Global Macros and Static Functions                       *
 *******************************************************************************/
#define get_GPT_MODULE(X)          (Gpt_ChannelType)(X/10)
#define get_GPT_SUBMODULE(X)       (Gpt_ChannelType)(X%10)

STATIC void Gpt_ClockEnable(Gpt_ChannelType   Module_Num)
{
    if(Module_Num < 6)
        SYSCTL_RCGCTIMER_R |= 1<<Module_Num;
    else
        SYSCTL_RCGCWTIMER_R |= 1<<(Module_Num-6);
}
STATIC void Gpt_ClockDisable(Gpt_ChannelType   Module_Num)
{
    if(Module_Num < 6)
        SYSCTL_RCGCTIMER_R &= ~(1<<Module_Num);
    else
        SYSCTL_RCGCWTIMER_R &= ~(1<<(Module_Num-6));
}
/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/
typedef struct
{
	 Gpt_StateType timer_state[GPT_CONFIGURED_CHANNELS];
	 Gpt_ValueType Max_value[GPT_CONFIGURED_CHANNELS];
	 Gpt_ValueType Target_value[GPT_CONFIGURED_CHANNELS];
	 Gpt_ValueType Stopped_value[GPT_CONFIGURED_CHANNELS];
     uint8 reserved_mods[24];
	 Gpt_ModeType  Gpt_mode;
	 Gpt_NotificationStateType channel_notification[GPT_CONFIGURED_CHANNELS];
}Gpt_GlobalType;

STATIC Gpt_ChannelConfigType* channelconfig_ptr = NULL_PTR;
STATIC Gpt_GlobalType Gpt_Global_Info = 
{
	{Gpt_Uninitialized},
	{GPT_PRESCALER_OFF},
	{0},
	{0},
	{0},
	GPT_MODE_NORMAL,
	{Gpt_Notification_Disabled}
};
/*******************************************************************************
 *                      Function Definitions                                   *
 *******************************************************************************/

/************************************************************************************
* Service Name: Gpt_GetVersionInfo
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): VersionInfoPtr - Pointer to Structure type with the version's parameters (major, minor, patch)
* Return value: None
* Description: Function to return the version information of the gpt module.
************************************************************************************/
#if (GPT_VERSION_INFO_API == STD_ON)
void Gpt_GetVersionInfo( Std_VersionInfoType* VersionInfoPtr )
{
	boolean error = FALSE;
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
/* 
 * Error Detection and reporting to Det Module is enabled by 
 * assigning STD_ON to GPT_DEV_ERROR_DETECT in Gpt_Cfg.h 
 */
#if (GPT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == VersionInfoPtr)
	{
		/* Report to DET  */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,GPT_GET_VERSION_INFO_SID, GPT_E_PARAM_POINTER);
		error = TRUE;
	}
#endif	
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/* In case there are no errors */
	if(FALSE == error)
	{
		/* Send the Gpt Module ID */
		VersionInfoPtr->moduleID         = (uint16)GPT_MODULE_ID;
		/* Send the Gpt Module Software Major Version */
		VersionInfoPtr->sw_major_version = (uint8)GPT_SW_MAJOR_VERSION;
		/* Send the Gpt Module Software Minor Version */
		VersionInfoPtr->sw_minor_version = (uint8)GPT_SW_MINOR_VERSION;
		/* Send the Gpt Module Software Patch Version */
		VersionInfoPtr->sw_patch_version = (uint8)GPT_SW_PATCH_VERSION;
		/* Send the Gpt Module Vendor ID */
		VersionInfoPtr->vendorID		  = (uint16)GPT_VENDOR_ID;
	}else
	{
		/* Nothing to do here yet */
	}
}
#endif

/************************************************************************************
* Service Name: Gpt_Init
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Gpt module.
************************************************************************************/
void Gpt_Init( const Gpt_ConfigType* ConfigPtr )
{
	boolean error = FALSE;
	uint8 loop_index = 0;
	Gpt_ChannelType Gpt_Module;
	Gpt_ChannelType Gpt_SubModule;
	Gpt_ChannelConfigType* channel_temp_ptr = NULL_PTR;

/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
/* 
 * Error Detection and reporting to Det Module is enabled by 
 * assigning STD_ON to GPT_DEV_ERROR_DETECT in Gpt_Cfg.h 
 */
#if (GPT_DEV_ERROR_DETECT == STD_ON)
/* Check if the input parameter is NULL */
	if (NULL_PTR == ConfigPtr)
	{
    /* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_INIT_SID, GPT_E_PARAM_POINTER);
		error = TRUE;
	}else{/*Nothing to here*/}
	for(loop_index = 0;loop_index<GPT_CONFIGURED_CHANNELS;loop_index++)
    {
    /* Check if the module is not initialized */
        if (Gpt_Uninitialized != Gpt_Global_Info.timer_state[loop_index])
        {
        /* Report Parameter Error to the Det Module */
            Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DEINIT_SID, GPT_E_ALREADY_INITIALIZED);
            error = TRUE;
        }else{/*Nothing to here*/}
    /* Check if the module is reserved before */
        Gpt_Module = (ConfigPtr->Timer_Channels[loop_index].Timer_Id)/10;
        Gpt_SubModule = (ConfigPtr->Timer_Channels[loop_index].Timer_Id)%10;
        if(Gpt_SubModule<2) // A or B
        {
            index_num =  (2*Gpt_Module)+Gpt_SubModule;
            if (1 == Gpt_Global_Info.reserved_mods[index_num])
            {
            /* Report Parameter Error to the Det Module */
                Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DEINIT_SID, GPT_E_PARAM_CHANNEL);
                error = TRUE;
            }else
            {
            /* Update the timer modules used to reserved */
                Gpt_Global_Info.reserved_mods[index_num] = 1;
            }
        }else // A and B
        {
            index_num = 2*Gpt_Module;
            if ((1 == Gpt_Global_Info.reserved_mods[index_num]) || (1 == Gpt_Global_Info.reserved_mods[index_num+1]))
            {
            /* Report Parameter Error to the Det Module */
                Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DEINIT_SID, GPT_E_PARAM_CHANNEL);
                error = TRUE;
            }else
            {
            /* Update the timer modules used to reserved */
                Gpt_Global_Info.reserved_mods[index_num] = 1;
                Gpt_Global_Info.reserved_mods[index_num+1] = 1;
            }
        }
    }
		
#endif	
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/

	/* In case there are no errors */
	if (FALSE == error)
	{
    /* Point to the Configuration Struct in Gpt_PBCfg.c */
		channelconfig_ptr = (Gpt_ChannelConfigType*) ConfigPtr->Timer_Channels;
		for(loop_index = 0;loop_index<GPT_CONFIGURED_CHANNELS;loop_index++)
		{
		    channel_temp_ptr = &channelconfig_ptr[loop_index];
			Gpt_Module = get_GPT_MODULE(channel_temp_ptr->Timer_Id);
			Gpt_SubModule = get_GPT_SUBMODULE(channel_temp_ptr->Timer_Id);

        /*
         * Initialize the Configured Timer Modules
         */
        /* Enable Clock to the used Timer Module */
			Gpt_ClockEnable(Gpt_Module);

			if(Gpt_SubModule == GPT_TIMER_AB) //Timer A and B concatenated
			{
            /* Disable Timer A and Timer B to configure parameters */
			    GPT(Gpt_Module)->CTL &= ~(1<<GPT_CTL_TAEN);
#if(GPT_STALL_DEBUGGER == STD_ON)
            /* Enable the freeze counting while debugging */
			    GPT(Gpt_Module)->CTL |= 1<<GPT_CTL_TASTALL;
#endif
            /* Set to Concatenated Timer A and B mode */
			    GPT(Gpt_Module)->CFG = GPT_CFG_CONCATENATED;
            /* Periodic or One Shot */
			    GPT(Gpt_Module)->TAMR |= (channel_temp_ptr->RunMode)<<GPT_TAMR_TAMR;
            /* Count UP */
			    GPT(Gpt_Module)->TAMR |= (1<<GPT_TAMR_TACDIR);
            /* Counter and Prescaler status */
			    if((channel_temp_ptr->Timer_Width) == GPT_WIDTH_TIM_AB_32BITS)
			    {
                /* Update the Module's maximum value */
			        Gpt_Global_Info.Max_value[loop_index] = GPT_MAX_VALUE_32BIT;
			    }else if((channel_temp_ptr->Timer_Width) == GPT_WIDTH_WTIM_AB_64BITS)
			    {
                /* Update the Module's maximum value */
			        Gpt_Global_Info.Max_value[loop_index] = GPT_MAX_VALUE_64BIT;
			    }
#if (GPT_DEV_ERROR_DETECT == STD_ON)
			    /* Check if the width is configured wrong */
			    else
			    {
                /* Report width parameter DET error */
			        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_INIT_SID, GPT_E_PARAM_WIDTH);
			    }
#endif
			}else if(Gpt_SubModule == GPT_TIMER_B) //TimerB
			{
            /* Disable Timer B to configure parameters */
			    GPT(Gpt_Module)->CTL &= ~(1<<GPT_CTL_TBEN);
#if(GPT_STALL_DEBUGGER == STD_ON)
            /* Enable the freeze counting while debugging */
                GPT(Gpt_Module)->CTL |= 1<<GPT_CTL_TBSTALL;
#endif
            /* Set to Individual Timer B mode */
			    GPT(Gpt_Module)->CFG = GPT_CFG_INDIVIDUAL;
            /* Periodic or One Shot */
                GPT(Gpt_Module)->TBMR |= (channel_temp_ptr->RunMode)<<GPT_TAMR_TAMR;
            /* Count UP */
                GPT(Gpt_Module)->TBMR |= (1<<GPT_TAMR_TACDIR);
            /* Counter and Prescaler status */
                switch(channel_temp_ptr->Timer_Width)
                {/* Update the Module's maximum value */
                case GPT_WIDTH_TIM_B_16BITS:
                    Gpt_Global_Info.Max_value[loop_index] = GPT_MAX_VALUE_16BIT;
                    break;
                case GPT_WIDTH_TIM_B_24BITS:
                    Gpt_Global_Info.Max_value[loop_index] = GPT_MAX_VALUE_24BIT;
                    break;
                case GPT_WIDTH_WTIM_B_32BITS:
                    Gpt_Global_Info.Max_value[loop_index] = GPT_MAX_VALUE_32BIT;
                    break;
                case GPT_WIDTH_WTIM_B_48BITS:
                    Gpt_Global_Info.Max_value[loop_index] = GPT_MAX_VALUE_48BIT;
                    break;
                default:
                    break;
                }
			}else if(Gpt_SubModule == GPT_TIMER_A) //TimerA
			{
            /* Disable Timer A to configure parameters */
			    GPT(Gpt_Module)->CTL &= ~(1<<GPT_CTL_TAEN);
#if(GPT_STALL_DEBUGGER == STD_ON)
            /* Enable the freeze counting while debugging */
                GPT(Gpt_Module)->CTL |= 1<<GPT_CTL_TASTALL;
#endif
            /* Set to Individual Timer A mode */
                GPT(Gpt_Module)->CFG = GPT_CFG_INDIVIDUAL;
            /* Periodic or One Shot */
                GPT(Gpt_Module)->TAMR |= (channel_temp_ptr->RunMode)<<GPT_TAMR_TAMR;
            /* Count UP */
                GPT(Gpt_Module)->TAMR |= (1<<GPT_TAMR_TACDIR);
            /* Counter and Prescaler status */
                switch(channel_temp_ptr->Timer_Width)
                {/* Update the Module's maximum value */
                case GPT_WIDTH_TIM_A_16BITS:
                    Gpt_Global_Info.Max_value[loop_index] = GPT_MAX_VALUE_16BIT;
                    break;
                case GPT_WIDTH_TIM_A_24BITS:
                    Gpt_Global_Info.Max_value[loop_index] = GPT_MAX_VALUE_24BIT;
                    break;
                case GPT_WIDTH_WTIM_A_32BITS:
                    Gpt_Global_Info.Max_value[loop_index] = GPT_MAX_VALUE_32BIT;
                    break;
                case GPT_WIDTH_WTIM_A_48BITS:
                    Gpt_Global_Info.Max_value[loop_index] = GPT_MAX_VALUE_48BIT;
                    break;
                default:
                    break;
                }
			}else{/* Nothing to do here */}

        /* Update the timer module to Initialized state */
			Gpt_Global_Info.timer_state[loop_index] = Gpt_Initialized;
        /* Disable all interrupts */
            GPT(Gpt_Module)->IMR = 0x00;
		}
	}
		
}

/************************************************************************************
* Service Name: Gpt_DeInit
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to DeInitialize the Gpt module.
************************************************************************************/
#if (GPT_DEINIT_API == STD_ON)
void Gpt_DeInit( void )
{
	boolean error = FALSE;
	uint8 loop_index = 0;
    Gpt_ChannelType Gpt_Module;
//    Gpt_ChannelType Gpt_SubModule;
    Gpt_ChannelConfigType* channel_temp_ptr = NULL_PTR;
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
/* 
 * Error Detection and reporting to Det Module is enabled by 
 * assigning STD_ON to GPT_DEV_ERROR_DETECT in Gpt_Cfg.h 
 */
#if (GPT_DEV_ERROR_DETECT == STD_ON)
	/* Chek if the channel configuration global variable is NULL */
	if(NULL_PTR == channelconfig_ptr)
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DEINIT_SID, GPT_E_PARAM_POINTER);
		error = TRUE;
	}else{/*Nothing to here*/}
	for(loop_index = 0;loop_index<GPT_CONFIGURED_CHANNELS;loop_index++)
	{
		/* Check if the module is not initialized */
		if (Gpt_Uninitialized == Gpt_Global_Info.timer_state[loop_index])
		{
			/* Report Parameter Error to the Det Module */
			Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DEINIT_SID, GPT_E_UNINIT);
			error = TRUE;
		}else{/*Nothing to here*/}
		/* Check if the module is not initialized */
		if (Gpt_Running == Gpt_Global_Info.timer_state[loop_index])
		{
			/* Report Parameter Error to the Det Module */
			Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DEINIT_SID, GPT_E_BUSY);
			error = TRUE;
		}else{/*Nothing to here*/}
	}
#endif	
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/

	/* In case there are no errors */
	if (FALSE == error)
	{
		for(loop_index = 0;loop_index<GPT_CONFIGURED_CHANNELS;loop_index++)
		{
            channel_temp_ptr = &channelconfig_ptr[loop_index];
            Gpt_Module = get_GPT_MODULE(channel_temp_ptr->Timer_Id);
//            Gpt_SubModule = get_GPT_SUBMODULE(channel_temp_ptr->Timer_Id);

            GPT(Gpt_Module)->CFG  = 0x00;
            GPT(Gpt_Module)->TAMR = 0x00;
            GPT(Gpt_Module)->TBMR = 0x00;
            GPT(Gpt_Module)->CTL  = 0x00;
            GPT(Gpt_Module)->IMR  = 0x00;
            GPT(Gpt_Module)->ICR  = 0x00;
            GPT(Gpt_Module)->TAILR= 0x00;
            GPT(Gpt_Module)->TBILR= 0x00;
            GPT(Gpt_Module)->TAPR = 0x00;
            GPT(Gpt_Module)->TBPR = 0x00;
            GPT(Gpt_Module)->TAV  = 0x00;
            GPT(Gpt_Module)->TBV  = 0x00;
            Gpt_ClockDisable(Gpt_Module);
            /* Return the timer module to uninitialized state */
			Gpt_Global_Info.timer_state[loop_index] = Gpt_Uninitialized;
		}
		/* Return the global configuration pointer to NULL */
		channelconfig_ptr = NULL_PTR;
	}	
}
#endif


/************************************************************************************
* Service Name: Gpt_GetTimeElapsed
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel - The timer channel ID.
* Parameters (inout): None
* Parameters (out): None
* Return value: Gpt_ValueType - Data type for the value of timer counter in ticks
* Description: Function to return the elapsed time from start of counting until now.
************************************************************************************/
#if (GPT_TIME_ELAPSED_API == STD_ON)
Gpt_ValueType Gpt_GetTimeElapsed( Gpt_ChannelType Channel )
{
	boolean error = FALSE;
	Gpt_ValueType elapsedValue = 0;
    Gpt_ChannelType Gpt_Module;
    Gpt_ChannelType Gpt_SubModule;
	Gpt_ChannelConfigType* channel_temp_ptr = NULL_PTR;
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
/* 
 * Error Detection and reporting to Det Module is enabled by 
 * assigning STD_ON to GPT_DEV_ERROR_DETECT in Gpt_Cfg.h 
 */
#if (GPT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the module is not initialized */
	if (Gpt_Uninitialized == Gpt_Global_Info.timer_state[Channel])
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_TIME_ELAPSED_SID, GPT_E_UNINIT);
		error = TRUE;
	}else{/*Nothing to here*/}	
	
	/* Chek if the channel configuration global variable is NULL */
	if(NULL_PTR == channelconfig_ptr)
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_TIME_ELAPSED_SID, GPT_E_PARAM_POINTER);
		error = TRUE;
	}else{/*Nothing to here*/}
		
	/* Chek if the channel id is valid */
	if(GPT_CONFIGURED_CHANNELS <= Channel)
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_TIME_ELAPSED_SID, GPT_E_PARAM_CHANNEL);
		error = TRUE;
	}else{/*Nothing to here*/}
	
#endif
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/	
	if (FALSE == error)
	{
	    channel_temp_ptr = &channelconfig_ptr[Channel];
        Gpt_Module = get_GPT_MODULE(channel_temp_ptr->Timer_Id);
        Gpt_SubModule = get_GPT_SUBMODULE(channel_temp_ptr->Timer_Id);

		if (Gpt_Initialized == Gpt_Global_Info.timer_state[Channel])
		{
			elapsedValue = 0;
		}else if (Gpt_Expired == Gpt_Global_Info.timer_state[Channel])
		{
			elapsedValue = Gpt_Global_Info.Target_value[Channel];
		} 
		else if(Gpt_Stopped == Gpt_Global_Info.timer_state[Channel])
		{
			elapsedValue = Gpt_Global_Info.Stopped_value[Channel];
		}else if(Gpt_Running == Gpt_Global_Info.timer_state[Channel])
		{
            switch(Gpt_SubModule)
            {
        /************************************************************************/
        /************************************************************************/
            case GPT_TIMER_AB: //Concatenated Timer Modules
                if(Gpt_Module<6) //Normal 32 bits Timer
                {   elapsedValue = GPT(Gpt_Module)->TAR;   }
                else //Wide 64 bits Timer
                {   elapsedValue = (GPT(Gpt_Module)->TAR) | ((Gpt_ValueType)(GPT(Gpt_Module)->TBR)<<32);    }
                break;
        /************************************************************************/
        /************************************************************************/
            case GPT_TIMER_B: //Timer B
                if(Gpt_Module<6) //Normal 32 bits Timer
                {   elapsedValue = GPT(Gpt_Module)->TBV;   }
                else //Wide 64 bits Timer
                {   elapsedValue = (GPT(Gpt_Module)->TBV) | ((Gpt_ValueType)(GPT(Gpt_Module)->TBPV)<<32);    }
                break;
        /************************************************************************/
        /************************************************************************/
            case GPT_TIMER_A: //Timer A
                if(Gpt_Module<6) //Normal 32 bits Timer
                {   elapsedValue = GPT(Gpt_Module)->TAV;   }
                else //Wide 64 bits Timer
                {   elapsedValue = (GPT(Gpt_Module)->TAV) | ((Gpt_ValueType)(GPT(Gpt_Module)->TAPV)<<32);    }
                break;
        /************************************************************************/
        /************************************************************************/
            default:
            break;
            }
		}
	} 
	else
	{
		/* Nothing to do here yet */
	}
	return elapsedValue;
}
#endif


/************************************************************************************
* Service Name: Gpt_GetTimeRemaining
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel - The timer channel ID.
* Parameters (inout): None
* Parameters (out): None
* Return value: Gpt_ValueType - Data type for the value of timer counter in ticks
* Description: Function to return the remaining time from now until the reaching the time target.
************************************************************************************/
#if (GPT_TIME_REAMAINING_API == STD_ON)
Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType Channel )
{
	boolean error = FALSE;
    Gpt_ChannelType Gpt_Module;
    Gpt_ChannelType Gpt_SubModule;
	Gpt_ValueType remainValue = 0;
	Gpt_ChannelConfigType* channel_temp_ptr = NULL_PTR;
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
/* 
 * Error Detection and reporting to Det Module is enabled by 
 * assigning STD_ON to GPT_DEV_ERROR_DETECT in Gpt_Cfg.h 
 */
#if (GPT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the module is not initialized */
	if (Gpt_Uninitialized == Gpt_Global_Info.timer_state[Channel])
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_TIME_REMAINING_SID, GPT_E_UNINIT);
		error = TRUE;
	}else{/*Nothing to here*/}	
	
	/* Chek if the channel configuration global variable is NULL */
	if(NULL_PTR == channelconfig_ptr)
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_TIME_REMAINING_SID, GPT_E_PARAM_POINTER);
		error = TRUE;
	}else{/*Nothing to here*/}
		
	/* Chek if the channel id is valid */
	if(GPT_CONFIGURED_CHANNELS <= Channel)
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_TIME_REMAINING_SID, GPT_E_PARAM_CHANNEL);
		error = TRUE;
	}else{/*Nothing to here*/}
	
#endif
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/	
	if (FALSE == error)
	{
        channel_temp_ptr = &channelconfig_ptr[Channel];
        Gpt_Module = get_GPT_MODULE(channel_temp_ptr->Timer_Id);
        Gpt_SubModule = get_GPT_SUBMODULE(channel_temp_ptr->Timer_Id);
		if (Gpt_Initialized == Gpt_Global_Info.timer_state[Channel])
		{
			remainValue = 0;
		}else if (Gpt_Expired == Gpt_Global_Info.timer_state[Channel])
		{
			remainValue = 0;
		} 
		else if(Gpt_Stopped == Gpt_Global_Info.timer_state[Channel])
		{
			remainValue = Gpt_Global_Info.Target_value[Channel] - Gpt_Global_Info.Stopped_value[Channel];
		}else if(Gpt_Running == Gpt_Global_Info.timer_state[Channel])
		{
		    switch(Gpt_SubModule)
            {
        /************************************************************************/
        /************************************************************************/
            case GPT_TIMER_AB: //Concatenated Timer Modules
                if(Gpt_Module<6) //Normal 32 bits Timer
                {   remainValue = Gpt_Global_Info.Target_value[Channel] - GPT(Gpt_Module)->TAR;   }
                else //Wide 64 bits Timer
                {   remainValue = Gpt_Global_Info.Target_value[Channel] - ((GPT(Gpt_Module)->TAR) | ((Gpt_ValueType)(GPT(Gpt_Module)->TBR)<<32));    }
                break;
        /************************************************************************/
        /************************************************************************/
            case GPT_TIMER_B: //Timer B
                if(Gpt_Module<6) //Normal 32 bits Timer
                {   remainValue = Gpt_Global_Info.Target_value[Channel] - GPT(Gpt_Module)->TBV;   }
                else //Wide 64 bits Timer
                {   remainValue = Gpt_Global_Info.Target_value[Channel] - ((GPT(Gpt_Module)->TBV) | ((Gpt_ValueType)(GPT(Gpt_Module)->TBPV)<<32));    }
                break;
        /************************************************************************/
        /************************************************************************/
            case GPT_TIMER_A: //Timer A
                if(Gpt_Module<6) //Normal 32 bits Timer
                {   remainValue = Gpt_Global_Info.Target_value[Channel] - GPT(Gpt_Module)->TAV;   }
                else //Wide 64 bits Timer
                {   remainValue = Gpt_Global_Info.Target_value[Channel] - ((GPT(Gpt_Module)->TAV) | ((Gpt_ValueType)(GPT(Gpt_Module)->TAPV)<<32));    }
                break;
        /************************************************************************/
        /************************************************************************/
            default:
            break;
            }
		}
	} 
	else
	{
		/* Nothing to do here yet */
	}
	return remainValue;
}
#endif


/************************************************************************************
* Service Name: Gpt_StartTimer
* Service ID[hex]: 0x05
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel - The timer channel ID.
				   Value - The target time that the timer should reach.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Start the Timer module counting from 0x00 until (Value).
************************************************************************************/
void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value )
{
	boolean error = FALSE;
    Gpt_ChannelType Gpt_Module;
    Gpt_ChannelType Gpt_SubModule;
    Gpt_ChannelConfigType* channel_temp_ptr = NULL_PTR;

    channel_temp_ptr = &channelconfig_ptr[Channel];
    Gpt_Module = get_GPT_MODULE(channel_temp_ptr->Timer_Id);
    Gpt_SubModule = get_GPT_SUBMODULE(channel_temp_ptr->Timer_Id);
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
/* 
 * Error Detection and reporting to Det Module is enabled by 
 * assigning STD_ON to GPT_DEV_ERROR_DETECT in Gpt_Cfg.h 
 */
#if (GPT_DEV_ERROR_DETECT == STD_ON)
/* Check if the module is not initialized */
	if (Gpt_Uninitialized == Gpt_Global_Info.timer_state[Channel])
	{
    /* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_START_TIMER_SID, GPT_E_UNINIT);
		error = TRUE;
	}else{/*Nothing to here*/}
		
/* Check if the module is not initialized */
	if (Gpt_Running == Gpt_Global_Info.timer_state[Channel])
	{
    /* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_START_TIMER_SID, GPT_E_BUSY);
		error = TRUE;
	}else{/*Nothing to here*/}		
	
/* Chek if the channel configuration global variable is NULL */
	if(NULL_PTR == channelconfig_ptr)
	{
    /* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_START_TIMER_SID, GPT_E_PARAM_POINTER);
		error = TRUE;
	}else{/*Nothing to here*/}
		
/* Chek if the channel id is valid */
	if(GPT_CONFIGURED_CHANNELS <= Channel)
	{
    /* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_START_TIMER_SID, GPT_E_PARAM_CHANNEL);
		error = TRUE;
	}else{/*Nothing to here*/}
	
/* Check for the value of the target time if it in the expected range and not equal to zero */
	if((Value > (Gpt_Global_Info.Max_value[Channel])) || (Value==0))
	{
    /* Report Parameter Error to the Det Module */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_START_TIMER_SID, GPT_E_PARAM_VALUE);
        error = TRUE;
	}
#endif	
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/* In case there are no errors */
	if(FALSE == error)
	{
    /* Save the target value in the global struct */
        Gpt_Global_Info.Target_value[Channel] = Value;
	    switch(Gpt_SubModule)
	    {
    /************************************************************************/
    /************************************************************************/
	    case GPT_TIMER_AB: //Concatenated Timer Modules
	        if(Gpt_Module<6) //Normal 32 bits Timer
	        {   /* Load the 32 bits value in TAILR Register */
	            GPT(Gpt_Module)->TAV  = 0x00;
	            GPT(Gpt_Module)->TAILR = Value;
	        }
	        else //Wide 64 bits Timer
	        {   /* Load the first 32 bits of the 64 bits value in TAILR and the second 32 bits in TBILR */
	            GPT(Gpt_Module)->TAV  = 0x00;
                GPT(Gpt_Module)->TBV  = 0x00;
	            GPT(Gpt_Module)->TAILR = Value & 0xFFFFFFFF;
	            GPT(Gpt_Module)->TBILR = (Value & 0xFFFFFFFF00000000)>>32;
	        }
	        /* Start Counting by setting Timer A Enable */
	        GPT(Gpt_Module)->CTL |= 1<<GPT_CTL_TAEN;
	        break;
    /************************************************************************/
    /************************************************************************/
	    case GPT_TIMER_B: //Timer B
            GPT(Gpt_Module)->TBV  = 0x00;
            GPT(Gpt_Module)->TBILR = 0x00;
	        if((channel_temp_ptr->Timer_Width) == GPT_WIDTH_TIM_B_16BITS)
	        { /* Normal or Wide Timer == No Prescaler */
            /* Load the 16 or 32 bits value in TBILR Register */
                GPT(Gpt_Module)->TBILR = Value;
	        }else if((channel_temp_ptr->Timer_Width) == GPT_WIDTH_TIM_B_24BITS)
	        { /* Normal 16 bits Timer B with 8 bits prescaler */
            /* Load the 16 bits value in TBILR Register */
                GPT(Gpt_Module)->TBILR = Value&0xFFFF;
            /* Load the 8 bits prescaler in TBPR Register */
                GPT(Gpt_Module)->TBPR = Value>>16;
	        }else if((channel_temp_ptr->Timer_Width) == GPT_WIDTH_WTIM_B_32BITS)
            { /* Normal or Wide Timer == No Prescaler */
            /* Load the 16 or 32 bits value in TBILR Register */
                GPT(Gpt_Module)->TBILR = Value;
            }else if((channel_temp_ptr->Timer_Width) == GPT_WIDTH_WTIM_B_48BITS)
	        { /* Wide 32 bits Timer B with 16 bits prescaler */
            /* Load the 32 bits value in TBILR Register */
                GPT(Gpt_Module)->TBILR = Value&0xFFFFFFFF;
            /* Load the 16 bits prescaler in TBPR Register */
                GPT(Gpt_Module)->TBPR = Value>>32;
	        }
        /* Start Counting by setting Timer B Enable */
	        GPT(Gpt_Module)->CTL |= 1<<GPT_CTL_TBEN;
	        break;
    /************************************************************************/
    /************************************************************************/
	    case GPT_TIMER_A: //Timer A
	        GPT(Gpt_Module)->TAV  = 0x00;
            if((channel_temp_ptr->Timer_Width) == GPT_WIDTH_TIM_A_16BITS)
            { /* Normal or Wide Timer == No Prescaler */
            /* Load the 16 or 32 bits value in TAILR Register */
                GPT(Gpt_Module)->TAILR = Value;
            }else if((channel_temp_ptr->Timer_Width) == GPT_WIDTH_TIM_A_24BITS)
            { /* Normal 16 bits Timer B with 8 bits prescaler */
            /* Load the 16 bits value in TAILR Register */
                GPT(Gpt_Module)->TAILR = Value&0xFFFF;
            /* Load the 8 bits prescaler in TAPR Register */
                GPT(Gpt_Module)->TAPR = Value>>16;
            }else if((channel_temp_ptr->Timer_Width) == GPT_WIDTH_WTIM_A_32BITS)
            { /* Normal or Wide Timer == No Prescaler */
            /* Load the 16 or 32 bits value in TAILR Register */
                GPT(Gpt_Module)->TAILR = Value;
            }else if((channel_temp_ptr->Timer_Width) == GPT_WIDTH_WTIM_A_48BITS)
            { /* Wide 32 bits Timer B with 16 bits prescaler */
            /* Load the 32 bits value in TAILR Register */
                GPT(Gpt_Module)->TAILR = Value&0xFFFFFFFF;
            /* Load the 16 bits prescaler in TAPR Register */
                GPT(Gpt_Module)->TAPR = Value>>32;
            }
        /* Start Counting by setting Timer A Enable */
	        GPT(Gpt_Module)->CTL |= 1<<GPT_CTL_TAEN;
	        break;
    /************************************************************************/
    /************************************************************************/
	    default:
	        break;
	    }
		/* Update the timer's state to running */
		Gpt_Global_Info.timer_state[Channel] = Gpt_Running;
	}else
	{
		/* Nothing to do here yet */
	}
}



/************************************************************************************
* Service Name: Gpt_StopTimer
* Service ID[hex]: 0x06
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel - The timer channel ID.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Stop the timer from counting.
************************************************************************************/
void Gpt_StopTimer( Gpt_ChannelType Channel )
{
	boolean error = FALSE;
	Gpt_ChannelType Gpt_Module;
    Gpt_ChannelType Gpt_SubModule;
    Gpt_ChannelConfigType* channel_temp_ptr = NULL_PTR;

    channel_temp_ptr = &channelconfig_ptr[Channel];
    Gpt_Module = get_GPT_MODULE(channel_temp_ptr->Timer_Id);
    Gpt_SubModule = get_GPT_SUBMODULE(channel_temp_ptr->Timer_Id);
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
/* 
 * Error Detection and reporting to Det Module is enabled by 
 * assigning STD_ON to GPT_DEV_ERROR_DETECT in Gpt_Cfg.h 
 */
#if (GPT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the module is not initialized */
	if (Gpt_Uninitialized == Gpt_Global_Info.timer_state[Channel])
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_STOP_TIMER_SID, GPT_E_UNINIT);
		error = TRUE;
	}else{/*Nothing to here*/}

	/* Chek if the channel configuration global variable is NULL */
	if(NULL_PTR == channelconfig_ptr)
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_STOP_TIMER_SID, GPT_E_PARAM_POINTER);
		error = TRUE;
	}else{/*Nothing to here*/}
		
	/* Chek if the channel id is valid */
	if(GPT_CONFIGURED_CHANNELS <= Channel)
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_STOP_TIMER_SID, GPT_E_PARAM_CHANNEL);
		error = TRUE;
	}else{/*Nothing to here*/}
#endif	
	/*
	 * Check if the module is not running
	 * Function Gpt_StopTimer will leave without reporting any DET errors
	 * According to GPT099 and GPT344 in AutoSAR requirements
	 */
	if (Gpt_Running != Gpt_Global_Info.timer_state[Channel])
	{
		error = TRUE;
	}else{/*Nothing to here*/}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/* In case there are no errors */
	if(FALSE == error)
	{
        switch(Gpt_SubModule)
        {
    /************************************************************************/
    /************************************************************************/
        case GPT_TIMER_AB: //Concatenated Timer Modules
        /* Stop Counting by clearing Timer A Enable */
            GPT(Gpt_Module)->CTL &= ~(1<<GPT_CTL_TAEN);
            if(Gpt_Module<6) //Normal 32 bits Timer
            {
                Gpt_Global_Info.Stopped_value[Channel] = GPT(Gpt_Module)->TAV;
            }
            else //Wide 64 bits Timer
            {
                Gpt_Global_Info.Stopped_value[Channel] = (GPT(Gpt_Module)->TAV) | ((Gpt_ValueType)(GPT(Gpt_Module)->TBV)<<32);
            }
            break;
    /************************************************************************/
    /************************************************************************/
        case GPT_TIMER_B: //Timer B
        /* Stop Counting by clearing Timer A Enable */
            GPT(Gpt_Module)->CTL &= ~(1<<GPT_CTL_TBEN);
            if((channel_temp_ptr->Timer_Width) == GPT_WIDTH_TIM_B_16BITS)
            { /* Normal or Wide Timer == No Prescaler */
                Gpt_Global_Info.Stopped_value[Channel] = GPT(Gpt_Module)->TBV;
            }else if((channel_temp_ptr->Timer_Width) == GPT_WIDTH_TIM_B_24BITS)
            { /* Normal 16 bits Timer B with 8 bits prescaler */
                Gpt_Global_Info.Stopped_value[Channel] = GPT(Gpt_Module)->TBV;
            }else if((channel_temp_ptr->Timer_Width) == GPT_WIDTH_WTIM_B_48BITS)
            { /* Wide 32 bits Timer B with 16 bits prescaler */
                Gpt_Global_Info.Stopped_value[Channel] = (GPT(Gpt_Module)->TBV) | ((Gpt_ValueType)(GPT(Gpt_Module)->TBPV)<<32);
            }
            break;
    /************************************************************************/
    /************************************************************************/
        case GPT_TIMER_A: //Timer A
        /* Stop Counting by clearing Timer A Enable */
            GPT(Gpt_Module)->CTL &= ~(1<<GPT_CTL_TAEN);
            if((channel_temp_ptr->Timer_Width) == GPT_WIDTH_TIM_A_16BITS)
            { /* Normal or Wide Timer == No Prescaler */
                Gpt_Global_Info.Stopped_value[Channel] = GPT(Gpt_Module)->TAV;
            }else if((channel_temp_ptr->Timer_Width) == GPT_WIDTH_TIM_A_24BITS)
            { /* Normal 16 bits Timer B with 8 bits prescaler */
                Gpt_Global_Info.Stopped_value[Channel] = GPT(Gpt_Module)->TAV;
            }else if((channel_temp_ptr->Timer_Width) == GPT_WIDTH_WTIM_A_48BITS)
            { /* Wide 32 bits Timer B with 16 bits prescaler */
                Gpt_Global_Info.Stopped_value[Channel] = (GPT(Gpt_Module)->TAV) | ((Gpt_ValueType)(GPT(Gpt_Module)->TAPV)<<32);
            }
            break;
    /************************************************************************/
    /************************************************************************/
        default:
            break;
        }
		/* Update the timer's state to stopped */
		Gpt_Global_Info.timer_state[Channel] = Gpt_Stopped;
	}else
	{
		/* Nothing to do here yet */
	}
}

/************************************************************************************
* Service Name: Gpt_EnableNotification
* Service ID[hex]: 0x07
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel - The timer channel ID.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Enable the interrupt notification for a channel (relevant in normal mode).
************************************************************************************/
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
void Gpt_EnableNotification( Gpt_ChannelType Channel )
{
	boolean error = FALSE;
	Gpt_ChannelType Gpt_Module;
    Gpt_ChannelType Gpt_SubModule;
    Gpt_ChannelConfigType* channel_temp_ptr = NULL_PTR;
    uint8 irq_num=0;
    channel_temp_ptr = &channelconfig_ptr[Channel];
    Gpt_Module = get_GPT_MODULE(channel_temp_ptr->Timer_Id);
    Gpt_SubModule = get_GPT_SUBMODULE(channel_temp_ptr->Timer_Id);
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
/* 
 * Error Detection and reporting to Det Module is enabled by 
 * assigning STD_ON to GPT_DEV_ERROR_DETECT in Gpt_Cfg.h 
 */
#if (GPT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the module is not initialized */
	if (Gpt_Uninitialized == Gpt_Global_Info.timer_state[Channel])
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ENABLE_NOTIFICATION_SID, GPT_E_UNINIT);
		error = TRUE;
	}else{/*Nothing to here*/}

	/* Chek if the channel configuration global variable is NULL */
	if(NULL_PTR == channelconfig_ptr)
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ENABLE_NOTIFICATION_SID, GPT_E_PARAM_POINTER);
		error = TRUE;
	}else{/*Nothing to here*/}
		
	/* Chek if the channel id is valid */
	if(GPT_CONFIGURED_CHANNELS <= Channel)
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ENABLE_NOTIFICATION_SID, GPT_E_PARAM_CHANNEL);
		error = TRUE;
	}else{/*Nothing to here*/}
		
	/* Chek if the notification function is valid */
	if(NULL_PTR == channelconfig_ptr[Channel].notification_func_ptr)
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ENABLE_NOTIFICATION_SID, GPT_E_PARAM_CHANNEL);
		error = TRUE;
	}else{/*Nothing to here*/}
#endif	
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/* In case there are no errors */
	if(FALSE == error)
	{
	    switch(Gpt_SubModule)
        {
    /************************************************************************/
    /************************************************************************/
        case GPT_TIMER_AB: //Concatenated Timer Modules
        /* Get the Irq Num from the LUT in Irq.h */
            irq_num = (Gpt_Module*2);
        /* Enable the TimeOut Interrupt in GPTMIMR */
            GPT(Gpt_Module)->IMR |= 1<<GPT_IMR_TATOIM;
        /* Enable the Global Interrupt to the appropriate IRQ number in the Vector Table */
            Gpt_NVICEnable(Gpt_IRQNumType[irq_num]);
            break;
    /************************************************************************/
    /************************************************************************/
        case GPT_TIMER_B: //Timer B
        /* Get the Irq Num from the LUT in Irq.h */
            irq_num = (Gpt_Module*2)+Gpt_SubModule;
        /* Enable the TimeOut Interrupt in GPTMIMR */
            GPT(Gpt_Module)->IMR |= 1<<GPT_IMR_TBTOIM;
        /* Enable the Global Interrupt to the appropriate IRQ number in the Vector Table */
            Gpt_NVICEnable(Gpt_IRQNumType[irq_num]);
            break;
    /************************************************************************/
    /************************************************************************/
        case GPT_TIMER_A: //Timer A
        /* Get the Irq Num from the LUT in Irq.h */
            irq_num = (Gpt_Module*2)+Gpt_SubModule;
        /* Enable the TimeOut Interrupt in GPTMIMR */
            GPT(Gpt_Module)->IMR |= 1<<GPT_IMR_TATOIM;
        /* Enable the Global Interrupt to the appropriate IRQ number in the Vector Table */
            Gpt_NVICEnable(Gpt_IRQNumType[irq_num]);
            break;
    /************************************************************************/
    /************************************************************************/
        default:
            break;
        }
		Gpt_Global_Info.channel_notification[Channel] = Gpt_Notification_Enabled;
	}else
	{
		/* Nothing to do here yet */
	}
}

/************************************************************************************
* Service Name: Gpt_DisableNotification
* Service ID[hex]: 0x08
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel - The timer chabnnel ID.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Disable the interrupt notification for a channel (relevant in normal mode).
************************************************************************************/
void Gpt_DisableNotification( Gpt_ChannelType Channel )
{
	boolean error = FALSE;
	Gpt_ChannelType Gpt_Module;
    Gpt_ChannelType Gpt_SubModule;
    Gpt_ChannelConfigType* channel_temp_ptr = NULL_PTR;
    uint8 irq_num=0;
    channel_temp_ptr = &channelconfig_ptr[Channel];
    Gpt_Module = get_GPT_MODULE(channel_temp_ptr->Timer_Id);
    Gpt_SubModule = get_GPT_SUBMODULE(channel_temp_ptr->Timer_Id);
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
/* 
 * Error Detection and reporting to Det Module is enabled by 
 * assigning STD_ON to GPT_DEV_ERROR_DETECT in Gpt_Cfg.h 
 */
#if (GPT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the module is not initialized */
	if (Gpt_Uninitialized == Gpt_Global_Info.timer_state[Channel])
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ENABLE_NOTIFICATION_SID, GPT_E_UNINIT);
		error = TRUE;
	}else{/*Nothing to here*/}

	/* Chek if the channel configuration global variable is NULL */
	if(NULL_PTR == channelconfig_ptr)
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ENABLE_NOTIFICATION_SID, GPT_E_PARAM_POINTER);
		error = TRUE;
	}else{/*Nothing to here*/}
		
	/* Chek if the channel id is valid */
	if(GPT_CONFIGURED_CHANNELS <= Channel)
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ENABLE_NOTIFICATION_SID, GPT_E_PARAM_CHANNEL);
		error = TRUE;
	}else{/*Nothing to here*/}
		
	/* Chek if the notification function is valid */
	if(NULL_PTR == channelconfig_ptr[Channel].notification_func_ptr)
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ENABLE_NOTIFICATION_SID, GPT_E_PARAM_CHANNEL);
		error = TRUE;
	}else{/*Nothing to here*/}
#endif	
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/* In case there are no errors */
	if(FALSE == error)
	{
        switch(Gpt_SubModule)
        {
    /************************************************************************/
    /************************************************************************/
        case GPT_TIMER_AB: //Concatenated Timer Modules
        /* Get the Irq Num from the LUT in Irq.h */
            irq_num = (Gpt_Module*2);
        /* Enable the Global Interrupt to the appropriate IRQ number in the Vector Table */
            Gpt_NVICDisable(Gpt_IRQNumType[irq_num]);
        /* Enable the TimeOut Interrupt in GPTMIMR */
            GPT(Gpt_Module)->IMR &= ~(1<<GPT_IMR_TATOIM);
            break;
    /************************************************************************/
    /************************************************************************/
        case GPT_TIMER_B: //Timer B
        /* Get the Irq Num from the LUT in Irq.h */
            irq_num = (Gpt_Module*2)+Gpt_SubModule;
        /* Enable the Global Interrupt to the appropriate IRQ number in the Vector Table */
            Gpt_NVICDisable(Gpt_IRQNumType[irq_num]);
        /* Enable the TimeOut Interrupt in GPTMIMR */
            GPT(Gpt_Module)->IMR &= ~(1<<GPT_IMR_TBTOIM);
            break;
    /************************************************************************/
    /************************************************************************/
        case GPT_TIMER_A: //Timer A
        /* Get the Irq Num from the LUT in Irq.h */
            irq_num = (Gpt_Module*2)+Gpt_SubModule;
        /* Enable the Global Interrupt to the appropriate IRQ number in the Vector Table */
            Gpt_NVICDisable(Gpt_IRQNumType[irq_num]);
        /* Enable the TimeOut Interrupt in GPTMIMR */
            GPT(Gpt_Module)->IMR &= ~(1<<GPT_IMR_TATOIM);
            break;
    /************************************************************************/
    /************************************************************************/
        default:
            break;
        }
		Gpt_Global_Info.channel_notification[Channel] = Gpt_Notification_Disabled;
	}else
	{
		/* Nothing to do here yet */
	}
}
#endif



/************************************************************************************
* Service Name: Gpt_SetMode
* Service ID[hex]: 0x09
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): Mode - Data type for the mode of the timer.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set the mode of the timer (GPT_MODE_NORMAL or GPT_MODE_SLEEP).
************************************************************************************/
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)

void Gpt_SetMode( Gpt_ModeType Mode )
{
	boolean error = FALSE;
	uint8 loop_index = 0;
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
/* 
 * Error Detection and reporting to Det Module is enabled by 
 * assigning STD_ON to GPT_DEV_ERROR_DETECT in Gpt_Cfg.h 
 */
#if (GPT_DEV_ERROR_DETECT == STD_ON)
	for(loop_index = 0;loop_index<GPT_CONFIGURED_CHANNELS;loop_index++)
	{
		/* Check if the module is not initialized */
		if (Gpt_Uninitialized == Gpt_Global_Info.timer_state[loop_index])
		{
			/* Report Parameter Error to the Det Module */
			Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SET_MODE_SID, GPT_E_UNINIT);
			error = TRUE;
		}else{/*Nothing to here*/}
	}

	/* Chek if the channel configuration global variable is NULL */
	if(NULL_PTR == channelconfig_ptr)
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SET_MODE_SID, GPT_E_PARAM_POINTER);
		error = TRUE;
	}else{/*Nothing to here*/}
		
	/* Chek if the channel id is valid */
	if((Mode != GPT_MODE_NORMAL) || (Mode != GPT_MODE_SLEEP))
	{
		/* Report Parameter Error to the Det Module */
		Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SET_MODE_SID, GPT_E_PARAM_MODE);
		error = TRUE;
	}else{/*Nothing to here*/}
		
#endif	
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/* In case there are no errors */
	if(FALSE == error)
	{
		if (GPT_MODE_NORMAL == Mode)
		{
			for(loop_index=0 ; loop_index<GPT_CONFIGURED_CHANNELS; loop_index++)
			{
				if (Gpt_Global_Info.channel_notification[loop_index] == Gpt_Notification_Enabled)
				{
					Gpt_EnableNotification(loop_index);
				} 
				else{/* Nothing to do here */}
			}
		}else if(GPT_MODE_SLEEP == Mode)
		{
			for(loop_index=0 ; loop_index<GPT_CONFIGURED_CHANNELS; loop_index++)
			{
				if (Gpt_Global_Info.timer_state[loop_index] == Gpt_Running)
				{
					Gpt_StopTimer(loop_index);
					Gpt_Global_Info.timer_state[loop_index] = Gpt_Stopped;
				}
				else{/* Nothing to do here */}
			}
		}else
		{
			/* Nothing to do here */
		}
	}else
	{
		/* Nothing to do here yet */
	}
}



/************************************************************************************
* Service Name: Gpt_DisableWakeup
* Service ID[hex]: 0x0A
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel - The timer channel ID.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Disable the wakeup interrupt of a channel (relevant in sleep mode).
************************************************************************************/
void Gpt_DisableWakeup( Gpt_ChannelType Channel )
{
	
}



/************************************************************************************
* Service Name: Gpt_EnableWakeup
* Service ID[hex]: 0x0B
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel - The timer channel ID.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Enable the wakeup interrupt of a channel (relevant in sleep mode).
************************************************************************************/
void Gpt_EnableWakeup( Gpt_ChannelType Channel )
{
	
}



/************************************************************************************
* Service Name: Gpt_CheckWakeup
* Service ID[hex]: 0x0C
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): WakeupSource - Information on wakeup source to be checked.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Check if a wakeup capable GPT channel is the source for a 
*              wakeup event and calls the ECU state manager service EcuM_SetWakeupEvent 
*              in case of a valid GPT channel wakeup event.
************************************************************************************/
#ifdef ECUM_H_
void Gpt_CheckWakeup( EcuM_WakeupSourceType WakeupSource )
{
	
}
#endif
#endif
#endif


/************************************************************************************/
/************************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% NON AUTOSAR FUNCTIONS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/************************************************************************************/
/************************************************************************************/

/************************************************************************************
* Service Name: Gpt_StateChange
* Service ID[hex]: 0xEE
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel - Id of the channel in the configuration struct.
*                  State   - The state of the channel to be changed
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Non AutoSAR Function to change the state of the channel in the Static Global Struct.
*              Specially used by another source files to change this static struct
************************************************************************************/
void Gpt_StateChange(Gpt_ChannelType Channel, Gpt_StateType State)
{
	Gpt_Global_Info.timer_state[Channel] = State;
}
