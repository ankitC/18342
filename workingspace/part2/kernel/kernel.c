/*
 * kernel.c: Kernel main (entry) function.
 *			 Wires in our SWI handler and provides for
 *			 the backup of the original instructions.
 *			 Calls the  init() for initializing the
 *			 userspace env.
 *
 * Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
 *			Group Member 2: Jiten Mehta <jitenm>
 *			Group Member 3: Ankit Chheda <achheda>
 * Date:    Oct 24, 2013 9:00 AM
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

/* Saving the env of U-Boot */
unsigned* kernellr = 0;
unsigned* kernelsp = 0;

int main(int argc, char *argv[]) {
	/* Finding the original offset in the Vector table */
	unsigned*  swi_vector = (unsigned int *) SWI_VECTOR_ADDR;
	unsigned  swi_loader = *swi_vector;
	unsigned  offset = swi_loader & (0x0FFF);

	/* Address of the old SWI handler */
	unsigned*  old_SWI_container = (unsigned*)(SWI_VECTOR_ADDR + offset + 0x08);
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

/* Program never reaches here, if we return here,
 * there is a problem */
	return -255;
}
