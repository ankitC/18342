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
#include<stdlib.h>
#include <stdio.h>
int main(int argc, char** argv)
{
	const char hello[] = "Hello World\r\n";
	char temp [100];
	printf("Hello again\n");
	int t = time();
	sprintf(temp,"%d,\n",t);
	printf(temp);
	t = t;
	write(STDOUT_FILENO, hello, sizeof(hello) - 1);
	t = time();
	sprintf(temp,"%d,\n",t);
	printf(temp);
	return 0;
}
