
#include "io.h"
#include "system.h"
#include "alt_types.h"
#include "sys/alt_irq.h"
#include "timerISR.h"
#include "buttonISR.h"

/*******************************************************************************
 /*int main()                                                                  *
 *                                                                             *
 ******************************************************************************/
volatile alt_u8 display_as_bcd;

int main(void)
{ 
    /* Setup */
	display_as_bcd = 1;
//volatile int *interval_timer_ptr = (int*) INTERVAL_TIMER_BASE; // pointer of interval timer base as int
//olatile int *KEY_ptr = (int*) PUSHBUTTONS_BASE;				//volatile because the system will change it, tells the system not to make it const
//static int counter = 0x2faf080; // this value will make it count in seconds 1/(50MHz) x 0x2faf080 = 1 second

alt_u32 *pCount;
static alt_u32 count = 0; //declare this variable once
pCount = &count;//pCount = the value at count(which is zero)


/* Initialize Variables */


/* Register ISRs */
alt_irq_register(PUSHBUTTONS_IRQ,(void*) pCount , buttonISR);
alt_irq_register(INTERVAL_TIMER_IRQ, (void*) pCount, timerISR);//register interrupt handler for timer
															  //void * because in another program it might be a different type and this will bypass compiler type check


/* Initialize Timer */
//Setup start value
IOWR(INTERVAL_TIMER_BASE, 2, 0xFFFF&INTERVAL_TIMER_FREQ); // and with FFFF to get first 16 bits
IOWR(INTERVAL_TIMER_BASE, 3, 0xFFFF&(INTERVAL_TIMER_FREQ >>16)); //shift 16 bits to the right and and with FFF(not necessary)


//Start the timer
IOWR(INTERVAL_TIMER_BASE, 1, 0x7); // 0x7 = 111 start=1 continuous=1 ito=1
IOWR(PUSHBUTTONS_BASE, 2, 0xE); //write to interrupt mask register
								// E= 1110b masks because the first register is a reset
//IOWR(INTERVAL,1,?); //stop = 0, Start = 1, count = 1


    /* Loop while processing interrupts */
    while( 1 ) 
    {

    }
    return 0; // should never get here
}
