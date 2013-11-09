@ dispatcher.S: Dispatcher to preprocess the syscall
@				and dispatch the SWI to the handler.
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Oct 24, 2013 9:00 AM

.file "dispatcher"

.text
.global IRQ_dispatcher
.global C_IRQ_handler

IRQ_dispatcher:
		STMFD sp!, {r0 - r12, lr}		@store registers

		BL C_IRQ_handler

		MRS r12, cpsr					@enable interrupts
		BIC r12, r12, #0x80
		MSR cpsr, r12

		LDMFD sp!, {r0 - r12 , lr}		@restore registers

		SUBS pc, lr, #4					@lr points to PC + 4, so go
										@to the next instr in userspace
