

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char** argv)
{
	//char buf[10] ;
	char no[2];
	int n;
	printf("Enter a number\n");
	read(STDIN_FILENO, no, 2);
	n = no[0] - 48;
	printf("%d\n", n);
	return 0;
}
