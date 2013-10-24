/*
 * kernel.c: Kernel main (entry) function
 *
 * Author: Group Member 1<email address>
 *         Group Member 2 <email address>
 * Date:   The current time & date
 */

#include "kernel.h"

extern unsigned int *first_old_instr;
extern unsigned int *second_old_instr;
extern unsigned* old_SWI_addr;


void restore_old_SWI(void)
{
	*old_SWI_addr =(unsigned) first_old_instr;
	*(old_SWI_addr + 1) =(unsigned) second_old_instr;
}
