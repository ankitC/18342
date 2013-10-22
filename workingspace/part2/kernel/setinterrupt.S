@ irqfiq.S: Disabling IRQ-FIQ
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Oct 14, 2013 9:00 AM

//#include "utilfuncs.h"

	.file	"setinterrupt.S"
	.text
	.align 2
	
	.global	setinterrupt

setinterrupt:
	STR r1,[sp]!
	MRS r1, cpsr 
 	ORR r1, r1, #0x60 
 	MSR cpsr, r1 
 	LDR r1,[sp]!
 	MOVS pc, lr
