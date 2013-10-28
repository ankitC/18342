@ init.S: initilizing the evn for main user_space app
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Oct 24, 2013 9:00 AM

#include "kernel.h"
#include <bits/swi.h>

	.file	"init.S"
	.text
	.align 2

	.global	init

init:
	MRS r12, cpsr
 	ORR r12, r12, #0x60				@ Disabling IRQ and FIQ
 	BIC r12, r12, #0x03				@ Changing to user_mode
 	MSR cpsr, r12

@	LDR sp, =USR_STACK_BASE						@ Setting up the userspace stack
@	STMFD sp!, {r0-r1}				@ Pushing arguments on Userspace stack

	mov sp, r0
	mov lr, pc
	LDR pc, =USR_MAIN_ADDR

 	swi EXIT_SWI					@exit with the status returned by userspace
									@main program.
