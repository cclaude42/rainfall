#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int p (char *s)
{
    printf(s);
}

int n (void)
{
    char s[512];
    int m;

    fgets(s, 512, stdin);
    p(s);
    if (m == 0x1025544) {
        system("/bin/cat /home/user/level5/.pass");
    }
    return 0;
}


int main (void)
{
    n();
    return 0;
}