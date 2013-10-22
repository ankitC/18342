@ init.S: initilizing the main user_space app
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Oct 14, 2013 9:00 AM

#include "kernel.h"

	.file	"init.S"
	.text
	.align 2
	
	.global	init

	@STR r1,[sp]!			@Disabling Interrupts
	MRS r12, cpsr 
 	ORR r12, r12, #0x60 
 	
 	BIC r12, r12, #0x03 	@Changing to user_mode
 	MSR cpsr, r12 
	
	LDR sp, =USR_STACK_BASE @Setting up the userspace stack
	STMFD sp!, {r0-r1}
	
	LDR r12, =USR_MAIN_ADDR
 	bl r12
 	
 	swi EXIT_SWI
