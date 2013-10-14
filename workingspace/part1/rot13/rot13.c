/*
 * rot13.c: ROT13 cipher test application
 * Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
 *          Group Member 2: Jiten Mehta <jitenm>
 *  	    Group Member 3: Ankit Chheda <achheda>
 * Date: Oct 14, 2013. 9:00AM
 */
#include <unistd.h>
#include <stdlib.h>
#include <fileno.h>

#define BUFSIZE 10

int main(void)
{
	int i = 0;
	int r, w = 0;
	char buf[BUFSIZE];
	while(1)
	{
		r = read(STDIN_FILENO, buf, BUFSIZE);
		/* Read 0 bytes hence terminate the program */
		if(r == 0)
			exit(0);
		/* Checking return value for errors */
		else if(r < 0)
			exit(1);
		else
		{
			for(i = 0; i < r; i++)
			{
				if(((buf[i] >= 65) && (buf[i] <= 77)) || ((buf[i] >= 97) && (buf[i] <= 109)))
					buf[i] += 13;
				else if(((buf[i] >= 78) && (buf[i] <= 90)) || ((buf[i] >= 110) && (buf[i] <= 122)))
					buf[i] -= 13;
			}
		}
		/* Ensuring that we retransmit in case of short count on write */
		while(r != w){
			w = write(STDOUT_FILENO, buf, r);
			if(w < 0)
			{
				exit(1);
			}
		}
		w = 0; /* Resetting w for checking r!=w */
	}
	return 0;
}
