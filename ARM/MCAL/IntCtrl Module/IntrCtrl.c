/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  IntCtrl.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "IntCtrl.h"

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
#define INT_CTRL_APINT_VECKEY             (uint32)0x5FAUL
#define APINT_R                           AIRCR
#define NVIC_PRI_GROUPING_OFFSET          5U
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
static IntCtrl_GrpPrioSys_t SystemPriority_Grouping = 0;
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
static void IntDefaultHandler(void)
{
    while (1)
    {
    }
}
/*- GLOBAL STATIC VARIABLES
-------------------------------*/
pf_Vector old_Vectors[] = 
{
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler,
    IntDefaultHandler
};


/*- Function Definitions
-------------------------------*/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
Std_ReturnType IntCtrl_Init(void)
{
    Std_ReturnType ErrorStatus = E_OK;
    uint8 u8_loopCounter = 0;
    
    if(INT_CTRL_INTERRUPTS_USED == 0)
    {
        ErrorStatus = E_NOT_OK;
    }
    else
    {
    #if INT_CTRL_SYS_PRIO_TYPE > INT_CTRL_SYS_PRIO_TYPE_0_3      
        #error Invalid System Priority Grouping
    #endif 
        /* Set Priority System */
        if(IntCtrl_SetPrioritySystem(INT_CTRL_SYS_PRIO_TYPE) == E_NOT_OK)
        {
            ErrorStatus = E_NOT_OK;
        }
        else
        {
            for (u8_loopCounter = 0; u8_loopCounter < INT_CTRL_INTERRUPTS_USED; u8_loopCounter++)
            {   
                /* Set Priority */
                if(IntCtrl_SetPriority(IntCtrl_Configuartions[u8_loopCounter].IRQ_Num, 
                                    IntCtrl_Configuartions[u8_loopCounter].IRQ_Grp_Prio,
                                    IntCtrl_Configuartions[u8_loopCounter].IRQ_SubGrp_Prio) == E_NOT_OK)
                                    {
                                        ErrorStatus = E_NOT_OK;
                                    }
                /* Set inital state of the interrupt */
                if(IntCtrl_Configuartions[u8_loopCounter].IRQ_Initial == INT_CTRL_ENABLED)
                {
                    IntCtrl_EnableIRQ(IntCtrl_Configuartions[u8_loopCounter].IRQ_Num);
                }
                else if(IntCtrl_Configuartions[u8_loopCounter].IRQ_Initial == INT_CTRL_DISABLED)
                {
                    IntCtrl_DisableIRQ(IntCtrl_Configuartions[u8_loopCounter].IRQ_Num);
                }
                else
                {
                    ErrorStatus = E_NOT_OK;
                }
            }
        }
    }
    return ErrorStatus;
}

Std_ReturnType IntCtrl_EnableIRQ(IRQn_Type IRQ_Number)
{
    Std_ReturnType ErrorStatus = E_OK;
    uint8 RegIndex = 0;
    uint8 RegBitOffset = 0;
    if((IRQ_Number >= 0) && (IRQ_Number < INVALID_IRQn))
    {
        /* Calculate the Index of the register in the array */
        RegIndex = IRQ_Number >> 5;
        /* Calculate the offset of the bit inside the register */
        RegBitOffset = IRQ_Number & 0x1FUL;
        /* Enable the Interrupt in the EN register */
        NVIC->ISER[RegIndex] |= (uint32)(1 << RegBitOffset);
    }
    else
    {
        ErrorStatus = E_NOT_OK;
    }
    return ErrorStatus;
}

Std_ReturnType IntCtrl_DisableIRQ(IRQn_Type IRQ_Number)
{
    Std_ReturnType ErrorStatus = E_OK;
    uint8 RegIndex = 0;
    uint8 RegBitOffset = 0;
    if((IRQ_Number >= 0) && (IRQ_Number < INVALID_IRQn))
    {
        /* Calculate the Index of the register in the array */
        RegIndex = IRQ_Number >> 5;
        /* Calculate the offset of the bit inside the register */
        RegBitOffset = IRQ_Number & 0x1FUL;
        /* Clear the Interrupt in the DIS register */
        NVIC->ICER[RegIndex] |= (uint32)(1 << RegBitOffset);
    }
    else
    {
        ErrorStatus = E_NOT_OK;
    }
    return ErrorStatus;
}

Std_ReturnType IntCtrl_EnableGlobalInterrupts(void)
{
    NVIC->ISER[0] = 0xFFFFFFFFUL;
    NVIC->ISER[1] = 0xFFFFFFFFUL;
    NVIC->ISER[2] = 0xFFFFFFFFUL;
    NVIC->ISER[3] = 0xFFFFFFFFUL;
    NVIC->ISER[4] = 0xFFFFFFFFUL;
    return E_OK;
}

Std_ReturnType IntCtrl_DisableGlobalInterrupts(void)
{
    NVIC->ICER[0] = 0xFFFFFFFFUL;
    NVIC->ICER[1] = 0xFFFFFFFFUL;
    NVIC->ICER[2] = 0xFFFFFFFFUL;
    NVIC->ICER[3] = 0xFFFFFFFFUL;
    NVIC->ICER[4] = 0xFFFFFFFFUL;
    return E_OK;
}

Std_ReturnType IntCtrl_SetPriority(IRQn_Type IRQ_Number, IntCtrl_GrpPrio_t GrpPrio, IntCtrl_SubGrpPrio_t SubGrpPrio)
{
    Std_ReturnType ErrorStatus = E_OK;
    uint8 prioValue = 0;
    if((IRQ_Number >= 0) && (IRQ_Number < INVALID_IRQn))
    {
        /* Check for the priority configurations */
        switch (SystemPriority_Grouping)
        {
            case INT_CTRL_SYS_PRIO_TYPE_3_0:
            {
                /* Check if the Grp and SubGrp parameters are Invalid with the Grouping Settings */
                if( (GrpPrio > INT_CTRL_PRIORITY_GRP_7) 
                  ||(SubGrpPrio > INT_CTRL_PRIORITY_SUBGRP_0))
                {
                    ErrorStatus = E_NOT_OK;
                }
                else
                {
                    /* Set the Grp and SubGrp Priority */
                    prioValue = GrpPrio;
                    NVIC->IP[IRQ_Number] = prioValue << NVIC_PRI_GROUPING_OFFSET;
                }
                break;
            }
            case INT_CTRL_SYS_PRIO_TYPE_2_1:
            {
                /* Check if the Grp and SubGrp parameters are Invalid with the Grouping Settings */
                if( (GrpPrio > INT_CTRL_PRIORITY_GRP_3) 
                  ||(SubGrpPrio > INT_CTRL_PRIORITY_SUBGRP_1))
                {
                    ErrorStatus = E_NOT_OK;
                }
                else
                {
                    /* Set the Grp and SubGrp Priority */
                    prioValue = (GrpPrio << 1) | (SubGrpPrio);
                    NVIC->IP[IRQ_Number] = prioValue << NVIC_PRI_GROUPING_OFFSET;
                }
                break;
            }
            case INT_CTRL_SYS_PRIO_TYPE_1_2:
            {
                /* Check if the Grp and SubGrp parameters are Invalid with the Grouping Settings */
                if( (GrpPrio > INT_CTRL_PRIORITY_GRP_1) 
                  ||(SubGrpPrio > INT_CTRL_PRIORITY_SUBGRP_3))
                {
                    ErrorStatus = E_NOT_OK;
                }
                else
                {
                    /* Set the Grp and SubGrp Priority */
                    prioValue = (GrpPrio << 2) | (SubGrpPrio);
                    NVIC->IP[IRQ_Number] = prioValue << NVIC_PRI_GROUPING_OFFSET;
                }
                break;
            }
            case INT_CTRL_SYS_PRIO_TYPE_0_3:
            {
                /* Check if the Grp and SubGrp parameters are Invalid with the Grouping Settings */
                if( (GrpPrio > INT_CTRL_PRIORITY_GRP_0) 
                  ||(SubGrpPrio > INT_CTRL_PRIORITY_SUBGRP_7))
                {
                    ErrorStatus = E_NOT_OK;
                }
                else
                {
                    /* Set the Grp and SubGrp Priority */
                    prioValue = SubGrpPrio;
                    NVIC->IP[IRQ_Number] = prioValue << NVIC_PRI_GROUPING_OFFSET;
                }
                break;
            }
            default:
            {
                ErrorStatus = E_NOT_OK;
                break;
            }
        }
    }
    else
    {
        ErrorStatus = E_NOT_OK;
    }
    return ErrorStatus;
}

Std_ReturnType IntCtrl_SetPrioritySystem(IntCtrl_GrpPrioSys_t PrioSystem)
{
    Std_ReturnType ErrorStatus = E_OK;

    if(PrioSystem > INT_CTRL_SYS_PRIO_TYPE_0_3)
    {
        ErrorStatus = E_NOT_OK;
    }
    else
    {
        /* Set the global System priority variable to the new settings */
        SystemPriority_Grouping = PrioSystem;
        /* Set the register with the Veckey and the new prio group setting */
        SCB->AIRCR = (INT_CTRL_APINT_VECKEY << SCB_AIRCR_VECTKEY_Pos) | (PrioSystem << SCB_AIRCR_PRIGROUP_Pos);
    }
    return ErrorStatus;
}

Std_ReturnType Interrupt_install(uint8_t vectorId_u8, pf_Vector ISR_Callback)
{
    if((ISR_Callback != NULL_PTR) && (vectorId_u8 < INVALID_ID_vecID))
    {
        old_Vectors[vectorId_u8] = ISR_Callback;
    }
    else
    {
        return E_NOT_OK;
    }
    return E_OK;
}

Std_ReturnType Interrupt_deinstall(uint8_t vectorId_u8)
{
    if(vectorId_u8 < INVALID_ID_vecID)
    {
        old_Vectors[vectorId_u8] = IntDefaultHandler;
    }
    else
    {
        return E_NOT_OK;
    }
    return E_OK;
}


void GPIOPortA_IRQHandler(void){old_Vectors[0]();}
void GPIOPortB_IRQHandler(void){old_Vectors[1]();}
void GPIOPortC_IRQHandler(void){old_Vectors[2]();}
void GPIOPortD_IRQHandler(void){old_Vectors[3]();}
void GPIOPortE_IRQHandler(void){old_Vectors[4]();}
void UART0_IRQHandler(void){old_Vectors[5]();}
void UART1_IRQHandler(void){old_Vectors[6]();}
void SSI0_IRQHandler(void){old_Vectors[7]();}
void I2C0_IRQHandler(void){old_Vectors[8]();}
void PWMFault_IRQHandler(void){old_Vectors[9]();}
void PWMGen0_IRQHandler(void){old_Vectors[10]();}
void PWMGen1_IRQHandler(void){old_Vectors[11]();}
void PWMGen2_IRQHandler(void){old_Vectors[12]();}
void QEI0_IRQHandler(void){old_Vectors[13]();}
void ADCSeq0_IRQHandler(void){old_Vectors[14]();}
void ADCSeq1_IRQHandler(void){old_Vectors[15]();}
void ADCSeq2_IRQHandler(void){old_Vectors[16]();}
void ADCSeq3_IRQHandler(void){old_Vectors[17]();}
void Watchdog_IRQHandler(void){old_Vectors[18]();}
void Timer0A_IRQHandler(void){old_Vectors[19]();}
void Timer0B_IRQHandler(void){old_Vectors[20]();}
void Timer1A_IRQHandler(void){old_Vectors[21]();}
void Timer1B_IRQHandler(void){old_Vectors[22]();}
void Timer2A_IRQHandler(void){old_Vectors[23]();}
void Timer2B_IRQHandler(void){old_Vectors[24]();}
void Comp0_IRQHandler(void){old_Vectors[25]();}
void Comp1_IRQHandler(void){old_Vectors[26]();}
void Comp2_IRQHandler(void){old_Vectors[27]();}
void SysCtrl_IRQHandler(void){old_Vectors[28]();}
void FlashCtrl_IRQHandler(void){old_Vectors[29]();}
void GPIOPortF_IRQHandler(void){old_Vectors[30]();}
void GPIOPortG_IRQHandler(void){old_Vectors[31]();}
void GPIOPortH_IRQHandler(void){old_Vectors[32]();}
void UART2_IRQHandler(void){old_Vectors[33]();}
void SSI1_IRQHandler(void){old_Vectors[34]();}
void Timer3A_IRQHandler(void){old_Vectors[35]();}
void Timer3B_IRQHandler(void){old_Vectors[36]();}
void I2C1_IRQHandler(void){old_Vectors[37]();}
void QEI1_IRQHandler(void){old_Vectors[38]();}
void CAN0_IRQHandler(void){old_Vectors[39]();}
void CAN1_IRQHandler(void){old_Vectors[40]();}
void CAN2_IRQHandler(void){old_Vectors[41]();}
void Hibernate_IRQHandler(void){old_Vectors[42]();}
void USB0_IRQHandler(void){old_Vectors[43]();}
void PWMGen3_IRQHandler(void){old_Vectors[44]();}
void uDMAST_IRQHandler(void){old_Vectors[45]();}
void uDMAError_IRQHandler(void){old_Vectors[46]();}
void ADC1Seq0_IRQHandler(void){old_Vectors[47]();}
void ADC1Seq1_IRQHandler(void){old_Vectors[48]();}
void ADC1Seq2_IRQHandler(void){old_Vectors[49]();}
void ADC1Seq3_IRQHandler(void){old_Vectors[50]();}
void GPIOPortJ_IRQHandler(void){old_Vectors[51]();}
void GPIOPortK_IRQHandler(void){old_Vectors[52]();}
void GPIOPortL_IRQHandler(void){old_Vectors[53]();}
void SSI2_IRQHandler(void){old_Vectors[54]();}
void SSI3_IRQHandler(void){old_Vectors[55]();}
void UART3_IRQHandler(void){old_Vectors[56]();}
void UART4_IRQHandler(void){old_Vectors[57]();}
void UART5_IRQHandler(void){old_Vectors[58]();}
void UART6_IRQHandler(void){old_Vectors[59]();}
void UART7_IRQHandler(void){old_Vectors[60]();}
void I2C2_IRQHandler(void){old_Vectors[61]();}
void I2C3_IRQHandler(void){old_Vectors[62]();}
void Timer4A_IRQHandler(void){old_Vectors[63]();}
void Timer4B_IRQHandler(void){old_Vectors[64]();}
void Timer5A_IRQHandler(void){old_Vectors[65]();}
void Timer5B_IRQHandler(void){old_Vectors[66]();}
void WideTimer0A_IRQHandler(void){old_Vectors[67]();}
void WideTimer0B_IRQHandler(void){old_Vectors[68]();}
void WideTimer1A_IRQHandler(void){old_Vectors[69]();}
void WideTimer1B_IRQHandler(void){old_Vectors[70]();}
void WideTimer2A_IRQHandler(void){old_Vectors[71]();}
void WideTimer2B_IRQHandler(void){old_Vectors[72]();}
void WideTimer3A_IRQHandler(void){old_Vectors[73]();}
void WideTimer3B_IRQHandler(void){old_Vectors[74]();}
void WideTimer4A_IRQHandler(void){old_Vectors[75]();}
void WideTimer4B_IRQHandler(void){old_Vectors[76]();}
void WideTimer5A_IRQHandler(void){old_Vectors[77]();}
void WideTimer5B_IRQHandler(void){old_Vectors[78]();}
void FPU_IRQHandler(void){old_Vectors[79]();}
void I2C4_IRQHandler(void){old_Vectors[80]();}
void I2C5_IRQHandler(void){old_Vectors[81]();}
void GPIOPortM_IRQHandler(void){old_Vectors[82]();}
void GPIOPortN_IRQHandler(void){old_Vectors[83]();}
void QEI2_IRQHandler(void){old_Vectors[84]();}
void GPIOPortP0_IRQHandler(void){old_Vectors[85]();}
void GPIOPortP1_IRQHandler(void){old_Vectors[86]();}
void GPIOPortP2_IRQHandler(void){old_Vectors[87]();}
void GPIOPortP3_IRQHandler(void){old_Vectors[88]();}
void GPIOPortP4_IRQHandler(void){old_Vectors[89]();}
void GPIOPortP5_IRQHandler(void){old_Vectors[90]();}
void GPIOPortP6_IRQHandler(void){old_Vectors[91]();}
void GPIOPortP7_IRQHandler(void){old_Vectors[92]();}
void GPIOPortQ0_IRQHandler(void){old_Vectors[93]();}
void GPIOPortQ1_IRQHandler(void){old_Vectors[94]();}
void GPIOPortQ2_IRQHandler(void){old_Vectors[95]();}
void GPIOPortQ3_IRQHandler(void){old_Vectors[96]();}
void GPIOPortQ4_IRQHandler(void){old_Vectors[97]();}
void GPIOPortQ5_IRQHandler(void){old_Vectors[98]();}
void GPIOPortQ6_IRQHandler(void){old_Vectors[99]();}
void GPIOPortQ7_IRQHandler(void){old_Vectors[100]();}
void GPIOPortR_IRQHandler(void){old_Vectors[101]();}
void GPIOPortS_IRQHandler(void){old_Vectors[102]();}
void PWM1Gen0_IRQHandler(void){old_Vectors[103]();}
void PWM1Gen1_IRQHandler(void){old_Vectors[104]();}
void PWM1Gen2_IRQHandler(void){old_Vectors[105]();}
void PWM1Gen3_IRQHandler(void){old_Vectors[106]();}
void PWM1Fault_IRQHandler(void){old_Vectors[107]();}
