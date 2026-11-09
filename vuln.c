#include <stdio.h>
#include <string.h>


int main(void) {
    char secret[16] = "LOCKED";
    char name[64];

    FILE *fp = fopen("config.ini", "r");
    if (!fp) { perror("fopen"); return 1; }

    char line[256];
    char value[256] = "";
    while(fgets(line, sizeof(line), fp)) {
        printf("%s", line);
        if (strncmp(line, "name=", 5) == 0) {
            strcpy(value, line + 5);
            value[strcspn(value, "\r\n")] = 0;
        }
    }
    printf("%s\n", value);
    printf("\n--------------------------------------\n");
    fclose(fp);

    strcpy(name, value); // vuln

    printf("name   = %s\n", name);
    printf("secret = %s\n", secret);

    if (strcmp(secret, "LOCKED") != 0) {
        printf("bof\n");
    }
    return 0;
}