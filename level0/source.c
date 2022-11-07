#include <stdlib.h>
#include <stdio.h>

int main (int ac, char **av)
{
    if (atoi(av[1]) == 423)
        system("/bin/sh");
    else
        printf("No !\n");
}