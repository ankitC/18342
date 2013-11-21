/** @file sched.c
 * 
 * @brief Top level implementation of the scheduler.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-20
 */

#include <types.h>
#include <assert.h>

#include <kernel.h>
#include <config.h>
#include "sched_i.h"

#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/physmem.h>
#include <device.h>

#define SLEEP_TASK_PRIO OS_MAX_TASKS - 1

tcb_t system_tcb[OS_MAX_TASKS]; /* allocate memory for system TCBs */

void sched_init(task_t* main_task  __attribute__((unused)))
{
	
}

/**
 * @brief This is the idle task that the system runs when no other task is runnable
 */
 
static void __attribute__((unused)) idle(void)
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
void allocate_tasks(task_t** tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
	unsigned int i = 0, j =0;
	for(i = 1; i < num_tasks; i++)
	{
		assert(tasks[i] != null);
		//panic("Null task detected during allocation.\n");

		system_tcb[i].native_prio = i;
		system_tcb[i].cur_prio = i;
		system_tcb[i].context.r5 = (uint32_t)tasks[i]->data;
		system_tcb[i].context.r4 = (uint32_t)tasks[i]->lambda;
		system_tcb[i].context.r6 = (uint32_t)tasks[i]->stack_pos;
		system_tcb[i].holds_lock = 0;
		system_tcb[i].sleep_queue = null;

		/* Initialize the sleep queue and next match for all devices */
		dev_init();

		/* Adding each task to the corresponding device sleep queue */
		for(j = 0 ; j < NUM_DEVICES ; j++)
		{
			if(tasks[i].T == dev_freq[j])
			{
				tasks[i].sleep_queue = devices[j].sleep_queue;
				devices[j].sleep_queue = tasks[i];
			}
		}

		/**
		 * Zero because this is the initialization of the tasks so you want to
		 * add all the tasks on all the devices to the run queue
		 */
		dev_update(0);
	}

	assert(tasks[i] == null);
	//panic("Tasks still pending to be allcoated.\n");	

	/* Initializing the idle task */
	system_tcb[SLEEP_TASK_PRIO].native_prio = SLEEP_TASK_PRIO;
	system_tcb[SLEEP_TASK_PRIO].cur_prio = SLEEP_TASK_PRIO;
	system_tcb[SLEEP_TASK_PRIO].context.r5 = 0;
	system_tcb[SLEEP_TASK_PRIO].context.r4 = (uint32_t) &idle;
	//TODO: Stack Pointer for idle task will be?
	//Design Decision.
	system_tcb[SLEEP_TASK_PRIO].context.r6 = 0xa000001f;
	system_tcb[SLEEP_TASK_PRIO].holds_lock = 0;
	system_tcb[SLEEP_TASK_PRIO].sleep_queue = null;

	/* Adding idle task to the run queue */
	runqueue_add(&system_tcb[SLEEP_TASK_PRIO], SLEEP_TASK_PRIO);
}
