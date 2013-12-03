/** @file ub_test.c
 * 
 * @brief The UB Test for basic schedulability
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-20
 */

//#define DEBUG 0

#include <sched.h>
#ifdef DEBUG
#include <exports.h>
#endif

float ub_table[62] = {1.0,0.828,0.78,0.757,0.743,0.735,0.729,0.724,0.721,
	0.718,0.715,0.714,0.712,0.711,0.709,0.708,0.707,0.707,0.706,0.705,0.705,
	0.704,0.704,0.703,0.703,0.702,0.702,0.702,0.701,0.701,0.701,0.701,0.7,0.7,
	0.7,0.7,0.7,0.7,0.699,0.699,0.699,0.699,0.699,0.699,0.699,0.698,0.698,0.698,
	0.698,0.698,0.698,0.698,0.698,0.698,0.698,0.697,0.697,0.697,0.697,0.697,
	0.697,0.697 };

 
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
static void sort(task_t*, int);

int assign_schedule(task_t** tasks, size_t num_tasks)
{
	task_t *temp = *tasks;

	/* Sort the tasks according to their priority */
	sort(temp, num_tasks);

	unsigned int i = 0;
	float constant = (temp[num_tasks - 1].C + temp[num_tasks - 1].B) / temp[num_tasks - 1].T;
	float result = constant;

	for(i = 0; i < num_tasks - 1; i++)
		result += (temp[i].C/temp[i].T);

	if(result <= ub_table[num_tasks - 1])
		return 1;  /* task set is schedulable */
	else
		return 0;  /* task set is not schedulable */

}

/* Sort the tasks in ascending order of their time period */
static void sort(task_t* temp, int size)
{
	int i = 0, j = 0;
	for (i = 0 ;i < size ; i ++)
		for ( j = i+1; j < size ; j++)
			if( temp[i].T > temp[j].T)
			{
				task_t t = temp[i];
				temp[i] = temp[j];
				temp[j] = t;
			}
}
