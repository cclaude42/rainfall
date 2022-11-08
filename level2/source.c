#include <unistd.h>
#include <stdio.h>


void	p()
{
	char	*s;

	fflush();
	gets(s);
	if (s & 0xb0000000) {
		printf(s);
		exit();
	}
	puts(s);
	strdup(s);
	system("/bin/sh");

}


int	main(int argc, char **argv)
{
	p();
	return 0;
}

