/*
 * timerISR.c
 *
 *  Created on: 
 *      Author: 
 */
#include "System.h"
#include "alt_types.h"
#include "HexDisplay.h"
#include "io.h"

/*****************************************************************************
 * Interval timer interrupt service routine
 *
 *
******************************************************************************/
#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
void timerISR(void* context)
#else
void timerISR(void * context, alt_u32 id)
#endif
{
	/* Cast context. It is important that this be declared
	 * volatile to avoid unwanted compiler optimization.
	 */
	//volatile int* interval_timer_ptr =(int*)INTERVAL_TIMER_BASE;
	alt_u32*pCount = (alt_u32*)context;


	/* clear the interrupt */
	IOWR(INTERVAL_TIMER_BASE,0, 1); //push anything -> resets

	/* Act upon the interrupt */
	*pCount = *pCount +1; //adding one to the value at pCount
	/* Display count value 
	 * (Is this the best place to do this? 
	 * Why or why not?) 
	 */
	HexDisplay((alt_u32*)HEX3_HEX0_BASE, *pCount);

	return;
}



