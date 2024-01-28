/*
 * execute.c -- fetch and execute instructions for the Manchester Prototype
 *
 * LW	06/16/89
 */
#include "madm.h"
#include "proto.h"
#include "keyboard.h"


#if defined(LINUX) || defined(APPLE)

#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <stropts.h>

int kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

#else 

#include <conio.h>

#endif

void
execute()
{
	do {
		fetch_instruction();
		exec_instruction();
	} while (MADM_status == RUNNING && !cmd_ready());
}
