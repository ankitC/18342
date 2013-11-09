/* hijack.c: Hijacks the handler at provided vector address and
 *			substitutes the handler at new_addr while backing up
 *			the instructions in first_old_instr and second_old_instr.
 * Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
 *			Group Member 2: Jiten Mehta <jitenm>
 *			Group Member 3: Ankit Chheda <achheda>
 * Date:    Oct 27, 2013 9:00 PM
 */

#include <exports.h>
#include "kernel.h"

/* Code to wire in our handlers */
int hijack(uint32_t vector_addr, uint32_t new_addr, uint32_t* old_addr, \
		uint32_t* first_old_instr, uint32_t* second_old_instr)
{

	uint32_t* vector_ref = (uint32_t *) vector_addr;
	uint32_t  vector_loader = *vector_ref;
	uint32_t  offset = vector_loader & (0x0FFF);

	/* Address of the old handler */
	uint32_t*  old_addr_container = (uint32_t*)(vector_addr + offset + 0x08);
	old_addr = (uint32_t*) *old_addr_container;

	/* Extracting the first 2 instructions */
	*first_old_instr =  *(old_addr);
	*second_old_instr = *(old_addr + 1);

	/* Preparing instructions to substitute */
	uint32_t  first_new_instr = (uint32_t) LDR_PC_PC_minus_4;
	uint32_t  second_new_instr = new_addr;

	/* Wiring in our handler */
	*old_addr = first_new_instr;
	*(old_addr + 1) = second_new_instr;

	return 1;
}
