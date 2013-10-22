#include <exports.h>

int read(int fd, char *buf, int length);
int write(int fd, char *buf, int length);

int main()
{

	char *buf;
	int length = 10;
	int r = read(0, buf, length);
	printf("read=%d\n",r);
	int w = write(1, buf, r);
	printf("write=%d\n",w);

	return 0;
}

int read(int fd, char *buf, int length)
{

	int i;
	for(i = 0; i < length; i++)
	{
		char c = getc();
		if(c == '\0')
			break;

		if(c == 4)
			break;

		if(c == '\b' || c == 127)		//TODO delete encountered
		{
			buf[i - 1] = '\0';
			i--;
			puts("\b \b");
		}

		if(c == '\n' || c == '\r')
		{
			buf[i] = c;
			break;
		}

		buf[i] = c;
	}
	return i;

}

int write(int fd, char *buf, int length)
{
	int i;
	for(i = 0; i < length ; i++)
	{
		if(buf[i] = '\0')
			break;
		putc(buf[i]);
	}
	return i;
}
