/* restore_old_SWI.c : Restores the original SWI handler on exit.
 *
 * Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
 *          Group Member 2: Jiten Mehta <jitenm>
 *		    Group Member 3: Ankit Chheda <achheda>
 * Date:    Oct 24, 2013 9:00 AM
 */

#include "kernel.h"

extern unsigned int *first_old_instr;
extern unsigned int *second_old_instr;
extern unsigned* old_SWI_addr;

/*
 * Restoring the original SWI_Handler
 * so that we don't break anything :D
 */
void restore_old_SWI(void)
{
	*old_SWI_addr =(unsigned) first_old_instr;
	*(old_SWI_addr + 1) =(unsigned) second_old_instr;
}
