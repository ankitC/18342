@ exit_to_kernel.S: Exiting the kernel and gracefully
@					restore the U-Boot env.
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Oct 24, 2013 9:00 AM


	.file	"exit_to_kernel.S"
	.text
	.align 2

	.global	exit_to_kernel

exit_to_kernel:
	LDR r0, [r1]
	LDR r2, [sp, #14 * 4]			@prepare to restore SPSR
	MSR spsr, r2					@restore SPSR from r2
	ADD sp, sp, #4
	LDMFD sp!, {r1 - r12 , lr}		@unstack user's registers

	ADD sp, sp, #96
	ldmfd sp!, {r1-r12, lr}
	mov pc, lr						@Seeya, our kernel!, going to U-Boot

