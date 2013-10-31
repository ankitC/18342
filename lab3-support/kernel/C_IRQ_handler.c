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

static void handle_timer_irq(void)
{
	timer_counter++;
	reg_write(OSTMR_OSCR_ADDR, 0x0);

	return;
}

void C_IRQ_handler()
{
	uint32_t icpr_reg, osmr0_mask, ossr_reg;
	icpr_reg = reg_read(INT_ICIP_ADDR);

	/*
	 *          * if the source is not osmr0 == oscr, bail out
	 *                   */
	osmr0_mask = 0x1 << INT_OSTMR_0;

	/* Check if the interrupt was from timer */
	if(!(icpr_reg & osmr0_mask)) {
		printf("\n Interrupt from an unknonwn source.\n");
		return;
	}

	handle_timer_irq();

	ossr_reg = reg_read(OSTMR_OSSR_ADDR);
	ossr_reg |= OSTMR_OSSR_M0;
	reg_write(OSTMR_OSSR_ADDR, ossr_reg);

	//ossr_reg = reg_read(OSTMR_OSSR_ADDR);
	return;
}


