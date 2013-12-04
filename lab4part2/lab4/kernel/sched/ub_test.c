/** @file ub_test.c
 * 
 * @brief The UB Test for basic schedulability
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-20
 */

#define DEBUG 0

#include <sched.h>
#ifdef DEBUG
#include <exports.h>
#endif

uint32_t ub_table[62] = {1000, 828, 780, 757, 743, 735, 729, 724, 721,
	 718, 715, 714, 712, 711, 709, 708, 707, 707, 706, 705, 705,
	 704, 704, 703, 703, 702, 702, 702, 701, 701, 701, 701, 700, 700,
	 700, 700, 700, 700, 699, 699, 699, 699, 699, 699, 699, 698, 698, 698,
	 698, 698, 698, 698, 698, 698, 698, 697, 697, 697, 697, 697,
	 697, 697};

/**
 * @brief Perform UB Test and reorder the task list.
 *
 * The task list at the end of this method will be sorted in order is priority
 * -- from highest priority (lowest priority number) to lowest priority
 * (highest priority number).
 *
 * @param tasks  An array of task pointers containing the task set to schedule.
 * @param num_tasks  The number of tasks in the array.
 *
 * @return 0  The test failed.
 * @return 1  Test succeeded.  The tasks are now in order.
 */
static void sort(task_t*, size_t);

int assign_schedule(task_t** tasks, size_t num_tasks)
{
	task_t *temp = *tasks;

	/* Sort the tasks according to their priority */
	sort(temp, num_tasks);

	uint32_t i = 0;
	uint32_t constant = (temp[num_tasks - 1].C + temp[num_tasks - 1].B) * 1000 / temp[num_tasks - 1].T;
	uint32_t result = constant;

	for(i = 0; i < num_tasks - 1; i++)
		result += (temp[i].C * 1000 / temp[i].T);

	if(result <= ub_table[num_tasks - 1])
		return 1;  /* task set is schedulable */

#ifdef DEBUG
	printf("Task set is not schedulable!\n");
#endif

	return 0;
}

/* Sort the tasks in ascending order of their time period */
static void sort(task_t* temp, size_t size)
{
	uint32_t i = 0, j = 0;
	for (i = 0; i < size; i ++)
		for (j = i + 1; j < size; j++)
			if(temp[i].T > temp[j].T)
			{
				task_t t = temp[i];
				temp[i] = temp[j];
				temp[j] = t;
			}
}
