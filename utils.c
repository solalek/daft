#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <dirent.h>
#include "fileHandler/reader.h"
#include "fileHandler/writer.h"
#include "dirHandler/listDir.h"
#include "dirHandler/recursiveRmDir.h"

char *getCommandByFlag(int *argc, char *argv[]) {
    printf("Argc: %d\n", *argc);
    if (argv[1][0] != '-' || argv[1][1] != 'c') {
        printf("%s: Invalid flag!!!", argv[1]);
        return NULL;
    } else {
        char *input = argv[2];
        char **localArgv = (char **) malloc(sizeof(char *) * (*argc - 3));
        for (int i = 3; i < *argc; ++i) {
            localArgv[i-3] = argv[i];
        }
        *argc -= 3;
        argv = realloc(argv, *argc);
        for (int i = 0; i < *argc; ++i) {
            argv[i] = (char *) malloc(strlen(localArgv[i]) + 1);
            strcpy(argv[i], localArgv[i]);
        }
        free(localArgv);
        return input;
    }
}

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

bool isEmptyDir(DIR *dir) {
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
            return false;
        }
    }
    return true;
}

int doCommand(char *command, int argc, char *args[]) {
    if (!strcmp(command, "help")) {
        if (argc != 0) {
            return TOO_MANY_ARGS;
        }
        helpCommand();
    } 
    else if (!strcmp(command, "clear")) {
        if (argc != 0) {
            return TOO_MANY_ARGS;
        }
        system("clear");
    } 
    else if (!strcmp(command, "read")) {
        readFile(argc, args);
    } 
    else if (!strcmp(command, "write")) {
        writeFile(argc, args);
    } 
    else if (!strcmp(command, "cd")) {
        if (argc > 1) {
            return TOO_MANY_ARGS;
        }
        if (argc < 1) {
            return NOT_ENOUGH_ARGS;
        }
        system("clear");
        chdir(args[0]);
    } 
    else if (!strcmp(command, "ls")) {
        if (argc > 1) {
            return TOO_MANY_ARGS;
        }
        system("clear");
        listDir(argc, args);
    } 
    else if (!strcmp(command, "mkdir")) {
        mkdir(args[0], 0777);
        printf("\n");
    } 
    else if (!strcmp(command, "rmdir")) {
        DIR *dir = opendir(args[0]);
        if (isEmptyDir(dir)) {
            rmdir(args[0]);
        } else {
            rrmdir(args[0]);
        }
        printf("\n");
    }
    else {
        return UNKNOWN_COMMAND;
    }
    return SUCCESS;
}

void showError(errorCode code, char *input) {
    if (code == SUCCESS) {
        return;
    } else if (code == TOO_MANY_ARGS) {
        printf("%s: Invalid argument: too many arguments!!!\n", input);
    } else if (code == NOT_ENOUGH_ARGS) {
        printf("%s: Invalid argument: not enough arguments!!!\n", input);
    } else if (code == UNKNOWN_COMMAND) {
        printf("%s: Invalid command!!!\n", input);
    }
}
