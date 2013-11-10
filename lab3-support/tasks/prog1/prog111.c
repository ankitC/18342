

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define INITIALSIZE 24
void spacing(void);

int main(int argc, char** argv)
{
	//char buf[10] ;
	char no[2];
	int n,i;
	//unsigned long t1,t2,t3;
	printf("Enter a number\n");
	read(STDIN_FILENO, no, 2);
	n = no[0] - 48;
	printf("%d\n", n);
	spacing();
	spacing();
	spacing();
	printf("\n");
	
	char buf[INITIALSIZE];
	char buf2[INITIALSIZE];
	for(i = 0 ; i < INITIALSIZE ; i++)
		{
			buf[i] = ' ';
			buf2[i] = '\b';
		}

	for( i = 0; i < INITIALSIZE ; i++)
	{
		buf[i]='O';
		write(STDOUT_FILENO, buf , INITIALSIZE);
		sleep(80);
		write(STDOUT_FILENO, buf2, INITIALSIZE);
		buf[i]= ' ';
		
	}
	return 0;
}

void spacing ()
{
	int i;
	unsigned long t1,t2;
		
	for(i=0; i< 5 ; i++)
		{
			write(STDOUT_FILENO,"|",1);
			t1 = time();
		}
	for(i=0; i< 3 ; i++)
		{
			write(STDOUT_FILENO," ",1);
			t2 = time();
		}
	/*
	for(i=0; i< 5 ; i++)
		{
			write(STDOUT_FILENO,"|",1);
			t3 = time();
		}
	*/
}
