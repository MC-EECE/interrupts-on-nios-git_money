/*
 * buttonISR.c
 *
 *  Created on: 
 *      Author: 
 */

#include "buttonISR.h"
#include "altera_avalon_pio_regs.h"
#include "lcd.h"
#include "alt_types.h"

#include "HexDisplay.h"

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
void buttonISR(void* context)
#else
void buttonISR(void* context, alt_u32 id)
#endif
{
    /* Cast context It is important that this be declared 
     * volatile to avoid unwanted compiler optimization.
     */
	alt_u8 edgeCapture = IORD(PUSHBUTTONS_BASE,3);
	alt_u8 format_display;

	//alt_u8 edgeCapture = *(PUSHBUTTONS_BASE +3)&0xE;

    /* Store the value in the PUSHBUTTONS's edge capture register in *context. */

	volatile alt_u32*pCount = (alt_u32*)context;
	alt_u8 controlRegisterValue;

    /* Reset the PUSHBUTTONS's edge capture register. */
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE, 0);



    /* Act upon the interrupt */
 switch(edgeCapture)
 {
			//key 1 = starts or stops counter
 case 2:
			//alt_u32 *controlRegister = *(INTERVAL_TIMER_BASE+ 1);
			//alt_u32 controlRegisterValue = (*controlRegister)&0xC;
	 	 	 controlRegisterValue = IORD(INTERVAL_TIMER_BASE,1);
			if(controlRegisterValue == 0xB)
				{
				IOWR(INTERVAL_TIMER_BASE, 1, 0x7);
				LCD_cursor(0,0);
				LCD_text("Running...        ");
				}
			else
				{
				IOWR(INTERVAL_TIMER_BASE, 1, 0xB);	//if it is stooped we start it, and if it is  started we stop
				LCD_cursor(0,0);
				LCD_text("PAUSED            ");
				}
			//IOWR(INTERVAL_TIMER_BASE, 1, 0x7); // 0x7 = 111 start=1 continuous=1 ito=1
		break;
 case 4: //key 2 = sets count to zero

			*pCount = 0;
			HexDisplay((alt_u32*)HEX3_HEX0_BASE, *pCount);
			LCD_cursor(0,0);
			LCD_text("Count Reset...        ");
		break;
 case 8:  //key 3, flip display
			format_display = bcd_hex_flip();
			HexDisplay((alt_u32*)HEX3_HEX0_BASE, *pCount);
			if(format_display)
			{
				LCD_cursor(0,0);
				LCD_text("BCD            ");
			}
			else
			{
				LCD_cursor(0,0);
				LCD_text("HEX            ");
			}
		break;

default:
		break;
 }		//key 3 = converts hex to bcd


    /*
     * Read the PIO to delay ISR exit. This is done to prevent a spurious
     * interrupt in systems with high processor -> pio latency and fast
     * interrupts.
     */
    IORD_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE);
}
