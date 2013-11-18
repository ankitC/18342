/* C_SWI_handler.c : SWI handler for servicing read, write
 *					and exit syscalls.
 *
 * Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
 *          Group Member 2: Jiten Mehta <jitenm>
 *		    Group Member 3: Ankit Chheda <achheda>
 * Date:    Oct 24, 2013 9:00 AM
 */

#include <bits/errno.h>
#include <bits/swi.h>
#include <exports.h>
#include <syscall.h>

/* Helper functions */
//extern void restore_old_handlers(void);
//extern void exit_to_kernel(int status);
//extern void disable_irqs(void);

//extern char* irq_stack;

void C_SWI_handler(int swino, unsigned* args)
{
	switch(swino)
	{
		/* Exit Syscall */
		//case(EXIT_SWI):
			//service_exit(args);

		/* Read Syscall*/
		case(READ_SWI):
			args[0] = read_syscall(args[0], (void*)args[1], args[2]);
			break;

		/* Write Syscall */
		case(WRITE_SWI):
			args[0] =  write_syscall(args[0], (void*)args[1], args[2]);
			break;
		/* Time Syscall */
		case(TIME_SWI):
			args[0] = time_syscall();
			break;
		/* Sleep Syscall */
		case(SLEEP_SWI):
			sleep_syscall(args[0]);
			break;
		default:
			invalid_syscall(swino);
			break;
	}
}

/*
void service_exit(unsigned* args)
{
	int exit_status = (int) args[0];
	disable_irqs();
	restore_old_handlers();
	free(irq_stack);
	exit_to_kernel(exit_status);
}
*/
