/*
 * rot13.c: ROT13 cipher test application
 *
 * Authors: Group Member 1 <email address>
 *          Group Member 2 <email address>
 * Date:    The current time & date
 */
#include <unistd.h>
#include <stdlib.h>

#include <unistd.h>
#include <stdlib.h>
//#include <bits/swi.h>

int main(void) {
	int i = 0;
	char buf[10];
	while(1)
	{
		int r = read(0, buf, 15);
		if(r-1==0){
			return 0;
		}

		else if(r < 0)
			return 1;
		else
		{
			for(i = 0; i < r; i++)
			{
				if(((buf[i] >= 65) && (buf[i] <= 77)) || ((buf[i] >= 97) && (buf[i] <= 109)))
				{
					buf[i] += 13;
				}
				else if(((buf[i] >= 78) && (buf[i] <= 90)) || ((buf[i] >= 110) && (buf[i] <= 122)))
				{
					buf[i] -= 13;
				}
			}
		}
		int w = write(1, buf, r);
		if(w < 0)
			return 1;
	}
	return 0;
}
