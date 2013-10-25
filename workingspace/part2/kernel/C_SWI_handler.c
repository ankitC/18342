#include <bits/fileno.h>
#include <bits/errno.h>
#include <exports.h>

/* Special characters */
#define EOT				4
#define BACKSPACE		8
#define DELETE			127
#define NEW_LINE		10
#define CARRAIGE_RETURN	13

extern void restore(void);
//char *buf;

extern void restore_old_SWI(void);
extern void exit_to_kernel(void);

void C_SWI_handler(int swino, unsigned* args)
{
	char* buf = (char*) args[1];
	switch (swino)
	{
		case(0x900001):

			//puts("Exit syscall called\n");
			//printf("exit returning %d\n", args[0]);

			restore_old_SWI();
			//puts("Restored\n");
			exit_to_kernel();
		case(0x900003):
			//puts("Read syscall called\n");
			if(args[0] == STDIN_FILENO)
			{
				int i;
				for(i = 0; i < args [2]; i++)
				{
					char c = getc();
					//printf("read character: %c\n", c);

					if(c == '\0')
						break;

					/* Ctrl + D */
					if(c == EOT)
						break;

					/* Backspace or Delete */
					if( c == BACKSPACE || c == DELETE)
					{
						i--;
						buf[i]='\0';
						i--;
						puts("\b \b");
						continue;
					}

					/* New line or Carraige return */
					
					if(c == NEW_LINE || c == CARRAIGE_RETURN)
					{
						buf[i] = c;
						//putc(buf[i]);
						//printf("read newline or carraige return: %c\n", c);
						i++;
						break;
					}
					
					/* For all other (normal) characters */
					buf[i] = c;
					putc(buf[i]);
					//printf("read: buf[i] = %c\n", buf[i]);
				}

				args[0] = i;	// return number of bytes read
				//printf("read returning %d\n", args[0]);
				//break;
			}
			else
			{
				args[0] = -EBADF;	// return bad fd error
				//printf("read error: %d\n", args[0]);
				break;
			}
			//printf("exiting read\n");
			break;
			// TODO EFAULT set

		case(0x900004):
			//puts("write syscall called\n");
			if(args[0] == STDOUT_FILENO)
			{
				int i ;
				for(i=0; i<args[2] ; i++)
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

				args[0] = i;	// return number of bytes written
				//printf("write returning %d\n", args[0]);
			}
			else
			{
				args[0] = -EBADF;	// return bad fd error
				//printf("write error: %d\n", args[0]);
			}
			//printf("exiting write\n");
			break;
			//TODO EFAULT set

		default:
			/* return invalid SWI_number error */
			puts("Invalid SWI no.\n");
			args[0] =  -0xBADC0DE;
			//printf("default: swi no = %d\n", args[0]);
			break;
	}
	//printf("exiting C handler\n");
	return;
	//TODO: return value = ssize_t?
}
