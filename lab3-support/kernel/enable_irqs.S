@ enable_IRQs.S: Enables IRQs since the handler is now in place
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Oct 24, 2013 9:00 AM

.file "enable_irqs"

.text
.global enable_irqs

enable_irqs:
		MRS r12, cpsr
		ORR r12, r12, #0x40
		MSR cpsr, r12
		MOV pc,lr 
	
