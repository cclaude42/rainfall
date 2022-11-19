

void p(char *dest, char *s)
{
    char *buf;
    
    puts(s);

    read(0, &buf, 4096);

    *strchr(&buf, '\n') = '\0';

    strncpy(dest, &buf, 20);

    return;
}


void pp(char *dest)
{
    unsigned int a;
    unsigned int b;


    p((char *)&a, " - ");
    p((char *)&b, " - ");

    strcpy(dest, &a);

    *(dest + strlen(dest)) = ' ';

    strcat(dest, &b);

    return ;
}



int main (void)
{
    char buffer [54];
    
    pp(buffer);

    puts(buffer);

    return 0;
}
