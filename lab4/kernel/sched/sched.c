/** @file sched.c
 * 
 * @brief Top level implementation of the scheduler.
 *
 * @author: Group Member 1: Arjun Ankleshwaria <aanklesh>
 *          Group Member 2: Jiten Mehta <jitenm>
 *		    Group Member 3: Ankit Chheda <achheda>
 *
 * @date:   Nov 19, 2013 9:00 PM
 */

#include <types.h>
#include <assert.h>
#include <kernel.h>
#include <config.h>
#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/physmem.h>
#include <device.h>
#include "sched_i.h"

tcb_t system_tcb[OS_MAX_TASKS]; /* allocate memory for system TCBs */

/**
 * @brief Initialize the scheduler.
 */
void sched_init(task_t* main_task  __attribute__((unused)))
{
	/* This function is not used */
}

/**
 * @brief This is the idle task that the system runs when no other task is runnable
 */
static void idle(void)
{
	enable_interrupts();
	while(1);
}

/**
 * @brief Allocate user-stacks and initializes the kernel contexts of the
 * given threads.
 *
 * This function assumes that:
 * - num_tasks < number of tasks allowed on the system.
 * - the tasks have already been deemed schedulable and have been appropriately
 *   scheduled.  In particular, this means that the task list is sorted in order
 *   of priority -- higher priority tasks come first.
 *
 * @param tasks  A list of scheduled task descriptors.
 * @param size   The number of tasks is the list.
 */
void allocate_tasks(task_t** tasks, size_t num_tasks)
{

	task_t* temp_tasks = *tasks;
	unsigned int i = 0;

	/* Initilize the run_queue and add the allocated tasks to the runqueue */
	runqueue_init();

	for(i = 1; i <= num_tasks; i++)
	{
		//assert(temp_tasks[i-1] != null);
		//panic("Null task detected during allocation.\n");

		system_tcb[i].native_prio = i;
		system_tcb[i].cur_prio = i;
		system_tcb[i].context.r5 = (uint32_t)temp_tasks[i - 1].data;
		system_tcb[i].context.r4 = (uint32_t)temp_tasks[i - 1].lambda;
		system_tcb[i].context.r6 = (uint32_t)temp_tasks[i - 1].stack_pos;
		system_tcb[i].context.sp = system_tcb[i].kstack_high;
		system_tcb[i].context.lr = &launch_task;
		system_tcb[i].holds_lock = 0;
		system_tcb[i].sleep_queue = null;

		runqueue_add(&system_tcb[i], i);
	}

	/* Initializing the idle task */
	system_tcb[IDLE_PRIO].native_prio = IDLE_PRIO;
	system_tcb[IDLE_PRIO].cur_prio = IDLE_PRIO;
	system_tcb[IDLE_PRIO].context.r5 = 0;
	system_tcb[IDLE_PRIO].context.r4 = (uint32_t)&idle;
	system_tcb[IDLE_PRIO].context.r8 = global_data;

	/* Don't need stack pointer in userspace for idle task */
	system_tcb[IDLE_PRIO].context.r6 = (unsigned)null;
	system_tcb[IDLE_PRIO].context.sp = system_tcb[IDLE_PRIO].kstack_high;
	system_tcb[IDLE_PRIO].holds_lock = 0;
	system_tcb[IDLE_PRIO].sleep_queue = null;
	system_tcb[IDLE_PRIO].context.lr = &idle;

	/* Adding idle task to the run queue */
	runqueue_add(&system_tcb[IDLE_PRIO], IDLE_PRIO);
}
