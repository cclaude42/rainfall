#include <unistd.h>
#include <stdio.h>
#include <string.h>

void p (void)
{
	char s[72];

	gets(s);
	if ((unsigned int)s & 0xb0000000) {
		printf(s);
		exit(1);
	}
	puts(s);
	strdup(s);
}

int	main(int argc, char **argv)
{
	p();
	return 0;
}

