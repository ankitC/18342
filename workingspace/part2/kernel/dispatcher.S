@ init.S: initilizing the main user_space app
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Oct 14, 2013 9:00 AM

#include "kernel.h"

	.file	"dispatcher.S"
	.text
	.align 2
	
	.global	dispatcher

	ldr pc, lr
