#include "writer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char *getTextToWrite() {
    char *buffer = (char *) malloc(1);
    size_t bufferSize = 1;
    size_t length = 0;
    char c;
    while (scanf("%c", &c) == 1 && c != '\n') {
        if (length + 1 >= bufferSize) {
            bufferSize *= 2;
            buffer = realloc(buffer, bufferSize);
            if (!buffer) {
                perror("Failed to reallocate memory");
                return NULL;
            }
        }
        buffer[length++] = c;
    }
    buffer[length] = '\0';
    return buffer;
}

int writeFile(char *PATH) {
    FILE *file = fopen(PATH, "w");
    if (file == NULL) {
        char *errorMsg = (char *) malloc(strlen("fopen: file \"\"") + strlen(PATH) + 1);
        sprintf(errorMsg, "fopen: file \"%s\"", PATH);
        perror(errorMsg);
        free(errorMsg);
        return -1;
    }
    system("clear");
    printf("Enter text to write in file('exit' to quit):\n");
    char *buffer;
    int i = 1;
    while (true) {
        printf("%d line: ", i);
        buffer = getTextToWrite();
        if (!buffer) {
            fclose(file);
            return -1;
        }
        if (!strcmp(buffer, "exit")) {
            printf("\nExiting from \"%s\"...\n\n", PATH);
            free(buffer);
            system("clear");
            break;
        }
        fprintf(file, "%s\n", buffer);
        free(buffer);
        i++;
    }
    fclose(file);
    return 1;
}
