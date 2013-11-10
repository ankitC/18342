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
	int i = 0; 
	const char hello[] = "Hello World\r\n";
	write(STDOUT_FILENO, hello, sizeof(hello) - 1);
	for(i = 0 ; i < argc ; i++)
	printf("Args:%s\n",argv[i]);
	return 0;
}
