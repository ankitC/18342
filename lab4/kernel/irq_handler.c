/* irq_handler.c : IRQ handler for maintaining clock ticks.
 *
 * Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
 *          Group Member 2: Jiten Mehta <jitenm>
 *		    Group Member 3: Ankit Chheda <achheda>
 * Date:    Oct 24, 2013 9:00 AM
 */

#include <exports.h>
#include <arm/timer.h>
#include <arm/reg.h>
#include <arm/interrupt.h>
#include <kernel_helper.h>
#include <config.h>
#include <device.h>
#include <sched.h>

extern unsigned long timer_counter; 

/* Handler for IRQs*/
void irq_handler(void)
{
	uint32_t icpr_reg, osmr0_mask, ossr_reg;
	uint32_t clocks_till_interrupt = 0;
	icpr_reg = reg_read(INT_ICIP_ADDR);

	osmr0_mask = 0x1 << INT_OSTMR_0;

	/* Check if the interrupt was from timer */
	if(!(icpr_reg & osmr0_mask)) {
		printf("\n Interrupt from an unknonwn source.\n");
		return;
	}

	timer_counter++;

	printf("-");
	/* Updating the match register for the counter */
	clocks_till_interrupt = reg_read(OSTMR_OSMR_ADDR(0));
	clocks_till_interrupt += (OSTMR_FREQ*OS_TIMER_RESOLUTION)/1000;
	reg_write(OSTMR_OSMR_ADDR(0), clocks_till_interrupt);

	/* Clearing the match bit */
	ossr_reg = reg_read(OSTMR_OSSR_ADDR);
	ossr_reg |= OSTMR_OSSR_M0;
	reg_write(OSTMR_OSSR_ADDR, ossr_reg);

	/*
	 * Check the devices for their firing and add the
	 * corresponding tasks to the run queue.
	 */
	dev_update(timer_counter * OS_TIMER_RESOLUTION);

	/* Context switch to the highest priority task in the run queue */
	dispatch_save();

	ossr_reg = reg_read(OSTMR_OSSR_ADDR);
	return;
}
