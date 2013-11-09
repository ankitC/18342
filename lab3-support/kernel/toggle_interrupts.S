@ toggle_interrupts.S: Enables and disables IRQs.
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Oct 24, 2013 9:00 AM

.file "toggle_interrputs"

.text
.global enable_irqs
.global disable_irqs

enable_irqs:
		MRS r12, cpsr
		BIC r12, r12, #0x80			@Unmask IRQs
		MSR cpsr, r12
		MOV pc,lr

disable_irqs:
		MRS r12, cpsr
		ORR r12, r12, #0xC0			@Mask IRQs
		MSR cpsr, r12
		MOV pc,lr

