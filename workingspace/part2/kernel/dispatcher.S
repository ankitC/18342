@ dispatcher.S: Dispatcher to preprocess the syscall
@				and dispatch the SWI to the handler.
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Oct 24, 2013 9:00 AM

.file "dispatcher"

.text
.global dispatcher
.global C_SWI_handler

dispatcher:
	SUB sp, sp, #4					@leave room on stack for SPSR
	STMFD sp!, {r0 - r12, lr}		@store user's gp registers
	MRS r2, spsr					@get SPSR into gp registers
	STR r2, [sp, #14 * 4]			@store SPSR above gp registers for re-entrancy
	MOV r1, sp						@pointer to parameters on stack
	LDR r0, [lr, #-4]				@extract the SWI number
	BIC r0, r0, #0xff000000			@get SWI # by bit-masking
	BL C_SWI_handler				@Our SWI Handler
	LDR r2, [sp, #14 * 4]			@prepare to restore SPSR
	MSR spsr, r2
	ADD sp, sp, #4					@restore SPSR from r2
	LDMFD sp!, {r1 - r12 , lr}		@unstack user's registers 
	ADD sp, sp, #4					@remove space used to store SPSR 
	MOVS pc, lr						@return from handler
