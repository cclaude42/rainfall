

class N {
    public:
        N (unsigned int a, unsigned int b) {
            *(code **)a = vtable.N.0;
            *(int32_t *)(a + 104) = b;
        }

        void setAnnotation (void *s1, char *s) {
            memcpy((unsigned int)s1 + 4, s, strlen(s));
        }
};

void main (int argc, char **argv)
{
    void *s1;
    void *s2;
    int var_bp_4h;
    
    if (argc < 2)
        exit(1);


    s1 = new unsigned int (108);
    s2 = new unsigned int (108);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        

    N::N((unsigned int)s1, 5);
    N::N((unsigned int)s2, 5);


    N::setAnnotation(s1, argv[1]);
    (**(code **)*s2)(s2, s1);

    return;
}