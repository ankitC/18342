/*
 * rot13.c: ROT13 cipher test application. The Application
 *			exits on any error from the syscall or when
 *			the user hits CLTR+C.
 *
 * Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
 *          Group Member 2: Jiten Mehta <jitenm>
 *  	    Group Member 3: Ankit Chheda <achheda>
 * Date: Oct 14, 2013. 9:00AM
 */
#include <unistd.h>
#include <stdlib.h>
#include <bits/fileno.h>
//#include <exports.h>

int main(void)
{
	char buf[11] = {};//"hello MAC!\n";
	int r = read(0, buf, 11);
	//printf("read returned %d\n", r);
	//int w = write(1,"writing buf\n",10);
	 int w = write(1, buf, 15);
	//printf("write returned %d\n", w);
	r=r;
	 w=w;
	exit(0);
	return 0;
}
