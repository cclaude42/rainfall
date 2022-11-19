

int main (void)
{
    uint8_t buf [5];
    char acStack139 [2];
    undefined auStack137 [125];


    while (true) {

        printf("%p, %p \n", _auth, _service);

        if (fgets(buf, 128, _stdin) == 0)
            return 0;

        if (strncmp(buf, "auth", 4) == 0) {
            _auth = (int *)malloc(4);
            *_auth = 0;

            if (strlen(acStack139) < 31) {
                strcpy(_auth, acStack139);
            }
        }


        if (strncmp(buf, "reset", 5) == 0)
            free(_auth);


        if (strncmp(buf, "service", 7) == 0)
            _service = strdup(auStack137);

        
        if (strncmp(buf, "login", 5) == 0) {
            if (_auth[8] == 0) {
                fwrite("Password:\n", 1, 10, _stdout);
            } else {
                system("/bin/sh");
            }
        }
    }
}