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

int hijack(uint32_t vector_addr, uint32_t new_addr, uint32_t* old_addr, \
		uint32_t* first_old_instr, uint32_t* second_old_instr)
{

	uint32_t*  swi_vector = (uint32_t *) vector_addr;
	uint32_t  swi_loader = *swi_vector;
	uint32_t  offset = swi_loader & (0x0FFF);
	
	printf("Going into Hijack\n");
	/* Address of the old handler */
	uint32_t*  old_SWI_container = (uint32_t*)(vector_addr + offset + 0x08);
	old_addr = (uint32_t*) *old_SWI_container;
	printf("SWI_vector:%p\n",swi_vector);
	printf("SWi_loader:%x\n",swi_loader);
	printf("vector_addr:%x\n",vector_addr);
	printf("Offset:%x\n",offset);
	printf("old_SWI_container:%p\n",old_SWI_container);
	printf("Old_addr:%p\n",old_addr);
	printf("Accessing mem\n");
	/* Extracting the first 2 instructions */
	*first_old_instr =  *(old_addr);
	printf("1\n");
	*second_old_instr = *(old_addr + 1);
	printf("2\n");
	/* Preparing instructions to substitute */
	uint32_t  first_new_instr = (uint32_t) LDR_PC_PC_minus_4;
	uint32_t  second_new_instr = new_addr;
	printf("Loading addresses\n");
	/* Wiring in our handler */
	*old_addr = first_new_instr;
	printf("3\n");
	*(old_addr + 1) = second_new_instr;
	
	printf("Returning from hijack\n");
	return 1;
}
