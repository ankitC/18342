@ task_create.S: task_create syscall wrapper
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Nov 16, 2013 9:00 PM

#include <asm.h>
#include <bits/swi.h>
#include <bits/errno.h>

	.file "task_create.S"
	.text

	.global errno
	.global task_create

FUNC(task_create)
	stmfd sp!, {r1-r12,lr}	@ Backing up the registers
	swi CREATE_SWI

	@ return value not expected from SWI
	@ if no error, then swi will not return here
	@ else set errno accordingly

	mov r1, #-1
	mul r1, r0, r1
	ldr r3, =errno	@ r3 points to errno
	str r1, [r3]	@ set errno
	mov r0, #-1		@ return -1

	ldmfd sp!, {r1-r12,lr}	@ Restoring registers
	mov pc,lr
