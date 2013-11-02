/** @file typo.c
 *
 * @brief Echos characters back with timing data.
 *
 * Links to libc.
 * Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
 *		   Group Member 2: Jiten Mehta <jitenm>
 *		   Group Member 3: Ankit Chheda <achheda>
 *

*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 150

int main(int argc, char** argv)
{
	while(1)
	{
		write(STDOUT_FILENO, "> " , 2);
		unsigned long orig_time = time();
		char input[MAX_LINE_LENGTH];
		int r = read(STDIN_FILENO, input , MAX_LINE_LENGTH);
		unsigned long final_time = time();
		write(STDOUT_FILENO, input ,r);
		write(STDOUT_FILENO, "\n", 1);
		time();
		write(STDOUT_FILENO, "\n", 1);
		unsigned long time_to_type = final_time - orig_time;
		char *buf = (void *)0;
		sprintf(buf, "%lu\n", time_to_type);
		//write(STDOUT_FILENO, buf, 16);
		puts("hello puts\n");
		puts(buf);
		puts("\n");
	}
	return 0;
}
