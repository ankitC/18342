/** @file main.c
 *
 * @brief Kernel main function.
 *
 * @author: Group Member 1: Arjun Ankleshwaria <aanklesh>
 *          Group Member 2: Jiten Mehta <jitenm>
 *		    Group Member 3: Ankit Chheda <achheda>
 *
 * @date:   Nov 18, 2013 9:00 PM
 */

#include <exports.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include <arm/reg.h>
#include <kernel_helper.h>
#include <lock.h>
#include <device.h>

#include <extern_helper.h>

//#define debug

/* Variable to hold global data */
uint32_t global_data;


/* Static helper functions */
static uint32_t* prepare_user_stack(int, char**);
static void irq_init();

/* IRQ Stack */
char* irq_stack;

/* Variables to hold the data of original SWI Handler */
unsigned int first_old_swii;
unsigned int second_old_swii;

/* Variables to hold the data of original IRQ Handler */
unsigned int first_old_irqi;
unsigned int second_old_irqi;

unsigned* kernelsp = 0;

int kmain(int argc, char** argv, uint32_t table, uint32_t* stackp)
{
	app_startup(); /* bss is valid after this point */
	global_data = table;
	kernelsp = stackp;

#ifdef debug
	printf("Starting to wire in dispatcher.\n");
#endif

	int retval = 0;
	unsigned* old_SWI_addr = 0;
	unsigned* old_IRQ_addr = 0;

	/* Hijacking SWI handler */
	unsigned swi_dispatcher_addr =(unsigned) &SWI_dispatcher;
	unsigned swi_vector = (unsigned) SWI_VECTOR_ADDR;

#ifdef debug
	printf("Hijacking SWI Handler\n");
#endif

	if((retval = hijack(swi_vector, swi_dispatcher_addr, old_SWI_addr, \
					&first_old_swii, &second_old_swii)) == 0)
		printf("SWI handler installation failed!!\n");

#ifdef debug
	printf("SWI handler Hijacked\n");
#endif

	/* Hijacking IRQ handler and starting the timer */
	unsigned irq_dispatcher_addr =(unsigned) &irq_wrapper;
	unsigned irq_vector = (unsigned) IRQ_VECTOR_ADDR;

	if((retval = hijack(irq_vector, irq_dispatcher_addr, old_IRQ_addr, \
					&first_old_irqi, &second_old_irqi)) == 0)
		printf("IRQ handler installation failed!!\n");

#ifdef debug
	printf("Wired in the dispatcher for IRQs\n");
#endif

	/* Initialize all the mutices */
	mutex_init();

	/* Initialize the sleep queue and next match for all devices */
	dev_init();

	/* Enabling IRQs and starting the timer for the kernel*/
	irq_init();
	init_kern_timer();

#ifdef debug
	printf("Timer init done.\n");
#endif

	/* Preparing the user stack and switching to userspace */
	unsigned* user_stack_ptr = prepare_user_stack(argc, argv);

#ifdef debug
	printf("Init stack for userspace...Done!\n");
#endif

	/* Init the userspace program */
	init(user_stack_ptr);

	/* CODE never reaches here */
	return 0;
}


/* Preparing user Stack */
static uint32_t* prepare_user_stack(int argc, char** argv)
{
	uint32_t* stack_addr =(uint32_t*) USR_STACK_BASE;
	int i = 0;
	stack_addr--;
	*stack_addr =(unsigned) ((void*)0);

#ifdef debug
	printf("usr_stack_ptr = %p \n", stack_addr);
#endif

	/* Full descending stack */
	for(i = argc - 1; i >= 0; i--)
	{
		stack_addr--;
		*stack_addr = (uint32_t)argv[i];

#ifdef debug
		printf("usr_stack_ptr = %p \n", stack_addr);
#endif

	}
	stack_addr--;
	*stack_addr = (uint32_t)argc;

#ifdef debug
	printf("usr_stack_ptr = %d \n", *stack_addr);
#endif

	return stack_addr;
}

/* Initializing the IRQs */
static void irq_init(void)
{
	uint32_t icmr_mask, iclr_reg, iclr_mask;

	/* Init the ICMR, unmask the interrupt for our OSTMR */
	icmr_mask = (0x1 << INT_OSTMR_0);

#ifdef debug
	printf("ICMR Mask: %x\n", icmr_mask);
#endif

	reg_write(INT_ICMR_ADDR, icmr_mask);
	iclr_reg = reg_read(INT_ICLR_ADDR);
	iclr_mask = ~(0x1 << INT_OSTMR_0);
	iclr_reg &= iclr_mask;

#ifdef debug
	printf("ICLR Mask: %x\n", iclr_reg);
#endif

	reg_write(INT_ICLR_ADDR, iclr_reg);

	/* Enabling the IRQs */
	enable_interrupts();

	return;
}
