@ crt0.S: Execution startup routine
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Oct 10 2013, 10:00 AM

#include <bits/swi.h>
#include <bits/errno.h>

.file   "crt0.S"
.text
.globl errno
.global _start
_start:
		ldmfd sp!, {r0}
		mov r1, sp
		bl main

