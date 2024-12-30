#include "reader.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int readFile(int argc, char *argv[]) {
    if (argc == 0) {
        char *PATH = (char *) malloc(strlen(argv[0]) + 1);
        strcpy(PATH, argv[0]);
        system("clear");
        printf("Opening \"%s\"...\n", PATH);
        FILE *file = fopen(PATH, "r");
        if (file == NULL) {
            char *errorMsg = (char *) malloc(strlen("fopen: file \"\"") + strlen(PATH) + 1);
            sprintf(errorMsg, "fopen: file \"%s\"", PATH);
            perror(errorMsg);
            free(errorMsg);
            return -1;
        }
        char ch;
        while ((ch = getc(file)) != EOF) {
            putchar(ch);
        }
        fclose(file);
        free(PATH);
    }
    return 0;
}

