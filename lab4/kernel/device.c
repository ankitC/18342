/**
 * @file device.c
 *
 * @brief Implements simulated devices.
 * 
 * @author: Group Member 1: Arjun Ankleshwaria <aanklesh>
 *          Group Member 2: Jiten Mehta <jitenm>
 *		    Group Member 3: Ankit Chheda <achheda>
 *
 * @date:   Nov 18, 2013 9:00 PM
 */

#include <types.h>
#include <assert.h>
#include <task.h>
#include <sched.h>
#include <device.h>
#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <assert.h>

/**
 * @brief Fake device maintainence structure.
 * Since our tasks are periodic, we can represent 
 * tasks with logical devices. 
 * These logical devices should be signalled periodically 
 * so that you can instantiate a new job every time period.
 * Devices are signaled by calling dev_update 
 * on every timer interrupt. In dev_update check if it is 
 * time to create a tasks new job. If so, make the task runnable.
 * There is a wait queue for every device which contains the tcbs of
 * all tasks waiting on the device event to occur.
 */

struct dev
{
	tcb_t* sleep_queue;
	unsigned long   next_match;
};
typedef struct dev dev_t;

/* devices will be periodically signaled at the following frequencies */
const unsigned long dev_freq[NUM_DEVICES] = {100, 200, 500, 50};
static dev_t devices[NUM_DEVICES];

/**
 * @brief Initialize the sleep queues and match values for all devices.
 */
void dev_init(void)
{
    /**
	 * Initializing sleep queue to NULL and next match to the
	 * corresponding device frequency
	 */
	int i = 0;
	for(i = 0; i < NUM_DEVICES; i++)
	{
		devices[i].sleep_queue = null;
		devices[i].next_match = dev_freq[i];
	}
}

/**
 * @brief Puts a task to sleep on the sleep queue until the next
 * event is signalled for the device.
 *
 * @param dev  Device number.
 */
void dev_wait(unsigned int dev __attribute__((unused)))
{
	tcb_t* present = get_cur_tcb();

	/* Adding to the head of sleep queue of the device */
	present->sleep_queue = devices[dev].sleep_queue;
	devices[dev].sleep_queue = present;
}

/**
 * @brief Signals the occurrence of an event on all applicable devices.
 * This function should be called on timer interrupts to determine that
 * the interrupt corresponds to the event frequency of a device. If the
 * interrupt corresponded to the interrupt frequency of a device, this
 * function should ensure that the task is made ready to run.
 */
void dev_update(unsigned long millis __attribute__((unused)))
{
	int i = 0;

	/**
	 * Matching the current time with match value of all the devices
	 * and add the tasks of the devices whose value matched to the run queue
	 */
	for(i = 0; i < NUM_DEVICES; i++)
	{
		if(devices[i].next_match == millis)
		{
			tcb_t *temp = null;
			printf("De:%d\n", i);
			/* Add the task to the run queue according to its priority */
			for(temp = devices[i].sleep_queue; temp != null;
									temp = temp->sleep_queue)
			{
				runqueue_add(temp, temp->cur_prio);
				printf("DP:%02x\n", highest_prio());
			}

			/* Update the sleep queue and next_match value of the device */
			devices[i].sleep_queue = null;
			devices[i].next_match += dev_freq[i];
		}
	}
}
