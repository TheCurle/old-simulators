/*
 * madm.h -- definitions relating to the operating characteristics of
 *			 the prototype Manchester Mark I
 *
 * LW	06/17/89
 */

#include <stdio.h>
#include <stdint.h>

typedef enum {STOPPED, RUNNING, MANUAL} STATUS;

extern STATUS MADM_status;

/*
 * Storage line in prototype Williams tube is 32 bits long
 */
typedef uint32_t LINE;

#define LINE_BITS		32
#define MAX_LINE		(~(~0L << LINE_BITS))		/* mask for usable bits */

/*
 * Structure of an instruction in the prototype
 */
typedef uint16_t ADDR;		/* storage location */

typedef struct {
	int16_t  i_func;		/* function code */
	ADDR i_addr;		/* store location referred to */
} INSTRUCTION;

#define FUNC_BITS			3
#define MAX_FUNC			(~(~0 << FUNC_BITS))	/* function mask */

#define ADDR_BITS			13
#define UNUSED_ADDR_BITS	8
#define MAX_ADDR			(~(~0 << (ADDR_BITS - UNUSED_ADDR_BITS)))
									/* address mask */

/*
 * Prototype registers & main memory (all in Williams Tubes)
 */
/* # of lines in the various Williams Tubes */
#define ACCUM_SIZE		 1
#define CONTROL_SIZE	 2
#define STORE_SIZE		32

/* indices of each line in the "register" tubes */
#define	A_LINE		0		/* Accumulator line */

#define CI_LINE		0		/* Control Instruction line */
#define PI_LINE		1		/* Present Instruction line */

extern LINE  Accumulator[], Control[], Store[];
extern INSTRUCTION Staticisor;


#if defined(LINUX) || defined(APPLE)


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