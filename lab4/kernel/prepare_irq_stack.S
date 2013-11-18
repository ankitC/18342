@ prepare_irq_stack.S: Preparing the stack for IRQ mode
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Oct 24, 2013 9:00 AM

	.file	"prepare_irq_stack.S"
	.text
	.align 2

	.global	prepare_irq_stack

prepare_irq_stack:
	mrs r12, cpsr                  @ change mode bits in CPSR to <flags>_IRQ
	bic r12, r12, #0x1
	msr cpsr, r12                  @switch to IRQ mode
	mov sp, r0                     @point sp_irq to allocated irq_stack
	mov r1, #0x13
	mrs r12, cpsr                  @ change mode bits in CPSR to <flags>_SVC
	orr r12, r12, r1
	msr cpsr, r12                  @switch back to SVC mode
	mov	pc, lr
