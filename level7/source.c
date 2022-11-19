

int main(int ac, char **argv)
{
    void *p1;
    unsigned int var;
    void *p2;
    
    p1 = (void *)malloc(8);
    var = malloc(8);

    p1[0] = 1;
    p1[1] = var;

    p2 = (void *)malloc(8);
    var = malloc(8);

    p2[0] = 2;
    p2[1] = var;


    strcpy(p1[1], argv[1]);
    strcpy(p2[1], argv[2]);


    var = fopen("/home/user/level8/.pass", 0x80486e9);
    fgets(c, 68, var);

    puts(0x8048703);

    return 0;
}