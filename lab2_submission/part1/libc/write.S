@ write.S: write sycall wrapper
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    The current time & date

#include <bits/swi.h>
#include <bits/errno.h>

	.file	"write.S"
	.text

	.globl errno
	.global	write
write:
	str lr, [sp]!
    swi WRITE_SWI
    cmp r0, #0
    bge ret			@ if no error, then return

	@ otherwise, set errno accordingly
    mov r1, #-1
	mul r1, r0, r1
    ldr r3, =errno	@ r3 points to errno
	str r1, [r3]	@ set errno
	mov r0, #-1		@ return -1

ret:
    ldr pc, [sp]!
