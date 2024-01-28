#ifndef KEYBOARD_H
#define KEYBOARD_H

/*
 * keyboard.h -- System dependent definitions needed for 
 *				 use of the keyboard in "editing" programs
 *				 for Prototype Manchester Mark I simulator.
 *
 *				 [IBM/PC Aztec C version]
 *
 * LW	06/16/89
 */
#define START_CMD	'\r'		/* CR to start pgm at instruction 1 */
#define SSTEP_CMD	's'			/* 's' to single-step program */
#define CLEAR_CMD	'c'			/* 'c' to clear store (KSC key) */
#define CLR_AC_CMD	'k'			/* 'k' to clear A & C (KCC key) */
#define TOGGLE_CMD	' '			/* space bar to toggle the current bit */
#define QUIT_CMD	'\033'		/* ESC to leave simulator */

#define CONTROL_CMD 224     /* Windows: Another code will follow for the arrow key.*/
#define UP_CMD		72		/* Up arrow key on Windows */
#define DOWN_CMD	80		/* Down arrow key on Windows */
#define RIGHT_CMD	77		/* Right arrow key on Windows */
#define LEFT_CMD	75		/* Left arrow key on Windows */

/* 
 * use Aztec C keyboard functions for echo-free input & polling
 */
#define next_cmd()	getch()			    /* get character/cmd from keyboard */
#define cmd_ready() (kbhit())	/* has a key been pressed? */

#endif /* KEYBOARD_H */