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
	@ldr r12, =kernelsp
	@ldr sp, [r12]					@Restore the kernel stack pointer

	LDR r2, [sp, #14 * 4]			@prepare to restore SPSR
	MSR spsr, r2					@restore SPSR from r2
	LDMFD sp!, {r0 - r12 , lr}		@unstack user's registers 
	SUB sp, sp, #12					@remove space used to store SPSR 	
	ldmfd sp!, {r0-r12, lr}			@Resoteing the U-Boot env.
	ldmfd sp!, {r0-r12, lr}	
	ldmfd sp!, {r0-r12, lr}
	mov pc, lr						@Seeya, our kernel!, going to U-Boot

