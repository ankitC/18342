@ init.S: initilizing the main user_space app
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Oct 14, 2013 9:00 AM

#include "kernel.h"
#include <bits/swi.h>
	
	.file	"init.S"
	.text
	.align 2
	
	.global	init

init:
	@STR r1,[sp]!			@Disabling Interrupts
	MRS r12, cpsr 
 	ORR r12, r12, #0x60 
 	
 	BIC r12, r12, #0x03 	@ Changing to user_mode
 	MSR cpsr, r12 
	
	ADR sp, addr			@ Setting up the userspace stack
	STMFD sp!, {r0-r1}
	
	mov lr, pc
	LDR pc, =USR_MAIN_ADDR
 	swi EXIT_SWI

addr:
	.word USR_STACK_BASE
