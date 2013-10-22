/*
 * kernel.c: Kernel main (entry) function
 *
 * Author: Group Member 1<email address>
 *         Group Member 2 <email address>
 * Date:   The current time & date
 */

#include "kernel.h"

extern void init(int argc, char** argv);
extern void dispatcher();

/*
 * Variables to store the instructions of the
 * original SWI handler
 */
unsigned int *first_old_instr = 0;
unsigned int *second_old_instr = 0;
unsigned* old_SWI_addr = 0;

int main(int argc, char *argv[]) {

	unsigned*  swi_vector = (unsigned int *) SWI_VECTOR_ADDR;
	unsigned  swi_loader = *swi_vector;
	unsigned  offset = swi_loader & (0x0FFF);

	/* Address of the old SWI handler */
	unsigned*  old_SWI_container = (unsigned*) (SWI_VECTOR_ADDR + offset + 0x08);
	old_SWI_addr = (unsigned*) *old_SWI_container;
	/* Extracting the first 2 instructions */
	first_old_instr = (unsigned int *) *(old_SWI_addr);
	second_old_instr = (unsigned int *) *(old_SWI_addr + 1);

	/* Preparing instructions to substitute */
	unsigned int first_new_instr = (unsigned int) LDR_PC_PC_minus_4;
	unsigned int second_new_instr = (unsigned int) &dispatcher;

	/* Wiring in our handler */
	*old_SWI_addr = first_new_instr;
	*(old_SWI_addr + 1) = second_new_instr;

	init(argc, argv);

	/* Need to restore the handler */
	//*old_SWI_addr = first_old_instr;
	//*(old_SWI_addr + 1) = second_old_instr;

	return 0;
}
