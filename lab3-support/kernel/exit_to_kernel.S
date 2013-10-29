@ exit_to_kernel.S: Exiting the kernel and gracefully
@					restore the U-Boot env.
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@	   Group Member 3: Ankit Chheda <achheda>
@ Date:    Oct 24, 2013 9:00 AM


	.file	"exit_to_kernel.S"
	.text
	.align 2

	.global	exit_to_kernel

exit_to_kernel:
	@ldr r0, r1				@Storing the return value into r0
	ldr r12, =kernelsp
	ldr sp, [r12]				@Restore the kernel stack pointer
	ldmfd sp!, {r1-r12, lr}			@Resoteing the U-Boot env.
	mov pc, lr				@Seeya, our kernel!, going to U-Boot

