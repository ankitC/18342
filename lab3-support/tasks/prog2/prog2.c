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

void print_buf(char buf[5][20],char **argv)
{
	int i, j;
	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 20; j++)
			printf("%c", buf[i][j]);
		printf("\n");
	}
	sleep(atoi(argv[1]));
	printf("%c%c5A", ESCAPE, BRACKET);
}

void step1(char **argv)
{
	char buf[5][20];
	int i, j;
	for(i = 0; i < 5; i++)
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

	print_buf(buf,argv );
}
/*
void step2()
{
	char buf[5][20];
	int i, j;
	for(i = 0; i < 5; i++)
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

	print_buf(buf);
}
*/

int main(int argc, char **argv)
{
	printf("\n");
	while(1)
	{
		step1(argv);
		//step2();
	}
	return 0;
}
