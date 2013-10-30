#include <exports.h>
#include <types.h>
#include <arm/timer.h>
#include <arm/reg.h>

volatile unsigned long timer_counter = 0;

void init_kern_timer(void)
{
	uint32_t clocks_till_interrupt = 0;
	uint32_t oier_register;

	/* Initilize the timer counter to zero */
	timer_counter = 0;

	/* Initialize the value to zero */
	reg_write(OSTMR_OSCR_ADDR, 0x0);

	clocks_till_interrupt = OSTMR_FREQ/(1000/TIMER_RESOLUTION);
	reg_write(OSTMR_OSMR_ADDR(0), clocks_till_interrupt);

	/* Activating OIER 0 */
	oier_register = reg_read(OSTMR_OIER_ADDR);
	oier_register = oier_register | OSTMR_OIER_E0;
	reg_write(OSTMR_OIER_ADDR, oier_register);

	return;
}

