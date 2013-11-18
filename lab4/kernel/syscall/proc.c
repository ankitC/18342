/** @file proc.c
 * 
 * @brief Implementation of `process' syscalls
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 14 Oct 2007 00:07:38 -0400
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-12
 */

#include <exports.h>
#include <bits/errno.h>
#include <config.h>
#include <kernel.h>
#include <syscall.h>
#include <sched.h>

#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/physmem.h>
#include <device.h>

#define START_ADD 0xa0000000
#define BOUND 0xa3000000
#define null (void*)0

int task_create(task_t* tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
	//return 1;  remove this line after adding your code 
	int i,j = 0;
	if(num_tasks > 64)
		return -EINVAL;//TODO set EINVAL

	for(i = 0 ; (unsigned)i < num_tasks ; i++)
	{
		if(tasks[i].lambda == null)
			return -EINVAL;//TODO Function is null

		for(j=0 ; (unsigned)j < num_tasks ; j++)
		{
			if(tasks[i].stack_pos == tasks[j].stack_pos && i !=j)
				return -EINVAL;//TODO Function has same stack position as some other task
		}

		if(!(valid_addr(tasks[i].stack_pos, sizeof(tasks[i]), START_ADD, BOUND)))
				return -EFAULT;//TODO Invalid Memory location EFAULT
	}
	return 1; //TODO, put to avoid warning
}

int event_wait(unsigned int dev  __attribute__((unused)))
{
	return 1; /* remove this line after adding your code */	
}

/* An invalid syscall causes the kernel to exit. */
void invalid_syscall(unsigned int call_num  __attribute__((unused)))
{
	printf("Kernel panic: invalid syscall -- 0x%08x\n", call_num);
	disable_interrupts();
	while(1);
	//return 0xBADC0DE;
}
