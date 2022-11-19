#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void    n(void)
{
    system("/bin/cat /home/user/level7/.pass");
}


void    m(void)
{
    puts("Nope");
}


int    main(int argc, char **argv)
{
    char    **var_one;
    char    **var_two;

    var_one = malloc(60);
    var_two = (char **)malloc(4);
    *var_two = m;
    strcpy(var_one, argv[1]);
    (**var_two)();
    return 0;
}