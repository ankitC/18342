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
	@STMFD sp!, {r0 - r3, r8, ip, lr}	@store user's gp registers

	STMFD sp!, {r0 - r11, ip, lr}

	LDR r12, =global_data				@Restoring r8 for lib funcs
	LDR r8, [r12]

	MRS r2, spsr						@get SPSR into gp registers
	@STR r2, [sp, #7 * 4]				@store SPSR above gp registers for re-entrancy

	STR r2, [sp, #14 * 4]

	MRS r12, cpsr
	BIC r12, r12, #PSR_IRQ				@enabling interrupts
	MSR cpsr, r12

	MOV r1, sp							@pointer to parameters on stack
	LDR r0, [lr, #-4]					@extract the SWI number
	BIC r0, r0, #0xff000000				@get SWI # by bit-masking

	BL C_SWI_handler					@Our SWI Handler

	MRS r2, cpsr
	ORR r2, #PSR_IRQ					@disabling interrupts for atomic restoration of registers
	MSR cpsr, r2

	LDR r2, [sp, #14 * 4]

	@LDR r2, [sp, #7 * 4]				@prepare to restore SPSR
	MSR spsr, r2						@restore SPSR from r2
	@ADD sp, sp, #4

	LDMFD sp!, {r0 - r11, ip, lr}

	@LDMFD sp!, {r0 - r3, r8, ip, lr}	@unstack user's registers
	ADD sp, sp, #4						@remove space used to store SPSR
	MOVS pc, lr							@return from handler
