/** @file proc.c
 * 
 * @brief Implementation of `process' syscalls
 *
 * @author: Group Member 1: Arjun Ankleshwaria <aanklesh>
 *          Group Member 2: Jiten Mehta <jitenm>
 *		    Group Member 3: Ankit Chheda <achheda>
 *
 * @date:   Nov 20, 2013 9:00 PM
 */

#include <exports.h>
#include <bits/errno.h>
#include <config.h>
#include <kernel.h>
#include <syscall.h>
#include <sched.h>
#include <lock.h>
#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/physmem.h>
#include <device.h>
#include <assert.h>

void swap(task_t, task_t);
void sort(task_t*, int);

int task_create(task_t* tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
	unsigned int i,j = 0;

	/* check for total number of tasks. return error if greater than 64 */
	if(num_tasks > 62)
		return -EINVAL;

	for(i = 0 ; i < num_tasks; i++)
	{
		/* check if function pointer is NULL */
		if(tasks[i].lambda == null)
			return -EINVAL;

		/* check if stack pointers of two tasks are same */
		for(j = 0 ; j < num_tasks; j++)
			if(tasks[i].stack_pos == tasks[j].stack_pos && i !=j)
				return -EINVAL;

		/* check if stack pointer lies outside the valid address space */
		if(!(valid_addr(tasks[i].stack_pos, sizeof(tasks[i]), USR_START_ADDR, USR_END_ADDR)))
				return -EFAULT;
	}

	// TODO: do schedulability test and then allocate_tasks
	
	sort(tasks, num_tasks);
	
	/* Initialize the sleep queue and next match for all devices */
	dev_init();

	/* Initialize all the mutices */
	mutex_init();

	allocate_tasks(&tasks, num_tasks);

	sched_init((task_t*) 0);
dispatch_nosave();	
	
	assert(0); /* should never reach here */
}

int event_wait(unsigned int dev  __attribute__((unused)))
{
	/* Return invalid if the device does not exist */
	if(dev >= NUM_DEVICES)
		return -EINVAL;

	dev_wait(dev);

	dispatch_sleep();

	return 0;
}

/* An invalid syscall causes the kernel to exit. */
void invalid_syscall(unsigned int call_num  __attribute__((unused)))
{
	printf("Kernel panic: invalid syscall -- 0x%08x\n", call_num);
	disable_interrupts();
	while(1);
}

void sort(task_t* temp, int size)
{
	int i = 0, j = 0;
	for (i = 0 ;i < size ; i ++)
		for ( j = 0; j < size ; j++) //TODO can it be < size -i?
			if( temp[i].T > temp[j].T)
				swap(temp[i], temp[j]);
}

void swap(task_t a, task_t b)
{
	task_t t = a;
	a = b;
	b = t;
}
