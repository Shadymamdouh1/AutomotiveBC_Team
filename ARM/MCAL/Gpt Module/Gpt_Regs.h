 /******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt_Regs.h
 *
 * Description: Header file for Gpt Module Registers.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/


#ifndef GPT_REGS_H_
#define GPT_REGS_H_

#include "Std_Types.h"
#include "Gpt_Symbols.h"

#define     __I     volatile const       /*!< Defines 'read only' permissions                 */
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */


#define NVIC_EN0_R              (*((volatile uint32 *)0xE000E100))
#define NVIC_EN1_R              (*((volatile uint32 *)0xE000E104))
#define NVIC_EN2_R              (*((volatile uint32 *)0xE000E108))
#define NVIC_EN3_R              (*((volatile uint32 *)0xE000E10C))
#define NVIC_EN4_R              (*((volatile uint32 *)0xE000E110))

#define SYSCTL_RCGCTIMER_R      (*((volatile uint32 *)0x400FE604))
#define SYSCTL_RCGCWTIMER_R     (*((volatile uint32 *)0x400FE65C))

#define GPTs_NUM        12U

#define GPT_TIMER0_BASE_ADDRESS            0x40030000U
#define GPT_TIMER1_BASE_ADDRESS            0x40031000U
#define GPT_TIMER2_BASE_ADDRESS            0x40032000U
#define GPT_TIMER3_BASE_ADDRESS            0x40033000U
#define GPT_TIMER4_BASE_ADDRESS            0x40034000U
#define GPT_TIMER5_BASE_ADDRESS            0x40035000U

#define GPT_WTIMER0_BASE_ADDRESS           0x40036000U
#define GPT_WTIMER1_BASE_ADDRESS           0x40037000U
#define GPT_WTIMER2_BASE_ADDRESS           0x4004C000U
#define GPT_WTIMER3_BASE_ADDRESS           0x4004D000U
#define GPT_WTIMER4_BASE_ADDRESS           0x4004E000U
#define GPT_WTIMER5_BASE_ADDRESS           0x4004F000U

static uint32 GPT_BaseAddressLut[GPTs_NUM] =
{   GPT_TIMER0_BASE_ADDRESS,
    GPT_TIMER1_BASE_ADDRESS,
    GPT_TIMER2_BASE_ADDRESS,
    GPT_TIMER3_BASE_ADDRESS,
    GPT_TIMER4_BASE_ADDRESS,
    GPT_TIMER5_BASE_ADDRESS,
    GPT_WTIMER0_BASE_ADDRESS,
    GPT_WTIMER1_BASE_ADDRESS,
    GPT_WTIMER2_BASE_ADDRESS,
    GPT_WTIMER3_BASE_ADDRESS,
    GPT_WTIMER4_BASE_ADDRESS,
    GPT_WTIMER5_BASE_ADDRESS
};
typedef struct {                                    /*!< TIMER0 Structure                                                      */
  __IO uint32  CFG;                               /*!< GPTM Configuration                                                    */
  __IO uint32  TAMR;                              /*!< GPTM Timer A Mode                                                     */
  __IO uint32  TBMR;                              /*!< GPTM Timer B Mode                                                     */
  __IO uint32  CTL;                               /*!< GPTM Control                                                          */
  __IO uint32  SYNC;                              /*!< GPTM Synchronize                                                      */
  __I  uint32  RESERVED0;
  __IO uint32  IMR;                               /*!< GPTM Interrupt Mask                                                   */
  __IO uint32  RIS;                               /*!< GPTM Raw Interrupt Status                                             */
  __IO uint32  MIS;                               /*!< GPTM Masked Interrupt Status                                          */
  __O  uint32  ICR;                               /*!< GPTM Interrupt Clear                                                  */
  __IO uint32  TAILR;                             /*!< GPTM Timer A Interval Load                                            */
  __IO uint32  TBILR;                             /*!< GPTM Timer B Interval Load                                            */
  __IO uint32  TAMATCHR;                          /*!< GPTM Timer A Match                                                    */
  __IO uint32  TBMATCHR;                          /*!< GPTM Timer B Match                                                    */
  __IO uint32  TAPR;                              /*!< GPTM Timer A Prescale                                                 */
  __IO uint32  TBPR;                              /*!< GPTM Timer B Prescale                                                 */
  __IO uint32  TAPMR;                             /*!< GPTM TimerA Prescale Match                                            */
  __IO uint32  TBPMR;                             /*!< GPTM TimerB Prescale Match                                            */
  __I  uint32  TAR;                               /*!< GPTM Timer A                                                          */
  __I  uint32  TBR;                               /*!< GPTM Timer B                                                          */
  __IO uint32  TAV;                               /*!< GPTM Timer A Value                                                    */
  __IO uint32  TBV;                               /*!< GPTM Timer B Value                                                    */
  __IO uint32  RTCPD;                             /*!< GPTM RTC Predivide                                                    */
  __IO uint32  TAPS;                              /*!< GPTM Timer A Prescale Snapshot                                        */
  __IO uint32  TBPS;                              /*!< GPTM Timer B Prescale Snapshot                                        */
  __I  uint32  TAPV;                              /*!< GPTM Timer A Prescale Value                                           */
  __I  uint32  TBPV;                              /*!< GPTM Timer B Prescale Value                                           */
  __I  uint32  RESERVED1[981];
  __IO uint32  PP;                                /*!< GPTM Peripheral Properties                                            */
} Gpt_MapType;

#define GPT(ID)    ((Gpt_MapType*)GPT_BaseAddressLut[ID])

#define GPT_TIMER0_MAP      GPT(GPT_TIMER_0)
#define GPT_TIMER1_MAP      GPT(GPT_TIMER_1)
#define GPT_TIMER2_MAP      GPT(GPT_TIMER_2)
#define GPT_TIMER3_MAP      GPT(GPT_TIMER_3)
#define GPT_TIMER4_MAP      GPT(GPT_TIMER_4)
#define GPT_TIMER5_MAP      GPT(GPT_TIMER_5)

#define GPT_WTIMER0_MAP      GPT(GPT_WTIMER_0)
#define GPT_WTIMER1_MAP      GPT(GPT_WTIMER_1)
#define GPT_WTIMER2_MAP      GPT(GPT_WTIMER_2)
#define GPT_WTIMER3_MAP      GPT(GPT_WTIMER_3)
#define GPT_WTIMER4_MAP      GPT(GPT_WTIMER_4)
#define GPT_WTIMER5_MAP      GPT(GPT_WTIMER_5)

#endif /* GPT_REGS_H_ */
