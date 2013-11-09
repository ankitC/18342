/* C_SWI_handler.c : SWI handler for servicing read, write
 *					and exit syscalls.
 *
 * Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
 *          Group Member 2: Jiten Mehta <jitenm>
 *		    Group Member 3: Ankit Chheda <achheda>
 * Date:    Oct 24, 2013 9:00 AM
 */
#include <bits/fileno.h>
#include <bits/errno.h>
#include <exports.h>
#include <arm/timer.h>
/* Special characters */
#define EOT				4
#define BACKSPACE		8
#define DELETE			127
#define NEW_LINE		10
#define CARRAIGE_RETURN	13

/* Helper functions */
extern void restore_old_handlers(void);
extern void exit_to_kernel(int status);
extern void disable_irqs(void);

extern char* irq_stack;
extern volatile unsigned long timer_counter;

int C_SWI_handler(int swino, unsigned* args)
{
	char* buf = (char*) args[1];
	unsigned int i = 0;
	int exit_status = 0;
	switch (swino)
	{
		/* EXIT syscall */
		case(0x900001):
			printf("Exiting\n");
			exit_status = (int) args[0];
			disable_irqs();
			restore_old_handlers();
			free(irq_stack);
			exit_to_kernel(exit_status);
			break;

			/* Read Syscall*/
		case(0x900003):
			/* Invalid file descriptor */
			if(!(args[0] == STDIN_FILENO))
				return -EBADF;

			else if(!( (((unsigned int)buf <= 0xa3ededf3) && (((unsigned int)buf - args[2]) >= 0xa0000000)) \
						|| (((unsigned int)buf >= 0xa3edf000) && (((unsigned int)buf + args[2]) <= 0xa3efffff))))
			{
				return -EFAULT;
			}
			else
			{
				for(i = 0; i < args [2]; i++)
				{
					char c = getc();
					if(c == '\0'){
						printf("Got Null at i=%d\n", i);
						break;
					}
					/* Ctrl + D */
					if(c == EOT)
						break;

					/* Backspace or Delete */
					if( c == BACKSPACE || c == DELETE)
					{
						if(i>0)
						{
							i--;
							buf[i]='\0';
							i--;
							puts("\b \b");
							continue;
						}
						i--;
						continue;
					}

					/* New line or Carraige return */
					if(c == NEW_LINE || c == CARRAIGE_RETURN)
					{
						buf[i] = c;
						putc('\n');
						i++;
						break;
					}

					/* For all other (normal) characters */
					buf[i] = c;
					putc(buf[i]);
				}
			}
			/* Taking the prompt to new line if the buffer is full*/
			break;

		/* Write syscall */
		case(0x900004):
			/* Invalid file descriptor */
			if(!(args[0] == STDOUT_FILENO))
		{
			return -EBADF;
		}
			else if(!(((unsigned int)buf + args[2] <= 0x00ffffff) \
						|| (((unsigned int)buf <= 0xa3ededf3) && ((unsigned int)buf - args[2] >= 0xa0000000)) \
						|| (((unsigned int)buf >= 0xa3edf000) && ((unsigned int)buf + args[2] <= 0xa3efffff))))
			{
				return -EFAULT;
			}
			else
			{
				for(i = 0; i < args[2]; i++)
				{
					if(buf[i] == '\0')
						break;
					putc(buf[i]);
					if(buf[i] == '\n')
					{
						i++;
						break;
					}
				}
			}
			break;
		/* time syscall */
		case(0x900006):
			//printf("%lu\n", timer_counter * TIMER_RESOLUTION);
			return(timer_counter * TIMER_RESOLUTION);

		/* Sleep Syscall */
		case(0x900007):
		/* Invalid args or zero, then simply return */
			if(args[0] <= 0)
				return 0;
			/* Wait till the time, rounding-up to the nearest multiple of 10 */
			uint32_t ticks_to_sleep = timer_counter + (args[0])/TIMER_RESOLUTION;
//			printf("timer_counter = %lu, ticks_to_sleep = %u \n",timer_counter, ticks_to_sleep);
			while(timer_counter < ticks_to_sleep);
//			printf("Returning");
			return 1;

		default:
			/* return invalid SWI_number error */
			printf("SWI No:%x\n", swino);
			puts("Invalid SWI no.\n");
			return  0xBADC0DE;
	}
	return i;
}
