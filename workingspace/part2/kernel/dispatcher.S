@ dispatcher.S
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Oct 14, 2013 9:00 AM

.file "dispatcher"

.text
.global dispatcher
.global C_SWI_handler

dispatcher:
	SUB sp, sp, #4
	STMFD sp!, {r0 - r12, lr}
	MRS r2, spsr
	STR r2, [sp, #14 * 4]
	MOV r1, sp
	LDR r0, [lr, #-4]
	BIC r0, r0, #0xff000000
	BL C_SWI_handler
	LDR r2, [sp, #14 * 4]
	MSR spsr, r2
	LDMFD sp!, {r0 - r12 , lr}
	ADD sp, sp, #4
	MOVS pc, lr
