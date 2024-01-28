/*
 * edit.c -- program editing functions for the Manchester Mark I
 *			 Prototype
 *
 * LW	06/17/89
 */
#include "madm.h"
#include "keyboard.h"
#include "display.h"
#include "proto.h"
//#include "conio_shim.h"

//Hack(anita): Move conio stuff to the top of the file and move it out of madm.h
#include <stdio.h>

#if defined(__APPLE__) || defined(__linux__)

#include <unistd.h>
#include <termios.h>

char getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    printf("%c\n", buf);
    return buf;
}

#else

#include <conio.h>

#endif


/*
 * edit -- get commands from the keyboard and obey them
 *		   until either the QUIT or START command is entered.
 *		   Return the value 0 for QUIT (exit the simulator) or
 *		   1 for START (start the program).
 */
int16_t
edit()
{
	ADDR line;

	place_cursor((ADDR)Control[CI_LINE], 0);

	for (;;) {

		switch (next_cmd()) {
		case QUIT_CMD:
			erase_cursor();
			return(0);
		case START_CMD:
			erase_cursor();
			MADM_status = RUNNING;
			return(1);
		case SSTEP_CMD:
			erase_cursor();
			MADM_status = MANUAL;
			return(1);
		case CLEAR_CMD:
			/* KSC switch clears the store */
			for (line = 0; line < STORE_SIZE; line++) {
				Store[line] = 0;
				display_line(S_TUBE, line);
			}
			show_cursor();
			break;
		case CLR_AC_CMD:
			/* KCC switch clears A & C */
			Accumulator[A_LINE] =
				Control[CI_LINE] = Control[PI_LINE] = 0;
			display_line(A_TUBE, A_LINE);
			display_line(C_TUBE, CI_LINE);
			display_line(C_TUBE, PI_LINE);
			place_cursor(0, 0);
			break;
		case TOGGLE_CMD:
			toggle_current_bit();
			display_current_bit();
			break;
		case CONTROL_CMD:
			char rd = getch();
			switch(rd) {
				case UP_CMD:
					move_cursor(-1, 0);
					break;
				case DOWN_CMD:
					move_cursor(1, 0);
					break;
				case LEFT_CMD:
					move_cursor(0, -1);
					break;
				case RIGHT_CMD:
					move_cursor(0, 1);
					break;
			}
		}

	}

}

/*
 * toggle_bit -- toggle the value of a given bit ("bit") in a given
 *				 line ("line") in the store.
 */
void
toggle_bit(ADDR line, uint16_t bit)
{
	Store[line] ^= 1L << bit;
}