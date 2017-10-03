/*
 * HexDisplay.c
 *
 *  Created on: Apr 21, 2015
 *      Author: brent.horine
 */
#include "io.h"
#include "system.h"
#include "alt_types.h"

#include "seven_seg_hex.h"
#include "seven_seg_bcd.h"
#include "HexDisplay.h"

//extern volatile alt_u8 leading_zeros;
extern volatile alt_u8 display_as_bcd;

alt_u8 bcd_hex_flip()
{
	display_as_bcd = !display_as_bcd;

	return display_as_bcd;
}

void HexDisplay(alt_u32 * base, alt_u16 num) {
	alt_u8 leading_zeros = 0x1&IORD(SLIDER_SWITCHES_BASE, 0);
	if (display_as_bcd) {
		seven_seg_bcd(base, num, leading_zeros);
	} else {
		seven_seg_hex(base, num, leading_zeros);
	}
}
