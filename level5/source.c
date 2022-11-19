#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void    o(void)
{
    system("/bin/sh");
    return exit(1);
}


int    n(void)
{
    char s[512];

    fgets(s, 512, stdin);
    printf(s);
    return exit(1);
}


int    main(void)
{
    n();
    return ;
}