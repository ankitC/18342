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
#define SLEEP 100

void print_buf(char buf[6][5])
{
	int i, j;
	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 5; j++)
			printf("%c", buf[i][j]);
		printf("\n");
	}
	sleep(SLEEP);
	printf("%c%c6A", ESCAPE, BRACKET);
}

void step1()
{
	char buf[6][5];
	int i, j;
	for(i = 0; i < 6; i++)
		for(j = 0; j < 5; j++)
			buf[i][j] = ' ';

	buf[1][2] = 'O';
	buf[2][2] = '|';
	buf[3][2] = '|';
	buf[4][1] = '/';
	buf[4][3] = '\\';

	buf[2][1] = '/';
	buf[3][0] = '/';
	buf[2][3] = '\\';
	buf[3][4] = '\\';
	buf[5][1] = '|';
	buf[5][3] = '|';
	print_buf(buf);
}

void step2()
{
	char buf[6][5];
	int i, j;
	for(i = 0; i < 6; i++)
		for(j = 0; j < 5; j++)
			buf[i][j] = ' ';

	buf[1][2] = 'O';
	buf[2][2] = '|';
	buf[3][2] = '|';
	buf[4][1] = '/';
	buf[4][3] = '\\';

	buf[1][0] = '_';
	buf[1][1] = '_';
	buf[1][3] = '_';
	buf[1][4] = '_';
	buf[5][1] = '|';
	buf[5][3] = '|';
	print_buf(buf);
}

void step3()
{
	char buf[6][5];
	int i, j;
	for(i = 0; i < 6; i++)
		for(j = 0; j < 5; j++)
			buf[i][j] = ' ';

	buf[1][2] = 'O';
	buf[2][2] = '|';
	buf[3][2] = '|';
	buf[4][1] = '/';
	buf[4][3] = '\\';

	buf[1][0] = '_';
	buf[1][1] = '_';
	buf[1][3] = '_';
	buf[1][4] = '_';
	buf[5][0] = '/';
	buf[5][4] = '\\';
	print_buf(buf);
}

void step4()
{
	char buf[6][5];
	int i, j;
	for(i = 0; i < 6; i++)
		for(j = 0; j < 5; j++)
			buf[i][j] = ' ';

	buf[1][2] = 'O';
	buf[2][2] = '|';
	buf[3][2] = '|';
	buf[4][1] = '/';
	buf[4][3] = '\\';

	buf[0][0] = '\\';
	buf[1][1] = '\\';
	buf[0][4] = '/';
	buf[1][3] = '/';
	buf[5][0] = '/';
	buf[5][4] = '\\';
	print_buf(buf);
}

void step5()
{
	char buf[6][5];
	int i, j;
	for(i = 0; i < 6; i++)
		for(j = 0; j < 5; j++)
			buf[i][j] = ' ';

	buf[1][2] = 'O';
	buf[2][2] = '|';
	buf[3][2] = '|';
	buf[4][1] = '/';
	buf[4][3] = '\\';

	buf[0][1] = '|';
	buf[1][1] = '|';
	buf[0][3] = '|';
	buf[1][3] = '|';
	buf[5][0] = '/';
	buf[5][4] = '\\';
	print_buf(buf);
}

int main(int argc, char **argv)
{
	printf("\n");
	while(1)
	{
		step1();
		step2();
		step3();
		step4();
		step5();
		step4();
		step3();
		step2();
	}
	return 0;
}
