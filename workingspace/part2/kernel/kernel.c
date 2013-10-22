/*
 * kernel.c: Kernel main (entry) function
 *
 * Author: Group Member 1 <email address>
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
unsigned* first_old_instr = 0;
unsigned* second_old_instr = 0;

int main(int argc, char *argv[]) {

	unsigned* swi_vector = (unsigned*) SWI_VECTOR_ADDR;
	unsigned swi_loader = *swi_vector;
	unsigned offset = swi_loader && (0xFFFFF000);
	unsigned* old_SWI_addr = swi_vector + offset + 0x08;

	/* Extracting the first 2 instructions */
	first_old_instr = (unsigned*)	*(old_SWI_addr);
	second_old_instr = (unsigned*) *(old_SWI_addr + 1);

	/* Preparing instructions to substitute */
	unsigned first_new_instr = (unsigned) LDR_PC_PC_minus_4;
	unsigned second_new_instr = (unsigned) &dispatcher;

	/* Wiring in our handler */
	*old_SWI_addr = first_new_instr;
	*(old_SWI_addr + 1) = second_new_instr;

	init(argc, argv);

	/* Need to restore the handler */
	return 0;
}

