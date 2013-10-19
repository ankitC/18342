#include<bits/fileno.h>
#include<bits/errno.h>

void main(int swino, char *args)
{
	switch (swino)
	{
		case(0x900001):

			break;

		case(0x900003):

			if(args[0]==STDIN_FILENO)
			{	int i;
				char *buf = args[1];		// Please check if we can write args[1][0] as args[1] is an array

				for(i=0;i < args [2])
				{
					char c = getc();
					if( c == '\0')
						break;

					if( c == 4 )
						break;

					if( c == '\b' || c == 127)		//TODO delete encountered
					{
						buf[i]='\0';
					}

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

			if(args[0] == STDOUT_FILENO)


			else
				args[0] = -EBADF;
			break;
			//TODO EFAULT set

		default:
			puts("Invalid SWI no.\n");
				args[0] =  -0xBADC0DE;
	}
}
