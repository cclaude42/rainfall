

int main (void)
{
    uint8_t cmd [5];
    char authbuf [2];
    char servbuf [125];


    while (true) {

        printf("%p, %p \n", _auth, _service);

        if (fgets(cmd, 128, _stdin) == 0)
            return 0;

        if (strncmp(cmd, "auth", 4) == 0) {
            _auth = (int *)malloc(4);
            *_auth = 0;

            if (strlen(authbuf) < 31) {
                strcpy(_auth, authbuf);
            }
        }


        if (strncmp(cmd, "reset", 5) == 0)
            free(_auth);


        if (strncmp(cmd, "service", 7) == 0)
            _service = strdup(servbuf);

        
        if (strncmp(cmd, "login", 5) == 0) {
            if (_auth[8] == 0) {
                fwrite("Password:\n", 1, 10, _stdout);
            } else {
                system("/bin/sh");
            }
        }
    }
}