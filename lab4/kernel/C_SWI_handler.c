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
#include <lock.h>

extern tcb_t system_tcb[];

void C_SWI_handler(int swino, unsigned* args)
{
	printf("CSH%u\n", &system_tcb[2].cur_prio);
	printf("CSH%u SWI: %x\n", system_tcb[2].cur_prio, swino);
	switch(swino)
	{
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

		/* Task Create Syscall */
		case(CREATE_SWI):
			args[0] = task_create((task_t*)args[0], args[1]);
			break;

		/* Mutex Create Syscall */
		case(MUTEX_CREATE):
			args[0] = mutex_create();
			break;

		/* Mutex Lock Syscall */
		case(MUTEX_LOCK):
			args[0] = mutex_lock(args[0]);
			break;

		/* Mutex Unlock Syscall */
		case(MUTEX_UNLOCK):
			args[0] = mutex_unlock(args[0]);
			break;

		/* Event Wait Syscall */
		case(EVENT_WAIT):
			args[0] = event_wait(args[0]);
			break;

		/* Invalid SWI Number */
		default:
			invalid_syscall(swino);
	}
}
