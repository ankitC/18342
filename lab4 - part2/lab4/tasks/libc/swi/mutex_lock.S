@ mutex_lock.S: mutex_lock syscall wrapper
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Nov 14, 2013 9:00 PM

#include <bits/swi.h>
#include <bits/errno.h>
#include <asm.h>

	.file "mutex_lock.S"
	.text

	.global errno
	.global	mutex_lock

FUNC(mutex_lock)
	stmfd sp!, {r1-r12,lr}  @ Backing up registers
	swi MUTEX_LOCK
	cmp r0, #0		@ Check the return value of SWI
	bge ret			@ if no error, then return

	@ otherwise, set errno accordingly
	mov r1, #-1
	mul r1, r0, r1
	ldr r3, =errno	@ r3 points to errno
	str r1, [r3]	@ set errno
	mov r0, #-1		@ return -1

ret:
	ldmfd sp!, {r1-r12,lr}  @ Restoring registers
	mov pc,lr
