
void greetuser(int n)
{
    char *s1;
    undefined4 uStack72;
    undefined4 uStack68;
    undefined4 uStack64;
    undefined2 uStack60;
    char cStack58;
    
    if (_language == 1) {
        s1 = (char *)0xc3767948;
        uStack72 = 0x20a4c3a4;
        uStack68 = 0x69a4c370;
        uStack64 = 0xc3a4c376;
        uStack60 = 0x20a4;
        cStack58 = '\0';
    } else if (_language == 2) {
        s1 = (char *)0x64656f47;
        uStack72 = 0x64696d65;
        uStack68 = 0x21676164;
        uStack64 = CONCAT22(uStack64._2_2_, 0x20);
    } else if (_language == 0) {
        s1 = (char *)0x6c6c6548;
        uStack72 = CONCAT13(uStack72._3_1_, 0x206f);
    }
    strcat(&s1, &arg_8h);
    puts(&s1);
    return;
}



int main (int ac, char **av)
{
    char *src; // Unused ??
    int n;
    char dest [19];
    char *s1;

    if (ac == 3) {

        memset(dest, '\0', 19);
        strncpy(dest, argv[1], 40);
        strncpy(dest + 40, argv[2], 32);

        s1 = getenv("LANG");
        if (s1 != 0) {
            if (memcmp(s1, 0x804873d, 2) == 0)
                _language = 1;
            else if (memcmp(s1, 0x8048740, 2) == 0)
                _language = 2;
        }

        memcpy(dest, STACK POINTER, 19); // Either this ?
        memcpy(STACK POINTER, dest, 19); // Or that ??
        greetuser(n);

        return ;
    }
    return 1;
}
