/** @file hello.c
 *
 * @brief Prints out Hello world using the syscall interface.
 *
 * Links to libc.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-10-29
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char** argv)
{
	const char hello[] = "Hello World\r\n";
	//unsigned long t = time();

	//time();
	write(STDOUT_FILENO, hello, sizeof(hello) - 1);
	/*sleep(1000);
	t = t;
	time();
	sleep(1000);
	time();*/
	//int i = 0;
	//for(i = 0; i <15 ; i++)
	while(1)
	{
		sleep(1000);
		printf("Time:%lu\n", time());
	}

	return 0;
}
