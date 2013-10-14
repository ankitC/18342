@ write.S: write sycall wrapper
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Oct 14, 2013 9:00 AM

#include <bits/swi.h>
#include <bits/errno.h>

	.file	"write.S"
	.text

	.global errno
	.global	write
write:
	str lr, [sp]!
	stmfd sp!, {r1-r12}  @ Backing up register
    swi WRITE_SWI
    cmp r0, #0		@ check the return value of SWI
    bge ret			@ if no error, then return

	@ otherwise, set errno accordingly
    mov r1, #-1
	mul r1, r0, r1
    ldr r3, =errno	@ r3 points to errno
	str r1, [r3]	@ set errno
	mov r0, #-1		@ return -1

ret:
	ldmfd sp!, {r1-r12}  @ Restoring registers
    ldr pc, [sp]!
