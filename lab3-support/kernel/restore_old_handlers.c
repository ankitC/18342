/* restore_old_SWI.c : Restores the original SWI handler on exit.
 *
 * Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
 *          Group Member 2: Jiten Mehta <jitenm>
 *		    Group Member 3: Ankit Chheda <achheda>
 * Date:    Oct 24, 2013 9:00 AM
 */

#include "kernel.h"
#include <exports.h>
extern unsigned int first_old_swii;
extern unsigned int second_old_swii;

extern unsigned int first_old_irqi;
extern unsigned int second_old_irqi;


/*
 * Restoring the original SWI_Handler and IRQ_handler
 * so that we don't break anything :D
 */
void restore_old_handlers(void)
{
	uint32_t temp = SWI_VECTOR_ADDR;
	uint32_t* swi_vector = (uint32_t*) temp;
	uint32_t  swi_loader = *swi_vector;
	uint32_t  offset = swi_loader & (0x0FFF);

	/* Address of the old handler */
	uint32_t*  old_SWI_container = (uint32_t*)( SWI_VECTOR_ADDR + offset + 0x08);
	uint32_t* old_addr = (uint32_t*) *old_SWI_container;

	/* Restoring SWI Handler */
	*old_addr = first_old_swii;
	*(old_addr + 1) = second_old_swii;

	temp = IRQ_VECTOR_ADDR;
	swi_vector = (uint32_t*) temp;
	swi_loader = *swi_vector;
	offset = swi_loader & (0x0FFF);
	old_SWI_container = (uint32_t*)(IRQ_VECTOR_ADDR + offset + 0x08);
	old_addr = (uint32_t*) *old_SWI_container;

	/* Restoring IRQ Handler */
	*old_addr = first_old_irqi;
	*(old_addr + 1) = second_old_irqi;
}
