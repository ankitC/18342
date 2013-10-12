@ exit.S: exit sycall wrapper
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    The current time & date

#include <bits/swi.h>
#include <bits/errno.h>

	.file	"exit.S"
	.text

	.globl errno
	.global	exit
exit:
	str lr, [sp]!

@ do we need to set errno here? chheda pls confirm
	ldr r3, =errno	@ r3 points to errno
	str r0, [r3]	@ set errno

	swi EXIT_SWI

@ since exit does not return, i dont think this is required. chheda pls confirm
	cmp r0, #0
	bge ret
	mov r0, #-1
ret:
	ldr pc, [sp]!
