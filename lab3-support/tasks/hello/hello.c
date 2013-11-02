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
	unsigned long t = time();
	//t = t;
	//printf("%lu\n", t);
	time();
	write(STDOUT_FILENO, hello, sizeof(hello) - 1);
//sleep(400);
	sleep(1000);
	t = t;
	time();
	sleep(1000);
	time();
	//t = time();
	//printf("%lu\n", t);
	//int t = time();
	//printf("Time %d\n", t);
	//	sprintf(temp,"%d,\n",t);
	//	printf(temp);
	return 0;
}
