

void main (int argc, char **argv)
{
    int ret;
    char buf [40];
    int32_t n;
    
    n = atoi(argv[1]);

    if (n < 10) {
        memcpy(buf, argv[2], n * 4);

        if (n == 0x574f4c46)
            execl("/bin/sh", 0x8048580, 0);

        return 0;
    }
    
    return 1:
}