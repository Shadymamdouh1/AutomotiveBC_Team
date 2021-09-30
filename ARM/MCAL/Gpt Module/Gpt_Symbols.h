 /******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt_Symbols.h
 *
 * Description: Header file for Gpt Module Symbols.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/


#ifndef GPT_SYMBOLS_H_
#define GPT_SYMBOLS_H_

/* GPT TIMER IDs */
#define GPT_TIMER_0		(0U)
#define GPT_TIMER_1		(1U)
#define GPT_TIMER_2		(2U)
#define GPT_TIMER_3     (3U)
#define GPT_TIMER_4     (4U)
#define GPT_TIMER_5     (5U)

#define GPT_WTIMER_0     (6U)
#define GPT_WTIMER_1     (7U)
#define GPT_WTIMER_2     (8U)
#define GPT_WTIMER_3     (9U)
#define GPT_WTIMER_4     (10U)
#define GPT_WTIMER_5     (11U)

#define GPT_TIMER_A     (0U)
#define GPT_TIMER_B     (1U)
#define GPT_TIMER_AB    (2U)
/**********************************************************************/
/*         Symbols for Gpt_ChannelType Data Type                      *
 * The unit value refers to the Timer submodule A or B or Concatenated
 * 0 >> A
 * 1 >> B
 * 2 >> A concatenated with B
 * The rest of the number is for the index of the Timer Module
 * in the register map
 * example: GPT_TIMER_3_AB has the value of (32)
 *          (3) >> Timer Module with index 3 in the array of register map
 *          (2) >> A and B concatenated together to form 32 bits timer
 * example: GPT_WTIMER_5_A has the value of (110)
 *          (11) >> Timer Module with index 11 in the array of register map
 *          (0)  >> SubModule Wide Timer A of width 32 bits
 * example: GPT_TIMER_4_B has the value of (41)
 *          (4) >> Timer Module with index 4 in the array of register map
 *          (1) >> SubModule Timer A of width 16 bits
 */
/**********************************************************************/
/*
 * 16 bits Timer Modules
 */
#define GPT_TIMER_0_A     (0U)
#define GPT_TIMER_0_B     (1U)

#define GPT_TIMER_1_A     (10U)
#define GPT_TIMER_1_B     (11U)

#define GPT_TIMER_2_A     (20U)
#define GPT_TIMER_2_B     (21U)

#define GPT_TIMER_3_A     (30U)
#define GPT_TIMER_3_B     (31U)

#define GPT_TIMER_4_A     (40U)
#define GPT_TIMER_4_B     (41U)

#define GPT_TIMER_5_A     (50U)
#define GPT_TIMER_5_B     (51U)


/*
 * Concatenated 32 bits Timer Modules
 */
#define GPT_TIMER_0_AB    (2U)
#define GPT_TIMER_1_AB    (12U)
#define GPT_TIMER_2_AB    (22U)
#define GPT_TIMER_3_AB    (32U)
#define GPT_TIMER_4_AB    (42U)
#define GPT_TIMER_5_AB    (52U)

/*
 * 32 bits Timer Modules
 */
#define GPT_WTIMER_0_A    (60U)
#define GPT_WTIMER_0_B    (61U)

#define GPT_WTIMER_1_A    (70U)
#define GPT_WTIMER_1_B    (71U)

#define GPT_WTIMER_2_A    (80U)
#define GPT_WTIMER_2_B    (81U)

#define GPT_WTIMER_3_A    (90U)
#define GPT_WTIMER_3_B    (91U)

#define GPT_WTIMER_4_A    (100U)
#define GPT_WTIMER_4_B    (101U)

#define GPT_WTIMER_5_A    (110U)
#define GPT_WTIMER_5_B    (111U)


/*
 * Concatenated 64 bits Timer Modules
 */
#define GPT_WTIMER_0_AB     (62U)
#define GPT_WTIMER_1_AB     (72U)
#define GPT_WTIMER_2_AB     (82U)
#define GPT_WTIMER_3_AB     (92U)
#define GPT_WTIMER_4_AB     (102U)
#define GPT_WTIMER_5_AB     (112U)

/*
 * GPT Width Symbols
 */
/* Symbols for Individual Timer A Width */
#define GPT_WIDTH_TIM_A_16BITS   (0U) //Normal Timer A 16 bits width
#define GPT_WIDTH_TIM_A_24BITS   (8U) //Timer A 16 bits concatenated with 8 bits prescaler

#define GPT_WIDTH_TIM_B_16BITS   (0U) //Normal Timer B 16 bits width
#define GPT_WIDTH_TIM_B_24BITS   (8U) //Timer B 16 bits concatenated with 8 bits prescaler

#define GPT_WIDTH_TIM_AB_32BITS  (32U)//Concatenated Timer A and B >>Prescaler is not used  for this mode<<

#define GPT_WIDTH_WTIM_A_32BITS  (1U) //Wide Timer A 32 bits width
#define GPT_WIDTH_WTIM_A_48BITS  (16U) //Wide Timer A 32 bits concatenated with 16 bits prescaler

#define GPT_WIDTH_WTIM_B_32BITS  (1U) //Wide Timer B 32 bits width
#define GPT_WIDTH_WTIM_B_48BITS  (16U) //Wide Timer B 32 bits concatenated with 16 bits prescaler

#define GPT_WIDTH_WTIM_AB_64BITS (64U)//Concatenated Wide Timer A and B >>Prescaler is not used  for this mode<<

/*
 * GPTMCFG Register Symbols
 */
#define GPT_CFG_CONCATENATED   0x00
#define GPT_CFG_INDIVIDUAL     0x04

/*
 * GPTMCTL Register Symbols
 */
#define GPT_CTL_TAEN        0U
#define GPT_CTL_TASTALL     1U
#define GPT_CTL_TBEN        8U
#define GPT_CTL_TBSTALL     9U

/*
 * GPTMTAMR Register Symbols
 */
#define GPT_TAMR_TAILD      8U
#define GPT_TAMR_TACDIR     4U
#define GPT_TAMR_TAMR       0U

/*
 * GPTMTBMR Register Symbols
 */
#define GPT_TBMR_TBILD      8U
#define GPT_TBMR_TBCDIR     4U
#define GPT_TBMR_TBMR       0U

/*
 * GPTMIMR Register Symbols
 */
#define GPT_IMR_TATOIM      0U
#define GPT_IMR_TBTOIM      8U

/*
 * GPTMICR Register Symbols
 */
#define GPT_ICR_TATOCINT    0U
#define GPT_ICR_TBTOCINT    8U

#endif



















