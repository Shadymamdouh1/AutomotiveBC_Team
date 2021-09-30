 /******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt_Irq.c
 *
 * Description: Source file for Gpt Module Interrupt Requests.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/


#include "Gpt_Irq.h"
#include "Gpt_Symbols.h"
#include "Gpt.h"

/*
 * Look Up Table for the IRQ numbers of the Timer modules in the NVIC table
 */
uint8 Gpt_IRQNumType[24] =
{
     19,  /* Gpt_IRQ_Timer0A */ /* Index 0 */
     20,  /* Gpt_IRQ_Timer0B */ /* Index 1 */
     21,  /* Gpt_IRQ_Timer1A */ /* Index 2 */
     22,  /* Gpt_IRQ_Timer1B */ /* Index 3 */
     23,  /* Gpt_IRQ_Timer2A */ /* Index 4 */
     24,  /* Gpt_IRQ_Timer2B */ /* Index 5 */
     35,  /* Gpt_IRQ_Timer3A */ /* Index 6 */
     36,  /* Gpt_IRQ_Timer3B */ /* Index 7 */
     70,  /* Gpt_IRQ_Timer4A */ /* Index 8 */
     71,  /* Gpt_IRQ_Timer4B */ /* Index 9 */
     92,  /* Gpt_IRQ_Timer5A */ /* Index 10 */
     93,  /* Gpt_IRQ_Timer5B */ /* Index 11 */
     94,  /* Gpt_IRQ_WTimer0A */ /* Index 12 */
     95,  /* Gpt_IRQ_WTimer0B */ /* Index 13 */
     96,  /* Gpt_IRQ_WTimer1A */ /* Index 14 */
     97,  /* Gpt_IRQ_WTimer1B */ /* Index 15 */
     98,  /* Gpt_IRQ_WTimer2A */ /* Index 16 */
     99,  /* Gpt_IRQ_WTimer2B */ /* Index 17 */
     100, /* Gpt_IRQ_WTimer3A */ /* Index 18 */
     101, /* Gpt_IRQ_WTimer3B */ /* Index 19 */
     102, /* Gpt_IRQ_WTimer4A */ /* Index 20 */
     103, /* Gpt_IRQ_WTimer4B */ /* Index 21 */
     104, /* Gpt_IRQ_WTimer5A */ /* Index 22 */
     105  /* Gpt_IRQ_WTimer5B */ /* Index 23 */
};

STATIC void Gpt_ISRHandler(Gpt_ChannelType Timer_id)
{
	uint8 loop_index=0;
	Gpt_ChannelType Channel = 0;
	/* Get the index of the channel in the configuration structure */
	for (loop_index=0 ; loop_index<GPT_CONFIGURED_CHANNELS ; loop_index++)
	{
		if(Timer_id == (Timers_Configurations.Timer_Channels[loop_index].Timer_Id))
		{
			Channel = loop_index;
		}else{/* Nothing to do here */}
	}

	GPT(Timer_id/10)->ICR |= 1<<((Timer_id%10)*8);
	/* Check if the channel is configured as OneShot mode */
	if (GPT_CH_MODE_ONESHOT == (Timers_Configurations.Timer_Channels[Channel].RunMode))
	{
		/* Change the state to expired */
		Gpt_StateChange(Channel, Gpt_Expired);
	}
	else{/* Nothing to do here yet */}

#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
/* Report wake up to ECUM */
		/*TODO*/
}
#endif
	/* CallBack the notification function */
	Timers_Configurations.Timer_Channels[Channel].notification_func_ptr();
}

 void Gpt_Timer0A_ISR(void){Gpt_ISRHandler(GPT_TIMER_0_A);}
 void Gpt_Timer0B_ISR(void){Gpt_ISRHandler(GPT_TIMER_0_B);}
 void Gpt_Timer1A_ISR(void){Gpt_ISRHandler(GPT_TIMER_1_A);}
 void Gpt_Timer1B_ISR(void){Gpt_ISRHandler(GPT_TIMER_1_B);}
 void Gpt_Timer2A_ISR(void){Gpt_ISRHandler(GPT_TIMER_2_A);}
 void Gpt_Timer2B_ISR(void){Gpt_ISRHandler(GPT_TIMER_2_B);}
 void Gpt_Timer3A_ISR(void){Gpt_ISRHandler(GPT_TIMER_3_A);}
 void Gpt_Timer3B_ISR(void){Gpt_ISRHandler(GPT_TIMER_3_B);}
 void Gpt_Timer4A_ISR(void){Gpt_ISRHandler(GPT_TIMER_4_A);}
 void Gpt_Timer4B_ISR(void){Gpt_ISRHandler(GPT_TIMER_4_B);}
 void Gpt_Timer5A_ISR(void){Gpt_ISRHandler(GPT_TIMER_5_A);}
 void Gpt_Timer5B_ISR(void){Gpt_ISRHandler(GPT_TIMER_5_B);}
 void Gpt_WTimer0A_ISR(void){Gpt_ISRHandler(GPT_WTIMER_0_A);}
 void Gpt_WTimer0B_ISR(void){Gpt_ISRHandler(GPT_WTIMER_0_B);}
 void Gpt_WTimer1A_ISR(void){Gpt_ISRHandler(GPT_WTIMER_1_A);}
 void Gpt_WTimer1B_ISR(void){Gpt_ISRHandler(GPT_WTIMER_1_B);}
 void Gpt_WTimer2A_ISR(void){Gpt_ISRHandler(GPT_WTIMER_2_A);}
 void Gpt_WTimer2B_ISR(void){Gpt_ISRHandler(GPT_WTIMER_2_B);}
 void Gpt_WTimer3A_ISR(void){Gpt_ISRHandler(GPT_WTIMER_3_A);}
 void Gpt_WTimer3B_ISR(void){Gpt_ISRHandler(GPT_WTIMER_3_B);}
 void Gpt_WTimer4A_ISR(void){Gpt_ISRHandler(GPT_WTIMER_4_A);}
 void Gpt_WTimer4B_ISR(void){Gpt_ISRHandler(GPT_WTIMER_4_B);}
 void Gpt_WTimer5A_ISR(void){Gpt_ISRHandler(GPT_WTIMER_5_A);}
 void Gpt_WTimer5B_ISR(void){Gpt_ISRHandler(GPT_WTIMER_5_B);}
