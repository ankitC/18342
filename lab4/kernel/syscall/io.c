/** @file io.c
 *
 * @brief Kernel I/O syscall implementations
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 14 Oct 2007 00:07:38 -0400
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-11-16
 */

#include <types.h>
#include <bits/errno.h>
#include <bits/fileno.h>
#include <arm/physmem.h>
#include <syscall.h>
#include <exports.h>
#include <kernel.h>

/* Special characters */
#define EOT				0x04
#define BACKSPACE		0x08
#define DELETE			0x7f
#define NEW_LINE		0x0a
#define CARRAIGE_RETURN	0x0d

/* Special addresses */
#define ROM_END			0x00ffffff
#define SUP_STACK_END	0xa3ededf3
#define RAM_START		0xa0000000
#define HEAP_START		0xa3edf000
#define HEAP_END		0xa3efffff

/* Read count bytes (or less) from fd into the buffer buf. */
ssize_t read_syscall(int fd __attribute__((unused)), void *buff __attribute__((unused)), size_t count __attribute__((unused)))
{
	char* buf = (char*) buff;
	unsigned int i = 0;

	/* Invalid file descriptor */
	if(fd != STDIN_FILENO)
		return -EBADF;

	/* check for buffer address out of range */
	else if(!( (((unsigned int)buf <= SUP_STACK_END) && (((unsigned int)buf - count) >= RAM_START)) \
				|| (((unsigned int)buf >= HEAP_START) && (((unsigned int)buf + count) <= HEAP_END))))
		return -EFAULT;

	else
	{
		for(i = 0; i < count; i++)
		{
			char c = getc();

			/* Null */
			if(c == '\0')
				break;

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
ssize_t write_syscall(int fd  __attribute__((unused)), const void *buff  __attribute__((unused)), size_t count  __attribute__((unused)))
{
	char* buf = (char*) buff;
	unsigned int i = 0;

	/* Invalid file descriptor */
	if(fd != STDOUT_FILENO)
		return -EBADF;

	/* check for buffer address out of range */
	else if(!(((unsigned int)buf + count <= ROM_END) \
				|| (((unsigned int)buf <= SUP_STACK_END) && ((unsigned int)buf - count >= RAM_START)) \
				|| (((unsigned int)buf >= HEAP_START) && ((unsigned int)buf + count <= HEAP_END))))
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

