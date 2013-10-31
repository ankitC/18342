/* C_IRQ_handler.c : IRQ handler for maintaining clock ticks.
 *
 * Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
 *          Group Member 2: Jiten Mehta <jitenm>
 *		    Group Member 3: Ankit Chheda <achheda>
 * Date:    Oct 24, 2013 9:00 AM
 */

#include <exports.h>
extern unsigned long timer_counter;

void C_IRQ_handler()
{
	//printf("IRQ Handler Called");
	handle_timer_irq();
	return;
}

static void handle_timer_irq(void)
{
	timer_counter++;
	reg_write(OSTMR_OSCR_ADDR, 0x0);

	return;
}
