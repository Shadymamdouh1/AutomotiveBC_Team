/*
 * Delay.c
 *
 * Created: 7/24/2021 11:03:45 AM
 *  Author: Mohamed Magdy
 */ 
#include "Delay.h"


void Delay_us(uint64 u64_time_us)
{

}
void Delay_ms(uint64 u64_time_ms)
{
	uint64 i,j;
	for (i=0;i<u64_time_ms;i++) // this is For(); loop delay used to define delay value in Embedded C
	{
		for (j=0;j<DELAY_MS_ITERATION;j++);
	}
}
void Delay_s(uint32 u32_time_s)
{
}

