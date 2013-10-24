#include<bits/fileno.h>
#include<bits/errno.h>
#include <exports.h>

//char *buf;

extern void restore(void);
extern void exit_to_kernel(void);

void C_SWI_handler(int swino, unsigned* args)
{
	char* buf = (char*) args[1];
	switch (swino)
	{
		case(0x900001):

			puts("Exit syscall called\n");
			printf("exit returning %d\n", args[0]);
			restore();
			puts("Restored\n");
			exit_to_kernel();
			break;

		case(0x900003):
			puts("Read syscall called\n");
			if(args[0]==STDIN_FILENO)
			{
				int i;
				for(i = 0; i < args [2]; i++)
				{
					char c = getc();
					printf("read character: %c\n", c);
					if(c == '\0')
						break;
					/* CLTR+D */
					if(c == 4)
						break;
					/* BACKSPACE or DEL */
					if( c == '\b' || c == 127)		//TODO delete encountered
					{
						buf[i-1]='\0';
						i--;
						puts("\b \b");
						break;
					}
					/* NEW LINE or CARRAIGE RETURN */
					if( c == '\n' || c == '\r')
					{
						buf[i] = c;
						printf("read newline or carraige return: %c\n", c);
						i++;
						break;
					}

					buf[i] = c;
					printf("read: buf[i] = %c\n", buf[i]);
				}

				args[0] = i;
				printf("read returning %d\n", args[0]);
			}
			else
			{
				args[0] = -EBADF;
				printf("read error: %d\n", args[0]);
			}
			break;
			// TODO EFAULT set

		case(0x900004):
			puts("write syscall called\n");
			if(args[0] == STDOUT_FILENO)
			{
				int i ;
				for(i=0; i<args[2] ; i++)
				{
					if(buf[i] == '\0')
						break;
					putc(buf[i]);
				}
				args[0] = i;
				printf("write returning %d\n", args[0]);
			}
			else
			{
				args[0] = -EBADF;
				printf("write error: %d\n", args[0]);
			}
			break;
			//TODO EFAULT set

		default:
			puts("Invalid SWI no.\n");
			args[0] =  -0xBADC0DE;
			printf("default: swi no = %d\n", args[0]);
	}
}
