
void greetuser(char *arg)
{
    char *s;
    
    if (_language == 1)
        s = "Hyvää päivää ";
    else if (_language == 2)
        s = "Goedemiddag! ";
    else if (_language == 0)
        s = "Hello ";

    strcat(s, arg);
    puts(s);

    return;
}



int main (int ac, char **av)
{
    char *src; // Unused ??
    int n;
    char dest [19];
    char *lang;

    if (ac == 3) {

        memset(dest, '\0', 19);
        strncpy(dest, argv[1], 40);
        strncpy(dest + 40, argv[2], 32);

        lang = getenv("LANG");
        if (lang != 0) {
            if (memcmp(lang, "fi", 2) == 0)
                _language = 1;
            else if (memcmp(lang, "nl", 2) == 0)
                _language = 2;
        }

        memcpy(STACK POINTER, dest, 19);
        greetuser(n);

        return ;
    }
    return 1;
}
