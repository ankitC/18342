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

int kmain(int argc, char** argv, uint32_t table)
{
	app_startup(); /* bss is valid after this point */
	global_data = table;

	/* Add your code here */
	int retval = 0;
	unsigned swi_dispatcher_addr =(unsigned) &dispatcher;
	unsigned  swi_vector = (unsigned) SWI_VECTOR_ADDR;
	if((retval = hijack(swi_vector, swi_dispatcher_addr, old_SWI_addr, \
					first_old_swii, second_old_swii)) == 0)
		printf("SWI handler installation failed!!\n");
	init(argc, argv);

	return 0;
}
