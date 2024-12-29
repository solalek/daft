#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "fileHandler/reader.h"
#include "fileHandler/writer.h"
#include "dirHandler/listDir.h"

char *getInput(char *args) {
    char *input = NULL;
    size_t bufferSize = 1;
    size_t length = 0;
    char *delimiter = " ";
    char *token;
    char *backArgs = args;

    input = malloc(bufferSize);
    if (!input) {
        perror("Failed to allocate memory");
        return NULL;
    }

    char c;
    while (scanf("%c", &c) == 1 && c != '\n') {
        if (length + 1 >= bufferSize) {
            bufferSize *= 2;
            input = realloc(input, bufferSize);
            if (!input) {
                perror("Failed to reallocate memory");
                return NULL;
            }
        }
        input[length++] = c;
    }
    input[length] = '\0';
    token = strtok(input, delimiter);
    token = strtok(NULL, delimiter);
    if (token) {
        args = realloc(args, strlen(token)+1);
        if (args == NULL) {
            perror("realloc");
            args = backArgs;
        }
        strcpy(args, token);
    } else {
        args = realloc(args, 2);
        strcpy(args, "");
    }
    return input;
}

void helpCommand() {
    system("clear");
    FILE *file = fopen(HELP_PATH, "r");
    if (file == NULL) {
        char *errorMsg = (char *) malloc(strlen("fopen: file \"\"") + strlen(HELP_PATH) + 1);
        sprintf(errorMsg, "fopen: file \"%s\"", HELP_PATH);
        perror(errorMsg);
        free(errorMsg);
    }
    char ch;
    while ((ch = getc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
}

int doCommand(char *command, char *args) {
    if (!strcmp(command, "help")) {
        helpCommand();
        return 0;
    } else if (!strcmp(command, "clear")) {
        system("clear");
    } else if (!strcmp(command, "read")) {
        readFile(args);
        return 0;
    } else if (!strcmp(command, "write")) {
        writeFile(args);
        return 0;
    } else if (!strcmp(command, "cd")) {
        system("clear");
        chdir(args);
    } else if (!strcmp(command, "ls")) {
        system("clear");
        listDir(args);
    } else if (!strcmp(command, "mkdir")) {
        mkdir(args, 0777);
        printf("\n");
    } else if (!strcmp(command, "rmdir")) {
        rmdir(args);
        printf("\n");
    }
    else {
        return -1;
    }
}
