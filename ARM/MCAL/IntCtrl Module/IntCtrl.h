/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IntCtrl.h
 *       Module:  Interrupt Controller
 *
 *  Description:  These file holds the     
 *  
 *********************************************************************************************************************/

#ifndef INTCTRL_H_
#define INTCTRL_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "TM4C123GH6PM.h"
#include "Platform_Types.h"
#include "Std_Types.h"
#include "IntCtrl_Cfg.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


#define GPIOA_vecID                    0U
#define GPIOB_vecID                    1U
#define GPIOC_vecID                    2U
#define GPIOD_vecID                    3U
#define GPIOE_vecID                    4U
#define UART0_vecID                    5U
#define UART1_vecID                    6U
#define SSI0_vecID                     7U
#define I2C0_vecID                     8U
#define PWM0_FAULT_vecID               9U
#define PWM0_GEN0_vecID               10U
#define PWM0_GEN1_vecID               11U
#define PWM0_GEN2_vecID               12U
#define QEI0_vecID                    13U
#define ADC0_SEQ0_vecID               14U
#define ADC0_SEQ1_vecID               15U
#define ADC0_SEQ2_vecID               16U
#define ADC0_SEQ3_vecID               17U
#define WDT_vecID                     18U
#define TIMER0A_vecID                 19U
#define TIMER0B_vecID                 20U
#define TIMER1A_vecID                 21U
#define TIMER1B_vecID                 22U
#define TIMER2A_vecID                 23U
#define TIMER2B_vecID                 24U
#define ANALOG_COMP0_vecID            25U
#define ANALOG_COMP1_vecID            26U
#define ANALOG_COMP2_vecID            27U
#define SYSCTRL_vecID                 28U
#define FLSHCTRL_vecID                29U
#define GPIOF_vecID                   30U
#define GPIOG_vecID                   31U
#define GPIOH_vecID                   32U
#define UART2_vecID                   33U
#define SSI1_vecID                    34U
#define TIMER3A_vecID                 35U
#define TIMER3B_vecID                 36U
#define I2C1_vecID                    37U
#define QEI1_vecID                    38U
#define CAN0_vecID                    39U
#define CAN1_vecID                    40U
#define CAN2_vecID                    41U
#define HIBERNATE_vecID               42U
#define USB0_vecID                    43U
#define PWM0_GEN3_vecID               44U
#define uDMAST_vecID                  45U
#define uDMAERROR_vecID               46U
#define ADC1_SEQ0_vecID               47U
#define ADC1_SEQ1_vecID               48U
#define ADC1_SEQ2_vecID               49U
#define ADC1_SEQ3_vecID               50U
#define GPIOJ_vecID                   51U
#define GPIOK_vecID                   52U
#define GPIOL_vecID                   53U
#define SSI2_vecID                    54U
#define SSI2_vecIDs                    55U
#define UART3_vecID                   56U
#define UART4_vecID                   57U
#define UART5_vecID                   58U
#define UART6_vecID                   59U
#define UART7_vecID                   60U
#define I2C2_vecID                    61U
#define I2C3_vecID                    62U
#define TIMER4A_vecID                 63U
#define TIMER4B_vecID                 64U
#define TIMER5A_vecID                 65U
#define TIMER5B_vecID                 66U
#define WTIMER0A_vecID                67U
#define WTIMER0B_vecID                68U
#define WTIMER1A_vecID                69U
#define WTIMER1B_vecID                70U
#define WTIMER2A_vecID                71U
#define WTIMER2B_vecID                72U
#define WTIMER3A_vecID                73U
#define WTIMER3B_vecID                74U
#define WTIMER4A_vecID                75U
#define WTIMER4B_vecID                76U
#define WTIMER5A_vecID                77U
#define WTIMER5B_vecID                78U
#define FPU_vecID                     79U
#define I2C4_vecID                    80U
#define I2C5_vecID                    81U
#define GPIOM_vecID                   82U
#define GPION_vecID                   83U
#define QEI2_vecID                    84U
#define GPIOP0_vecID                  85U
#define GPIOP1_vecID                  86U
#define GPIOP2_vecID                  87U
#define GPIOP3_vecID                  88U
#define GPIOP4_vecID                  89U
#define GPIOP5_vecID                  90U
#define GPIOP6_vecID                  91U
#define GPIOP7_vecID                  92U
#define GPIOQ0_vecID                  93U
#define GPIOQ1_vecID                  94U
#define GPIOQ2_vecID                  95U
#define GPIOQ3_vecID                  96U
#define GPIOQ4_vecID                  97U
#define GPIOQ5_vecID                  98U
#define GPIOQ6_vecID                  99U
#define GPIOQ7_vecID                 100U
#define GPIOR_vecID                  101U
#define GPIOS_vecID                  102U
#define PWM1_GEN0_vecID              103U
#define PWM1_GEN1_vecID              104U
#define PWM1_GEN2_vecID              105U
#define PWM1_GEN2_vecIDs              106U
#define PWM1_FAULT_vecID             107U
#define INVALID_ID_vecID             108U

#define INT_CTRL_PRIORITY_GRP_0             0
#define INT_CTRL_PRIORITY_GRP_1             1
#define INT_CTRL_PRIORITY_GRP_2             2
#define INT_CTRL_PRIORITY_GRP_3             3
#define INT_CTRL_PRIORITY_GRP_4             4
#define INT_CTRL_PRIORITY_GRP_5             5
#define INT_CTRL_PRIORITY_GRP_6             6
#define INT_CTRL_PRIORITY_GRP_7             7

#define INT_CTRL_PRIORITY_SUBGRP_0          0
#define INT_CTRL_PRIORITY_SUBGRP_1          1
#define INT_CTRL_PRIORITY_SUBGRP_2          2
#define INT_CTRL_PRIORITY_SUBGRP_3          3
#define INT_CTRL_PRIORITY_SUBGRP_4          4
#define INT_CTRL_PRIORITY_SUBGRP_5          5
#define INT_CTRL_PRIORITY_SUBGRP_6          6
#define INT_CTRL_PRIORITY_SUBGRP_7          7


#define INT_CTRL_SYS_PRIO_TYPE_3_0            0x04U
#define INT_CTRL_SYS_PRIO_TYPE_2_1            0x05U
#define INT_CTRL_SYS_PRIO_TYPE_1_2            0x06U
#define INT_CTRL_SYS_PRIO_TYPE_0_3            0x07U

#define INT_CTRL_DISABLED                     0
#define INT_CTRL_ENABLED                      1

#define EXCP_MEM_FAULT_BIT_OFFSET             16U
#define EXCP_BUS_FAULT_BIT_OFFSET             17U
#define EXCP_USAGE_FAULT_BIT_OFFSET           18U

#define EXCP_USAGEPEND_FAULT_BIT_OFFSET           12U
#define EXCP_MEMPEND_FAULT_BIT_OFFSET             13U
#define EXCP_BUSPEND_FAULT_BIT_OFFSET             14U
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/* Enable Global Interrupts. */
#define Enable_GlobalInterrupts()\
     __asm(" CPSIE I");\
     __asm(" CPSIE F")

/* Disable Global Interrupts. */
#define Disable_GlobalInterrupts()\
         __asm(" CPSID I");\
         __asm(" CPSID F")

#define ExceptionFault_ForcePend(FAULT_ID)\
        SCB->SHCSR |= 1<<FAULT_ID

#define ExceptionFault_Enable(FAULT_ID)\
        SCB->SHCSR |= 1<<FAULT_ID

#define ExceptionFault_Disable(FAULT_ID)\
        SCB->SHCSR |= 1<<FAULT_ID

#define SCB_DIV0_TRAP_ENABLE()\
        SCB->CCR |= 1<<4

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


typedef void (*pf_Vector)(void);

/* Data Type for the Group Priority */
typedef uint8 IntCtrl_GrpPrio_t;

/* Data Type for the Sub Group Priority */
typedef uint8 IntCtrl_SubGrpPrio_t;

/* Data Type for the System Grouping Priority */
typedef uint8 IntCtrl_GrpPrioSys_t;

/* Data Type for the Initial State of the IRQ (ENABLED || DISABLED) */
typedef uint8 IntCtrl_InitState_t;

typedef struct
{
    IRQn_Type               IRQ_Num;            /* IRQ Num of the Interrupt Gate */
    IntCtrl_GrpPrio_t       IRQ_Grp_Prio;       /* IRQ Group Priority -- according to the priority grouping system */
    IntCtrl_SubGrpPrio_t    IRQ_SubGrp_Prio;    /* IRQ SubGroup Priority -- according to the priority grouping system */
    IntCtrl_InitState_t     IRQ_Initial;        /* IRQ Initial State (ENABLED || DISABLED) */
}IntCtrl_Config_t;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
extern const IntCtrl_Config_t IntCtrl_Configuartions[INT_CTRL_INTERRUPTS_USED];

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
Std_ReturnType IntCtrl_Init(void);
Std_ReturnType IntCtrl_EnableIRQ(IRQn_Type IRQ_Number);
Std_ReturnType IntCtrl_DisableIRQ(IRQn_Type IRQ_Number);
Std_ReturnType IntCtrl_EnableGlobalInterrupts(void);
Std_ReturnType IntCtrl_DisableGlobalInterrupts(void);
Std_ReturnType IntCtrl_SetPriority(IRQn_Type IRQ_Number, IntCtrl_GrpPrio_t GrpPrio, IntCtrl_SubGrpPrio_t SubGrpPrio);
Std_ReturnType IntCtrl_SetPrioritySystem(IntCtrl_GrpPrioSys_t PrioSystem);

/** Installing and Deinstalling Functions **/
Std_ReturnType Interrupt_install(uint8_t vectorId_u8, pf_Vector ISR_Callback);
Std_ReturnType Interrupt_deinstall(uint8_t vectorId_u8);


#endif /* INTCTRL_H_ */

