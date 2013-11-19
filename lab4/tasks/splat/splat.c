/** @file splat.c
 *
 * @brief Displays a spinning cursor.
 *
 * Links to libc.
 *
 * Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
 *		   Group Member 2: Jiten Mehta <jitenm>
 *		   Group Member 3: Ankit Chheda <achheda>
 *
 */

#include <bits/fileno.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	/* unused arguments */
	argc = argc;
	argv = argv;

	while(1)
	{
		write(STDOUT_FILENO, "\r|", 2);
		sleep(200);
		write(STDOUT_FILENO, "\r/", 2);
		sleep(200);
		write(STDOUT_FILENO, "\r-", 2);
		sleep(200);
		write(STDOUT_FILENO, "\r\\", 2);
		sleep(200);
	}
	return 0;
}
