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
			restore_old_SWI();
			exit_to_kernel();
		
		case(0x900003):
			if(!(args[0] == STDIN_FILENO))
			{
				args[0] = -EBADF;
			}
			else if(!( (((unsigned int)buf >= 0xa0000000) && ((unsigned int)buf + args[2] <= 0xa2ffffff)) \
				    || (((unsigned int)buf >= 0xa3edf000) && ((unsigned int)buf + args[2] <= 0xa3efffff))))
			{
				args[0] = -EFAULT;
			}
			else
			{
				unsigned int i;
				for(i = 0; i < args [2]; i++)
				{
					char c = getc();

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
						putc(buf[i]);
						i++;
						break;
					}
					
					/* For all other (normal) characters */
					buf[i] = c;
					putc(buf[i]);
				}

				args[0] = i;	// return number of bytes read
			}
			
			puts("\n");
			break;

		case(0x900004):
			
			if(!(args[0] == STDOUT_FILENO))
			{
				args[0] = -EBADF;	// return bad fd error
			}
			else if(!(((unsigned int)buf + args[2] <= 0x00ffffff) \
					|| (((unsigned int)buf >= 0xa0000000) && ((unsigned int)buf + args[2] <= 0xa2ffffff)) \
				    || (((unsigned int)buf >= 0xa3edf000) && ((unsigned int)buf + args[2] <= 0xa3efffff))))
			{
				args[0] = -EFAULT;
			}
			else
			{
				unsigned int i ;
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
			}
			puts("\n");
			break;

		default:
			/* return invalid SWI_number error */
			puts("Invalid SWI no.\n");
			args[0] =  -0xBADC0DE;
			break;
	}
	return;
}
