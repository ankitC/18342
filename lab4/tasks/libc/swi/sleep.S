@ sleep.S: sleep syscall wrapper
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Oct 14, 2013 9:00 AM

#include <asm.h>
#include <bits/swi.h>

	.file "sleep.S"
	.text
	.global sleep

FUNC(sleep)

sleep:
	stmfd sp!, {r1-r12,lr}  @ Backing up register
    swi SLEEP_SWI
 	ldmfd sp!, {r1-r12,lr}  @ Restoring registers
    mov pc, lr
