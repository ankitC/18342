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

#define ESCAPE 0x1B
#define BRACKET 0x5B
#define SLEEP1 200

void print_buf(char buf[10][20],int n)
{
	int i, j;
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 20; j++)
			printf("%c", buf[i][j]);
		printf("\n");
	}
	sleep(n);
	printf("%c%c10A", ESCAPE, BRACKET);
}

void step1(int n)
{
	char buf[10][20];
	int i, j;
	for(i = 0; i < 10; i++)
		for(j = 0; j < 20; j++)
			buf[i][j] = ' ';
	
	buf[0][2] = '|';
	buf[1][2] = '|';
	buf[2][2] = '+';
	buf[3][2] = '|';
	buf[4][2] = '|';

	buf[2][0] = '-';
	buf[2][1] = '-';
	buf[2][3] = '-';
	buf[2][4] = '-';

	buf[0][17] = '|';
	buf[1][17] = '|';
	buf[2][17] = '|';
	buf[3][17] = '|';
	buf[4][17] = '|';
	
	buf[2][15] = '-';
	buf[2][16] = '-';
	buf[2][18] = '-';
	buf[2][19] = '-';
/*	
	buf[0][0] = '\\';
	buf[0][4] = '/';
	buf[1][1] = '\\';
	buf[1][3] = '/';
	buf[2][2] = 'x';
	buf[3][1] = '/';
	buf[3][3] = '\\';
	buf[4][0] = '/';
	buf[4][4] = '\\';

	buf[0][15] = '\\';
	buf[0][19] = '/';
	buf[1][16] = '\\';
	buf[1][18] = '/';
	buf[2][17] = 'x';
	buf[3][16] = '/';
	buf[3][18] = '\\';
	buf[4][15] = '/';
	buf[4][19] = '\\';
*/
	print_buf(buf,n );
}

void step2(int n)
{
	char buf[10][20];
	int i, j;
	for(i = 0; i < 10; i++)
		for(j = 0; j < 20; j++)
			buf[i][j] = ' ';
	buf[0][0] = '\\';
	buf[0][4] = '/';
	buf[1][1] = '\\';
	buf[1][3] = '/';
	buf[2][2] = 'x';
	buf[3][1] = '/';
	buf[3][3] = '\\';
	buf[4][0] = '/';
	buf[4][4] = '\\';

	buf[0][15] = '\\';
	buf[0][19] = '/';
	buf[1][16] = '\\';
	buf[1][18] = '/';
	buf[2][17] = 'x';
	buf[3][16] = '/';
	buf[3][18] = '\\';
	buf[4][15] = '/';
	buf[4][19] = '\\';

	print_buf(buf, n);
}

void rocket(int k, int n)
{
	char buf[10][20];
	int i, j;
	for(i = 0; i < 10; i++)
		for(j = 0; j < 20; j++)
			buf[i][j] = ' ';

	buf[k][2] = '^';
	buf[k][17] = '^';
	print_buf(buf, n);
}

int main(int argc, char **argv)
{
	printf("Enter the number of blinks for crackers\n");
	char buf[2];
	int i;
	read(STDIN_FILENO, buf, 2);
	int n = (int)buf[0] - 48;
	printf("Enter the time for rockets\n");
	read(STDIN_FILENO, buf, 2);
	int p = (int)buf[0] - 48;
	p *= 100;
	printf("\n");
	while(1)
	{
		for(i = 9 ; i>= 2 ; i--)
			rocket(i,p);
		for(i =0 ; i< n ;i++)
		{
		step1(200);
		step2(200);
		}
	}
	return 0;
}
