/** @file sleep.S
 *
 * @brief sleep sycall wrapper
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-31
 */

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
