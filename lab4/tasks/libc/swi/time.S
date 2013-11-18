/** @file time.S
 *
 * @brief time sycall wrapper
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-31
 */

#include <asm.h>
#include <bits/swi.h>
	.file "time.S"

	.text
	.global	time
FUNC(time)

time:
	stmfd sp!, {r1-r12,lr}  @ Backing up register
    swi TIME_SWI
 	ldmfd sp!, {r1-r12,lr}  @ Restoring registers
    mov pc, lr
