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
	char buf[11] = {0};
	int r = read(0, buf, 11);
	int w = write(1, buf, 11);
	r=r;
	w=w;
	return 0;
}
