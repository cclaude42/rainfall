

int main(int ac, char **av)
{
    char buf1 [16];
    int x;
    char buf2 [66];
    FILE *fptr;


    fptr = fopen("/home/user/end/.pass", 0x80486f0);
    memset(buf1, '\0', 33);

    if (ac == 2 && fptr != 0) {
        fread(buf1, 1, 66, fptr);
        x = 0;
        *(buf1 + atoi(av[1])) = 0;

        fread(buf2, 1, 65, fptr);
        fclose(fptr);
        
        if (strcmp(buf1, av[1]) == 0)
            execl("/bin/sh", 0x8048707, 0);
        else
            puts(buf2);

        return 0;
    }
    return -1;
}