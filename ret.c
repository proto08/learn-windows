#include <stdio.h>
#include <stdlib.h>

void greet(void) {
    printf("hello\n");
}

void run_ls(void) {
    printf(">>> ls\n");
    system("ls -la");
}

int main(void) {

    struct {
        char buf[64];
        void (*fp) (void);
    } s;
    s.fp = greet;

    printf("address of run_ls = %p\n", (void*)run_ls);

    FILE *f = fopen("config.ini", "rb");
    if (!f) { perror("fopen"); return 1;}
    fread(s.buf, 1, 4096, f);
    fclose(f);

    s.fp();
    return 0;
}