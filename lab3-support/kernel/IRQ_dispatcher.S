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
.global enale_irqs
.global disable_irqs

IRQ_dispatcher:
		STMFD sp!, {r0 - r12, lr}		@store registers
		@BL disable_irqs
		BL C_IRQ_handler
		@BL enable_irqs					@Our SWI Handler
		LDMFD sp!, {r0 - r12 , lr}		@restore registers
		SUBS pc, lr, #4					@Executing the same instruction as the one interrupted
