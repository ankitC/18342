#include<bits/fileno.h>
#include<bits/errno.h>
#include <exports.h>

//char *buf;
void C_SWI_handler(int swino, unsigned* args)
{
	char* buf = (char*) args[1];
	switch (swino)
	{
		case(0x900001):

			break;

		case(0x900003):
			puts("Read syscall called");
			if(args[0]==STDIN_FILENO)
			{
				int i;
				for(i = 0; i < args [2]; i++)
				{
					char c = getc();
					if( c == '\0')
						break;
					/* CLTR+D */
					if( c == 4 )
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
						break;
					}

					buf[i] = c;
				}

				args[0] = i;
			}
			else
				args[0] = -EBADF;
			break;
			// TODO EFAULT set

		case(0x900004):
			puts("write syscall called");
			if(args[0] == STDOUT_FILENO)
			{
				int i ;
				for(i=0; i<args[2] ; i++)
				{
					if(buf[i] == '\0')
						break;
					putc(buf[i]);
				}

			}



			else
				args[0] = -EBADF;
			break;
			//TODO EFAULT set

		default:
			puts("Invalid SWI no.\n");
			args[0] =  -0xBADC0DE;
	}
}
