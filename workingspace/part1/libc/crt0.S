@ crt0.S: Execution startup routine
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    The current time & date

#include <bits/swi.h>
#include <bits/errno.h>

.file   "crt0.S"
.text

.globl errno
.global _start
_start:
		ldmfd sp!, {r0, r1}
		bl main

		ldr r3, =errno  @ r3 points to errno
		str r0, [r3]    @ set errno to what main returns
		swi EXIT_SWI
