/*
 * cursor.c -- functions to manipulate the cursor used in
 *			   editing programs for the Prototype Manchester Machine
 *
 * LW	06/18/89
 */
#include "madm.h"
#include "graphics.h"
#include "display.h"
#include "proto.h"

typedef struct {
	ADDR c_line;		/* current line in store */
    uint16_t c_bit;		/* current bit in line */
	uint16_t c_x,		/* x position of cursor on screen */
			 c_y;		/* y position of cursor on screen */
} CURSOR;

static CURSOR Cursor = {
	0, 0,
	S_X,
	S_Y
};

/*
 * show_cursor -- display the cursor at its current screen position
 */
void
show_cursor()
{
	scr_curs(Cursor.c_x, Cursor.c_y);
	printf("\033[7m%s\033[0m", (Store[Cursor.c_line] & 1L << Cursor.c_bit) ? "#" : ".");
}

/*
 * erase_cursor -- remove the cursor from its current screen position
 */
void
erase_cursor()
{
	scr_curs(Cursor.c_x, Cursor.c_y);
	printf("\033[0m%s", (Store[Cursor.c_line] & 1L << Cursor.c_bit) ? "#" : ".");
}

/*
 * place_cursor -- place the cursor at a given bit ("bit")
 *				   on a given line ("line") and display it
 *				   at its new position
 */
void place_cursor(ADDR line, uint16_t bit)
{
	erase_cursor();

	Cursor.c_line = line % STORE_SIZE;
	Cursor.c_bit  = bit  % LINE_BITS;

	Cursor.c_x = S_X + Cursor.c_bit;
	Cursor.c_y = S_Y + Cursor.c_line;

	show_cursor();
}

/*
 * move_cursor -- move the cursor a given distance from the current line
 *				  ("d_line") and a given distance from the current bit
 *				  ("d_bit")
 */
void
move_cursor(int16_t d_line, int16_t d_bit)
{
	place_cursor(Cursor.c_line + d_line, Cursor.c_bit + d_bit);
}

/*
 * toggle_current_bit -- toggle the bit at the cursor's current location
 */
void
toggle_current_bit()
{
	toggle_bit(Cursor.c_line, Cursor.c_bit);
}

/*
 * display_current_bit -- display the bit at the cursor's current location
 */
void
display_current_bit()
{
	display_bit(S_TUBE, Cursor.c_line, Cursor.c_bit);
}
