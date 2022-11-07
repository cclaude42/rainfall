#include <stdio.h>
#include <stdlib.h>

void run (void)
{
    printf("Good... Wait what ?");
    system("/bin/ls");
}

int main (void)
{
    char *s;
    gets(s);
}