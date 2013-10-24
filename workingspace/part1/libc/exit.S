@ exit.S: exit sycall wrapper
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Oct 14, 2013 9:00 AM

#include <bits/swi.h>
#include <bits/errno.h>

	.file	"exit.S"
	.text

	.global errno
	.global	exit
exit:
@	str lr, [sp]!
	ldr r8, [sp]!
@setting the errno before calling SWI
@	ldr r3, =errno	@ r3 points to errno
@	str r0, [r3]	@ set errno

	swi EXIT_SWI
