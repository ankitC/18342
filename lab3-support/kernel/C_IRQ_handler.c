/* C_IRQ_handler.c : IRQ handler for maintaining clock ticks.
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

extern unsigned long timer_counter;

/* Handler for IRQs*/
void C_IRQ_handler()
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

	/* Updating the match register for the counter */
	clocks_till_interrupt = reg_read(OSTMR_OSMR_ADDR(0));
	clocks_till_interrupt += (OSTMR_FREQ*TIMER_RESOLUTION)/1000;
	reg_write(OSTMR_OSMR_ADDR(0), clocks_till_interrupt);

	/* Clearing the match bit */
	ossr_reg = reg_read(OSTMR_OSSR_ADDR);
	ossr_reg |= OSTMR_OSSR_M0;
	reg_write(OSTMR_OSSR_ADDR, ossr_reg);

	ossr_reg = reg_read(OSTMR_OSSR_ADDR);
	return;
}


