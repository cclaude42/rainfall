#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int v (void)
{
    char s[250];
    int m;

    fgets(s, 250, stdin);
    printf(s);
    if (m == 64) {
        char str[] = "Wait what?!\n";

        fwrite(str, 1, sizeof(str), stdout);
        system("/bin/sh");
    }
    return 0;
}


int main (void)
{
    v();
    return 0;
}