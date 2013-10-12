@ write.S: write sycall wrapper
@
@ Authors: Group Member 1 <email address>
@          Group Member 2 <email address>
@ Date:    The current time & date

//#include <errno.h>
#include <bits/swi.h>

	.file	"write.S"
	.text

	.global	write
write:
	@ Needs more code.
	STMFD sp!, {lr}
	SWI WRITE_SWI
	CMP r0, #0
	LDMGEIA sp!, {pc}
	
