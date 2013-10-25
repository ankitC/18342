#include <unistd.h>
#include <stdlib.h>
#include <bits/fileno.h>

#define BUFSIZE 10

int main(int argc, char **argv)
{
	int count = 0;
	int w;
	while((count + 1) < argc)
	{
		w = write(STDOUT_FILENO, argv[count], BUFSIZE);
		count++;
	}
	return 0;
}
