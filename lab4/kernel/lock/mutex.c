/**
 * @file mutex.c
 *
 * @brief Implements mutices.
 *
 * @author Harry Q Bovik < PUT YOUR NAMES HERE
 *
 * 
 * @date  
 */

#define DEBUG_MUTEX

#include <lock.h>
#include <task.h>
#include <sched.h>
#include <bits/errno.h>
#include <arm/psr.h>
#include <arm/exception.h>
#ifdef DEBUG_MUTEX
#include <exports.h> // temp
#define DEBUG
#endif

#define null (void*) 0

mutex_t gtMutex[OS_NUM_MUTEX];

void mutex_init()
{
	int i = 0;
	for ( i =0 ;i< OS_NUM_MUTEX ; i++)
	{
		gtMutex[i].bAvailable = TRUE;
		gtMutex[i].pHolding_Tcb = (void*) 0;
		gtMutex[i].bLock = FALSE;
		gtMutex[i].pSleep_queue = (void*) 0;
	}
}

int mutex_create(void)
{
	int i = 0 ;
	for (i = 0; i<OS_NUM_MUTEX ; i++)
	{
		if(gtMutex[i].bAvailable == TRUE )
		{
			gtMutex[i].bAvailable = FALSE;
			return i; // fix this to return the correct value
		}
	}
	//Returned only if we run out of mutexes
	return -ENOMEM;
}

int mutex_lock(int mutex  __attribute__((unused)))
{
	tcb_t *cur = get_cur_tcb();
	tcb_t *next = gtMutex[mutex].pSleep_queue;

	/* Error checks */
	if(gtMutex[mutex].bAvailable == TRUE || mutex >= OS_NUM_MUTEX || mutex < 0)
		return -EINVAL;

	/* If you already own the mutex, it will cause a deadlock*/
	if(cur == gtMutex[mutex].pHolding_Tcb)
		return -EDEADLOCK;

#ifdef DEBUG
	printf("Trying to allocated mutex to %u.\n", cur->native_prio);
#endif

	/* If someone is already holding the mutex and its not yourself */
	if(gtMutex[mutex].pHolding_Tcb!= null)
	{
		/* Remove the current from run queue and add it to the sleep queue */
		if(cur != runqueue_remove(cur->cur_prio))
			printf("Couldn't remove current during mutex lock.\n");

		cur->sleep_queue = null;

		if(gtMutex[mutex].pSleep_queue == null)
			gtMutex[mutex].pSleep_queue = cur;

		else/* Find the last element on the sleep queue.*/
		{
			while(next->sleep_queue != null)
				next = next->sleep_queue;

			next->sleep_queue = cur;
		}

		#ifdef DEBUG
		printf("Mutex unavail for %u. Task %u holds it.\n", cur->native_prio, gtMutex[mutex].pHolding_Tcb->native_prio);	
		#endif
			//@TODO: Schedule the next task and put the current to sleep.
			//dispatch_sleep();
	}

	gtMutex[mutex].pHolding_Tcb = cur;
	gtMutex[mutex].bLock = TRUE;
	cur->holds_lock++;

#ifdef DEBUG
	printf("Mutex allocated to task %u.\n", cur->native_prio);
#endif

	return 0;
}

int mutex_unlock(int mutex  __attribute__((unused)))
{
	tcb_t *cur = get_cur_tcb();
	tcb_t *head = gtMutex[mutex].pSleep_queue;

	if(gtMutex[mutex].bAvailable == TRUE || mutex >= OS_NUM_MUTEX || mutex < 0)
		return -EINVAL;

	/* If you do not hold the mutex but call an unlock on it, then Invalid!!*/
	if(cur != gtMutex[mutex].pHolding_Tcb)
		return -EPERM;

	cur->holds_lock--;
	gtMutex[mutex].pHolding_Tcb = null;
	gtMutex[mutex].bLock = FALSE;
	//head = gtMutex[mutex].pSleep_queue;

	if(head != null)
	{
		gtMutex[mutex].pSleep_queue = head->sleep_queue;
		head->sleep_queue=null;
		runqueue_add(head, head->cur_prio);
	}

#ifdef DEBUG
	printf("Mutex deallocated from task %u.\n", cur->native_prio);
#endif

	return 0;
}
