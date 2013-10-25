#include <unistd.h>
#include <stdlib.h>
#include <bits/fileno.h>


int main(void)
{
	write(1,"Hello",5);	
	return 0;
}
