@ SWI_dispatcher.S: Dispatcher to preprocess the syscall
@				and dispatch the SWI to the handler.
@
@ Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
@          Group Member 2: Jiten Mehta <jitenm>
@		   Group Member 3: Ankit Chheda <achheda>
@ Date:    Oct 24, 2013 9:00 AM

#include <arm/psr.h>

.file "dispatcher"

.text
.global SWI_dispatcher
.global C_SWI_handler

SWI_dispatcher:

	SUB sp, sp, #4						@leave room on stack for SPSR
	
	STMFD sp!, {r0 - r11, ip, lr}

	LDR r12, =global_data				@Restoring r8 for lib funcs
	LDR r8, [r12]

	MRS r2, spsr						@get SPSR into gp registers
	
	STR r2, [sp, #14 * 4]

	MOV r1, sp							@pointer to parameters on stack
	
	STMFD sp, {sp,lr}^        			@store user sp and lr on the stack
    SUB   sp, sp,#8     

	MRS r12, cpsr
	BIC r12, r12, #PSR_IRQ				@enabling interrupts
	MSR cpsr, r12

	
	LDR r0, [lr, #-4]					@extract the SWI number
	BIC r0, r0, #0xff000000				@get SWI # by bit-masking

	BL C_SWI_handler					@Our SWI Handler

	
	MRS r2, cpsr
	ORR r2, #PSR_IRQ					@disabling interrupts for atomic restoration of registers
	MSR cpsr, r2

	LDMFD sp, {sp,lr}^
    ADD sp, sp,#8


	LDR r2, [sp, #14 * 4]				@prepare to restore SPSR
	MSR spsr, r2						@restore SPSR from r2
	

	LDMFD sp!, {r0 - r11, ip, lr}

	ADD sp, sp, #4						@remove space used to store SPSR
	MOVS pc, lr							@return from handler
