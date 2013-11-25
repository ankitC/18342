/**
 * @file mutex.c
 *
 * @brief Implements mutices.
 *
 * @author: Group Member 1: Arjun Ankleshwaria <aanklesh>
 *          Group Member 2: Jiten Mehta <jitenm>
 *		    Group Member 3: Ankit Chheda <achheda>
 *
 * @date:   Nov 20, 2013 9:00 PM
 */

#include <lock.h>
#include <task.h>
#include <sched.h>
#include <bits/errno.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <exports.h>

//#define DEBUG 0

#define null (void*) 0

mutex_t gtMutex[OS_NUM_MUTEX];

/* Initialize all the mutices */
void mutex_init()
{
	int i = 0;
	for (i = 0; i < OS_NUM_MUTEX; i++)
	{
		gtMutex[i].bAvailable = TRUE;
		gtMutex[i].pHolding_Tcb = (void*) 0;
		gtMutex[i].bLock = FALSE;
		gtMutex[i].pSleep_queue = (void*) 0;
	}
}

/* Create a mutex */
int mutex_create(void)
{
	int i = 0 ;
	for (i = 0; i < OS_NUM_MUTEX; i++)
	{
		if(gtMutex[i].bAvailable == TRUE)
		{
			gtMutex[i].bAvailable = FALSE;
			return i;
		}
	}
	/* Returned only if we run out of mutices */
	return -ENOMEM;
}

/* Lock the mutex and assign it to the current task */
int mutex_lock(int mutex)
{
	tcb_t *cur = get_cur_tcb();
	tcb_t *next = gtMutex[mutex].pSleep_queue;

	/* Error checks */
	if((gtMutex[mutex].bAvailable == TRUE) || (mutex >= OS_NUM_MUTEX) ||
			(mutex < 0))
		return -EINVAL;

	/* If you already own the mutex, it will cause a deadlock*/
	if(cur == gtMutex[mutex].pHolding_Tcb)
		return -EDEADLOCK;

#ifdef DEBUG
	printf("Trying to allocated mutex %d to %u.\n", mutex, cur->native_prio);
#endif

	/* If someone is already holding the mutex and its not yourself */
	if(gtMutex[mutex].pHolding_Tcb!= null)
	{
		/* Add the current task to the sleep queue */
		cur->sleep_queue = null;

		if(gtMutex[mutex].pSleep_queue == null)
			gtMutex[mutex].pSleep_queue = cur;

		else	/* Find the last element on the sleep queue.*/
		{
			while(next->sleep_queue != null)
				next = next->sleep_queue;

			next->sleep_queue = cur;
		}

#ifdef DEBUG
		printf("Mutex unavail %d for %u. Task %u holds it.\n", mutex, \
				cur->native_prio, gtMutex[mutex].pHolding_Tcb->native_prio);
#endif

		/* Schedule the next task and put the current to sleep. */
		dispatch_sleep();
	}

	gtMutex[mutex].pHolding_Tcb = cur;
	gtMutex[mutex].bLock = TRUE;
	cur->holds_lock++;

#ifdef DEBUG
	printf("Mutex %d allocated to task %u.\n", mutex, cur->native_prio);
#endif

	return 0;
}

/* Unlock the mutex and make it available for acquisition */
int mutex_unlock(int mutex)
{
	tcb_t *cur = get_cur_tcb();
	tcb_t *head = gtMutex[mutex].pSleep_queue;

	if(gtMutex[mutex].bAvailable == TRUE || mutex >= OS_NUM_MUTEX || mutex < 0)
		return -EINVAL;

	/* If you do not hold the mutex but call an unlock on it, then Invalid!! */
	if(cur != gtMutex[mutex].pHolding_Tcb)
		return -EPERM;

	cur->holds_lock--;
	gtMutex[mutex].pHolding_Tcb = null;
	gtMutex[mutex].bLock = FALSE;

	if(head != null)
	{
		gtMutex[mutex].pSleep_queue = head->sleep_queue;
		head->sleep_queue=null;
		runqueue_add(head, head->cur_prio);
	}

#ifdef DEBUG
	printf("Mutex %d deallocated from task %u.\n", mutex, cur->native_prio);
#endif

	/**
	 * After the mutex is unlocked, check if any higher priority task
	 * was blocked by the current task.
	 */
	if(get_cur_tcb()->cur_prio < highest_prio())
		dispatch_save();

	return 0;
}
