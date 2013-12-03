/** @file io.c
 *
 * @brief Kernel I/O syscall implementations
 *
 * @author Arjun Ankleshwaria <aanklesh>
 *         Jiten Mehta <jitenm>
 *         Ankit Chheda <achheda>
 *
 * @date   17 Nov 2013  5:00 pm
 */

#include <types.h>
#include <config.h>
#include <bits/errno.h>
#include <bits/fileno.h>
#include <arm/physmem.h>
#include <syscall.h>
#include <exports.h>
#include <kernel.h>
#include <chars.h>

/* Read count bytes (or less) from fd into the buffer buf. */
ssize_t read_syscall(int fd, void *buff, size_t count)
{
	char* buf = (char*) buff;
	unsigned int i = 0;

	/* Invalid file descriptor */
	if(fd != STDIN_FILENO)
		return -EBADF;

	/* check for buffer address out of range */
	else if(!( (((unsigned int)buf <= SVC_STACK_END) && \
					(((unsigned int)buf - count) >= OS_RAM_START)) \
				|| (((unsigned int)buf >= OS_HEAP_START) && \
					(((unsigned int)buf + count) <= OS_HEAP_END))))
		return -EFAULT;

	else
	{
		for(i = 0; i < count; i++)
		{
			char c = getc();

			/* Ctrl + D */
			if(c == EOT)
				break;

			/* Backspace or Delete */
			if(c == BACKSPACE || c == DELETE)
			{
				if(i > 0)
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
	return i;
}

/* Write count bytes to fd from the buffer buf. */
ssize_t write_syscall(int fd, const void *buff, size_t count)
{
	char* buf = (char*) buff;
	unsigned int i = 0;

	/* Invalid file descriptor */
	if(fd != STDOUT_FILENO)
		return -EBADF;

	/* check for buffer address out of range */
	else if(!(((unsigned int)buf + count <= OS_ROM_END) \
				|| (((unsigned int)buf <= SVC_STACK_END) \
					      && ((unsigned int)buf - count >= OS_RAM_START)) \
				|| (((unsigned int)buf >= OS_HEAP_START) \
					      && ((unsigned int)buf + count <= OS_HEAP_END))))
		return -EFAULT;

	else
		for(i = 0; i < count; i++)
		{
			if(buf[i] == '\0')
				break;
			putc(buf[i]);
		}
	return i;
}

