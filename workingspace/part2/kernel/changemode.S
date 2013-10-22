@ switch_to_user_mode.S: Switching to user mode
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Oct 14, 2013 9:00 AM

//#include "utilfuncs.h"

	.file	"switch_to_user_mode.S"
	.text
	.align 2
	
	.global	switch_to_user_mode

switch_to_user_mode:
	STR r1, [sp]!
	MRS r1, cpsr 
 	BIC r1, r1, #0x03 
 	MSR cpsr, r1 
 	LDR r1, [sp]!
 	MOVS pc, lr
	
