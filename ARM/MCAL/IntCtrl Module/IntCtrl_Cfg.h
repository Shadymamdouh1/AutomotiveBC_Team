/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IntCtrl_Cfg.h
 *       Module:  Interrupt Controller
 *
 *  Description:  These file holds the configuration for the Interrupt Controller    
 *  
 *********************************************************************************************************************/
#ifndef INTCTRL_CFG_H
#define INTCTRL_CFG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*
 * Number of Interrupts used 
 */
#define INT_CTRL_INTERRUPTS_USED            1U

/*
 * System Priority Grouping
 */
#define INT_CTRL_SYS_PRIO_TYPE              INT_CTRL_SYS_PRIO_TYPE_3_0

/*
 * Assign STD_ON on the interrupt handlers used
 */ 
#define GPIOA_ISR_ENABLE                    STD_OFF
#define GPIOB_ISR_ENABLE                    STD_OFF
#define GPIOC_ISR_ENABLE                    STD_OFF
#define GPIOD_ISR_ENABLE                    STD_OFF
#define GPIOE_ISR_ENABLE                    STD_OFF
#define UART0_ISR_ENABLE                    STD_OFF
#define UART1_ISR_ENABLE                    STD_OFF
#define SSI0_ISR_ENABLE                     STD_OFF
#define I2C0_ISR_ENABLE                     STD_OFF
#define PWM0_FAULT_ISR_ENABLE               STD_OFF
#define PWM0_GEN0_ISR_ENABLE                STD_OFF
#define PWM0_GEN1_ISR_ENABLE                STD_OFF
#define PWM0_GEN2_ISR_ENABLE                STD_OFF
#define QEI0_ISR_ENABLE                     STD_OFF
#define ADC0_SEQ0_ISR_ENABLE                STD_OFF
#define ADC0_SEQ1_ISR_ENABLE                STD_OFF
#define ADC0_SEQ2_ISR_ENABLE                STD_OFF
#define ADC0_SEQ3_ISR_ENABLE                STD_OFF
#define WDT_ISR_ENABLE                      STD_OFF
#define TIMER0A_ISR_ENABLE                  STD_OFF
#define TIMER0B_ISR_ENABLE                  STD_OFF
#define TIMER1A_ISR_ENABLE                  STD_OFF
#define TIMER1B_ISR_ENABLE                  STD_OFF
#define TIMER2A_ISR_ENABLE                  STD_OFF
#define TIMER2B_ISR_ENABLE                  STD_OFF
#define ANALOG_COMP0_ISR_ENABLE             STD_OFF
#define ANALOG_COMP1_ISR_ENABLE             STD_OFF
#define ANALOG_COMP2_ISR_ENABLE             STD_OFF
#define SYSCTRL_ISR_ENABLE                  STD_OFF
#define FLSHCTRL_ISR_ENABLE                 STD_OFF
#define GPIOF_ISR_ENABLE                    STD_OFF
#define GPIOG_ISR_ENABLE                    STD_OFF
#define GPIOH_ISR_ENABLE                    STD_OFF
#define UART2_ISR_ENABLE                    STD_OFF
#define SSI1_ISR_ENABLE                     STD_OFF
#define TIMER3A_ISR_ENABLE                  STD_OFF
#define TIMER3B_ISR_ENABLE                  STD_OFF
#define I2C1_ISR_ENABLE                     STD_OFF
#define QEI1_ISR_ENABLE                     STD_OFF
#define CAN0_ISR_ENABLE                     STD_OFF
#define CAN1_ISR_ENABLE                     STD_OFF
#define CAN2_ISR_ENABLE                     STD_OFF
#define HIBERNATE_ISR_ENABLE                STD_OFF
#define USB0_ISR_ENABLE                     STD_OFF
#define PWM0_GEN3_ISR_ENABLE                STD_OFF
#define uDMAST_ISR_ENABLE                   STD_OFF
#define uDMAERROR_ISR_ENABLE                STD_OFF
#define ADC1_SEQ0_ISR_ENABLE                STD_OFF
#define ADC1_SEQ1_ISR_ENABLE                STD_OFF
#define ADC1_SEQ2_ISR_ENABLE                STD_OFF
#define ADC1_SEQ3_ISR_ENABLE                STD_OFF
#define GPIOJ_ISR_ENABLE                    STD_OFF
#define GPIOK_ISR_ENABLE                    STD_OFF
#define GPIOL_ISR_ENABLE                    STD_OFF
#define SSI2_ISR_ENABLE                     STD_OFF
#define SSI2_ISR_ENABLE                     STD_OFF
#define UART3_ISR_ENABLE                    STD_OFF
#define UART4_ISR_ENABLE                    STD_OFF
#define UART5_ISR_ENABLE                    STD_OFF
#define UART6_ISR_ENABLE                    STD_OFF
#define UART7_ISR_ENABLE                    STD_OFF
#define I2C2_ISR_ENABLE                     STD_OFF
#define I2C3_ISR_ENABLE                     STD_OFF
#define TIMER4A_ISR_ENABLE                  STD_OFF
#define TIMER4B_ISR_ENABLE                  STD_OFF
#define TIMER5A_ISR_ENABLE                  STD_OFF
#define TIMER5B_ISR_ENABLE                  STD_OFF
#define WTIMER0A_ISR_ENABLE                 STD_OFF
#define WTIMER0B_ISR_ENABLE                 STD_OFF
#define WTIMER1A_ISR_ENABLE                 STD_OFF
#define WTIMER1B_ISR_ENABLE                 STD_OFF
#define WTIMER2A_ISR_ENABLE                 STD_OFF
#define WTIMER2B_ISR_ENABLE                 STD_OFF
#define WTIMER3A_ISR_ENABLE                 STD_OFF
#define WTIMER3B_ISR_ENABLE                 STD_OFF
#define WTIMER4A_ISR_ENABLE                 STD_OFF
#define WTIMER4B_ISR_ENABLE                 STD_OFF
#define WTIMER5A_ISR_ENABLE                 STD_OFF
#define WTIMER5B_ISR_ENABLE                 STD_OFF
#define FPU_ISR_ENABLE                      STD_OFF
#define I2C4_ISR_ENABLE                     STD_OFF
#define I2C5_ISR_ENABLE                     STD_OFF
#define GPIOM_ISR_ENABLE                    STD_OFF
#define GPION_ISR_ENABLE                    STD_OFF
#define QEI2_ISR_ENABLE                     STD_OFF
#define GPIOP0_ISR_ENABLE                   STD_OFF
#define GPIOP1_ISR_ENABLE                   STD_OFF
#define GPIOP2_ISR_ENABLE                   STD_OFF
#define GPIOP3_ISR_ENABLE                   STD_OFF
#define GPIOP4_ISR_ENABLE                   STD_OFF
#define GPIOP5_ISR_ENABLE                   STD_OFF
#define GPIOP6_ISR_ENABLE                   STD_OFF
#define GPIOP7_ISR_ENABLE                   STD_OFF
#define GPIOQ0_ISR_ENABLE                   STD_OFF
#define GPIOQ1_ISR_ENABLE                   STD_OFF
#define GPIOQ2_ISR_ENABLE                   STD_OFF
#define GPIOQ3_ISR_ENABLE                   STD_OFF
#define GPIOQ4_ISR_ENABLE                   STD_OFF
#define GPIOQ5_ISR_ENABLE                   STD_OFF
#define GPIOQ6_ISR_ENABLE                   STD_OFF
#define GPIOQ7_ISR_ENABLE                   STD_OFF
#define GPIOR_ISR_ENABLE                    STD_OFF
#define GPIOS_ISR_ENABLE                    STD_OFF
#define PWM1_GEN0_ISR_ENABLE                STD_OFF
#define PWM1_GEN1_ISR_ENABLE                STD_OFF
#define PWM1_GEN2_ISR_ENABLE                STD_OFF
#define PWM1_GEN2_ISR_ENABLE                STD_OFF
#define PWM1_FAULT_ISR_ENABLE               STD_OFF
#endif  /* INTCTRL_CFG_H */
