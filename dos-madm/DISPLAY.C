/*
 * display.c -- routines to display binary values on the simulated
 *				Williams Tube "memory" for the Prototype Mark I.
 *
 * LW	06/17/89
 */
#include "madm.h"
#include "graphics.h"
#include "display.h"
#include "proto.h"

/* initialize the monitor tubes */
MONITOR_TUBE monitors[NUM_MONITORS] = {
	{A_X, A_Y, Accumulator},
	{C_X, C_Y, Control},
	{S_X, S_Y, Store}
};

/*
 * display_bit -- display the single bit value at position "bit"
 *				  on line "line" on the given monitor tube ("tube").
 *				  Note that numbers are displayed with the least
 *				  significant bit on the left (backwards binary).
 */
void
display_bit(int16_t tube, ADDR line, uint16_t bit)
{
	scr_curs(S_X + bit, S_Y + line);

	printf("\033[7m%s\033[0m", ((int16_t)(monitors[tube].mt_val[line] >> bit) & 0x1) ? "#" : ".");
}

/*
 * display_line -- display the value on a given "line" of the
 *				   given monitor "tube".
 */
void
display_line(int16_t tube, ADDR line)
{
	set_up_line(monitors[tube].mt_val[line]);
	show_line(monitors[tube].mt_x,
			  monitors[tube].mt_y + line);
}
