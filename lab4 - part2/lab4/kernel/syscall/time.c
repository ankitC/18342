/** @file time.c
 *
 * @brief Kernel timer based syscall implementations
 *
 * @author Jiten Mehta <jitenm>
 *         Ankit Chheda <achheda>
 *         Arjun Ankleshwaria <aanklesh>
 *
 * @date   Nov. 15, 2013  9:30 pm
 */

#include <types.h>
#include <config.h>
#include <bits/errno.h>
#include <arm/timer.h>
#include <syscall.h>

extern volatile unsigned long timer_counter;

/**
 * @brief Returns the current time of the system in milliseconds,
 *        rounding up to the nearest multiple of 10.
 */
unsigned long time_syscall(void)
{
	return (timer_counter * OS_TIMER_RESOLUTION);
}

/**
 * @brief Waits in a tight loop for atleast the given number of milliseconds.
 * @param millis  The number of milliseconds to sleep.
 */
void sleep_syscall(unsigned long millis)
{
	/* Wait till the time, rounding-up to the nearest multiple of 10 */
	uint32_t ticks_to_sleep = timer_counter + (millis / OS_TIMER_RESOLUTION);
	while(timer_counter < ticks_to_sleep);
}
