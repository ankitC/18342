#include <exports.h>

#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/timer.h>

#include "kernel.h"

uint32_t global_data;

extern void init(int argc, char** argv);
extern void dispatcher();
extern int hijack(uint32_t,uint32_t,uint32_t*,uint32_t*,uint32_t*);

unsigned int *first_old_swii = 0;
unsigned int *second_old_swii = 0;
unsigned* old_SWI_addr = 0;

unsigned* kernelsp = 0;

/*static uint32_t* prepare_user_stack(int argc, char** argv)
{
	uint32_t* stack_addr =(uint32_t*) USR_STACK_BASE;
	int i = 0;
	stack_addr--;
	*stack_addr =(unsigned) ((void*)0);

	for(i = argc - 1; i>=0; i--)
	{
		stack_addr--;
		*stack_addr = (uint32_t)argv[i];
	}

	stack_addr--;
	*stack_addr = (uint32_t)argc;

	return stack_addr;
}*/


int kmain(int argc, char** argv, uint32_t table, uint32_t* stackp)
{
	app_startup(); /* bss is valid after this point */
	global_data = table;
	kernelsp = stackp;
	/* Add your code here */
	int retval = 0;
	unsigned swi_dispatcher_addr =(unsigned) &dispatcher;
	unsigned  swi_vector = (unsigned) SWI_VECTOR_ADDR;
	if((retval = hijack(swi_vector, swi_dispatcher_addr, old_SWI_addr, \
					first_old_swii, second_old_swii)) == 0)
		printf("SWI handler installation failed!!\n");

//	unsigned* user_stack_ptr = prepare_user_stack(argc, argv);
//	init(user_stack_ptr);

	init(argc, argv);
	return 0;
}

