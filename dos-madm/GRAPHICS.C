/*
 * graphics.c -- system dependent graphics routines for Prototype
 *				 Manchester Mark I simulator.
 *
 *				 [IBM/PC Aztec C 4.10 Version]
 *
 *				 NOTE:  Display routines in the simulator assume that
 *				 (0, 0) and (X_MAX, Y_MAX) are the lower-left and upper-
 *				 right corners of the graphics screen.  If system-supplied
 *				 functions assume otherwise, the adjustments should be
 *				 made here.
 *
 * LW	06/18/89
 */

#include "madm.h"
#include "graphics.h"
#include "display.h"
#include "proto.h"
#include <stdlib.h>

#define odd(n)	((n) & 1)

/*
 * set_up_graphics -- put the display into graphics mode (if necessary)
 *					  and set up the display screen.
 */
void
set_up_graphics()
{
	static const char main_title[] = "Manchester Mark I Prototype";
	static const char sub_title[]  = "(1948)";

	clear_graphics();

	printf("\033[?25l"); // Stop the cursor from running around the screen every time we redraw

	// mode('m');		/* IBM/PC 320x200 color graphics mode */ - set by default

	show_label(19, 1, main_title);
	show_label(30, 2, sub_title);

	/* note that C & A labels are aligned horizontally */
	show_label(0,  5, "A:");
	show_label(35,  5, "C:");
	show_label(15,  11, "S:");

}

/*
 * clear_graphics -- clear the graphics display
 */
void
clear_graphics()
{
	printf("\033[2J");
}

/*
 * blob -- display a blob of light at coordinates (x, y) on the screen.
 *		   A "dash" blob will be displayed for a non-zero "value", a
 *		   "dot" for zero (this simulates the "look" of the Williams
 *		   Tube memory for the Prototype Mark I).
 */
void
blob(int16_t value, uint16_t x, uint16_t y)
{
	static char color = 0;

	if (value != 0) 
		color = 97;			/* white dashes */
	else
		color = 0;			/* black background */

	scr_curs(x + 1, y);
	printf("\033[%d;40m⬤\033[0", color);

	if (value == 0)
		color = 31;			/* dots are red (to look dimmer) */

	scr_curs(x, y);
	printf("\033[%d;40m⬤\033[0", color);
}

static unsigned char Scan_lines[(LINE_WIDTH+DOTS_PER_BYTE-1)/DOTS_PER_BYTE + 1];

/*
 * set_up_line -- set up the scan line(s) needed to display a given
 *				  "value" on the screen.
 *
 *				  NOTE:  The current algorithm for this routine works
 *				  only if S_X, BLOB_WIDTH+H_SPACE, and XHSPACE
 *				  are divisible by DOTS_PER_BYTE;
 */
void
set_up_line(LINE value)
{
	register uint16_t i, byte;

	byte = 0;

	for (i = 0; i < LINE_BITS; i++) {

		Scan_lines[byte] = (value & 0x1) ? '#' : '.';
		value >>= 1;

		byte += 1;
	}

	Scan_lines[32] = '\0';

}

/*
 * show_line -- display the value last set up by "set_up_line" at 
 *				location (x, y) on the screen.
 */
void
show_line(uint16_t x, uint16_t y)
{
	scr_curs(x, y);
	printf("%s", Scan_lines);
}

/*
 * draw_box -- draw a box whose lower left hand corner is (lo_x, lo_y)
 *			   and whose upper right hand corner is (hi_x, hi_y).
 *			   The remaining parameter ("visible") determines if the box
 *			   is to be visible or not.
 */
void
draw_box(int16_t visible, uint16_t lo_x, uint16_t lo_y, uint16_t hi_x, uint16_t hi_y)
{

	if (!visible) return;
	
	// horizontal, top
	scr_curs(lo_x, hi_y);
	printf("┌");
	for (int i = lo_x + 1; i < hi_x - 1; i++) {
		scr_curs(i, hi_y);
		printf("─");
	}
	scr_curs(hi_x, hi_y);
	printf("┐");
	
	// vertical
	for (int i = lo_y + 1; i < hi_y; i++) {
		scr_curs(lo_x, i);
		printf("│");
		scr_curs(hi_x, i);
		printf("│");
	}

	// horizontal, bottom
	scr_curs(lo_x, lo_y);
	printf("└");
	for (int i = lo_x + 1; i < hi_x - 1; i++) {
		scr_curs(i, lo_y);
		printf("─");
	}
	scr_curs(hi_x, lo_y);
	printf("┘");

}
