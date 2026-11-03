#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char **argv) {
    FILE *f = fopen(argv[1], "rb");
    if (!f) { perror("fopen"); return 1; }

    uint8_t dos[64];
    fread(dos, 1, 64, f);
    for (int i = 0; i < 64; i++) {
        printf("%02x ", dos[i]);
        if ((i + 1) % 16 == 0) printf("\n");
    }
    
    printf("%c%c\n", dos[0], dos[1]);


    uint32_t e_lfanew;
    memcpy(&e_lfanew, &dos[0x3c], 4);
    printf("PE Header Location: 0x%X\n", e_lfanew);
    fseek(f, e_lfanew + 4, SEEK_SET);

    uint16_t machine, nsec;
    fread(&machine, 2, 1, f);
    fread(&nsec, 2, 1, f);

    printf("machine: 0x%04X, sec: %u\n", machine, nsec); 

    fclose(f);
    return 0;
}