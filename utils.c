#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "fileHandler/reader.h"
#include "fileHandler/writer.h"
#include "dirHandler/listDir.h"

char *getInput(int *argc, char *argv[]) {
    char *input = NULL;
    size_t bufferSize = 1;
    size_t length = 0;
    char *delimiter = " ";
    char *token;

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
    if (token == NULL) {
        argv = realloc(argv, sizeof(char *));
        argv[0] = (char *) malloc(strlen("") + 1);
        strcpy(argv[0], "");
        *argc = 0;
    }
    for (int i = 0; token; ++i) {
        argv = realloc(argv, sizeof(char *) * (i + 1));
        argv[i] = (char *) malloc(strlen(token) + 1);
        printf("Token: %s\n", token);
        strcpy(argv[i], token);
        token = strtok(NULL, delimiter);
        *argc = i+1;
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

int doCommand(char *command, int argc, char *args[]) {
    if (!strcmp(command, "help")) {
        if (argc != 0) {
            printf("help: Invalid argument: too many arguments!!!");
            return -1;
        }
        helpCommand();
        return 0;
    } else if (!strcmp(command, "clear")) {
        if (argc != 0) {
            printf("clear: Invalid argument: too many arguments!!!");
            return -1;
        }
        system("clear");
        return 0;
    } else if (!strcmp(command, "read")) {
        readFile(argc, args);
        return 0;
    } else if (!strcmp(command, "write")) {
        writeFile(argc, args);
        return 0;
    } else if (!strcmp(command, "cd")) {
        if (argc > 1) {
            printf("cd: Invalid argument: too many arguments!!!");
            return -1;
        }
        if (argc < 1) {
            printf("cd: Invalid argument: not enough arguments!!!");
            return -1;
        }
        system("clear");
        chdir(args[0]);
        return 0;
    } else if (!strcmp(command, "ls")) {
        if (argc > 1) {
            printf("ls: Invalid argument: too many arguments!!!");
            return -1;
        }
        system("clear");
        listDir(argc, args);
        return 0;
    } else if (!strcmp(command, "mkdir")) {
        mkdir(args[0], 0777);
        printf("\n");
    } else if (!strcmp(command, "rmdir")) {
        rmdir(args[0]);
        printf("\n");
    }
    else {
        return -1;
    }
}
