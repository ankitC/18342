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
	ldr r12, =kernelsp
	ldr sp, [r12]
	ldmfd sp!, {r0-r12, lr}
	mov pc, lr

