/** @file dagger.c
 *
 * @brief Creates two simple periodic tasks.
 *
 * @note  This is like knife -- but smaller :)
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-11-30
 */
#include <stdio.h>
#include <task.h>
#include <unistd.h>
#include <lock.h>

volatile int mut = -1;

void panic(const char* str)
{
	puts(str);
	while(1);
}

void fun1(void* str)
{
	mut = mutex_create();
	mutex_lock(mut);
	putchar('1');
	mutex_unlock(mut);
	while(1)
	{
		putchar((int)str);
		if(event_wait(0) < 0)
			panic("Dev 0 failed");
	}
}

void fun2(void* str)
{
	while(1)
	{
		mutex_lock(mut);
		putchar('2');
		int i = 1;
		while(i <= 5)
		{
			putchar('5');
			i++;
			sleep(90);
		}
		putchar((int)str);
		mutex_unlock(mut);
	}
}

int main(int argc, char** argv)
{
	task_t tasks[2];
	tasks[0].lambda = fun1;
	tasks[0].data = (void*)'@';
	tasks[0].stack_pos = (void*)0xa2000000;
	tasks[0].C = 1;
	tasks[0].B = 1;
	tasks[0].T = PERIOD_DEV0;
	tasks[1].lambda = fun2;
	tasks[1].data = (void*)'<';
	tasks[1].stack_pos = (void*)0xa1000000;
	tasks[1].C = 1;
	tasks[1].B = 1;
	tasks[1].T = PERIOD_DEV1;

	task_create(tasks, 2);
	argc = argc; /* remove compiler warning */
	argv = argv; /* remove compiler warning */

	puts("Elvis could not leave the building, but why did your code get here!\n");
	return 0;
}
