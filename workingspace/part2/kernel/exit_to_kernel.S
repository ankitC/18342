@ exit_to_kernel.S: initilizing the main user_space app
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Oct 14, 2013 9:00 AM


	.file	"exit_to_kernel.S"
	.text
	.align 2
	
	.global	exit_to_kernel

exit_to_kernel:
	@LDR r2, [sp, #14*4]
	@MSR spsr, r2
	LDMFD sp!, {r0 - r12 , lr}
	ADD sp, sp, #4
	
	@ldr r8, [sp]!
	ldmfd sp!, {r0 - r12, pc}
	@ADD sp, sp, #44
	@ldr r12, =kernellr 
	@ldr pc , [r12]
	
	
