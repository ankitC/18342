#include <exports.h>

#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/timer.h>

#include "kernel.h"

/* Variable to hold global data */
uint32_t global_data;

/* External functions */
extern void init(uint32_t*);
extern void SWI_dispatcher();
extern void IRQ_dispatcher();
extern int hijack(uint32_t,uint32_t,uint32_t*,uint32_t*,uint32_t*);
extern void	init_kern_timer();
extern void enable_irqs();

/* Variables to hold the data of original SWI Handler */
unsigned int *first_old_swii = 0;
unsigned int *second_old_swii = 0;
unsigned* old_SWI_addr = 0;

/* Variables to hold the data of original IRQ Handler */
unsigned int *first_old_irqi = 0;
unsigned int *second_old_irqi = 0;
unsigned* old_IRQ_addr = 0;

unsigned* kernelsp = 0;

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
	for(i = argc - 1; i>=0; i--)
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



int kmain(int argc, char** argv, uint32_t table, uint32_t* stackp)
{
	app_startup(); /* bss is valid after this point */
	global_data = table;
	kernelsp = stackp;

	int retval = 0;
	/* Hijacking IRQ handler and starting the timer */
	unsigned irq_dispatcher_addr =(unsigned) &IRQ_dispatcher;
	unsigned irq_vector = (unsigned) IRQ_VECTOR_ADDR;
	if((retval = hijack(irq_vector, irq_dispatcher_addr, old_IRQ_addr, \
					first_old_irqi, second_old_irqi)) == 0)
		printf("IRQ handler installation failed!!\n");

	/* Enabling IRQs and starting the timer for the kernel*/
	enable_irqs();
	init_kern_timer();

	/* Hijacking SWI handler */
	unsigned swi_dispatcher_addr =(unsigned) &SWI_dispatcher;
	unsigned  swi_vector = (unsigned) SWI_VECTOR_ADDR;

		if((retval = hijack(swi_vector, swi_dispatcher_addr, old_SWI_addr, \
					first_old_swii, second_old_swii)) == 0)
		printf("SWI handler installation failed!!\n");

	/* Preparing the user stack and switching to userspace */
	unsigned* user_stack_ptr = prepare_user_stack(argc, argv);
	init(user_stack_ptr);

	return 0;
}

