#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
#include "dirHandler/curDirName.h"

#define RESET_COLOR "\033[0m"
#define BLUE_TEXT "\033[34m"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        argv = (char **) malloc(argc);
        if (!argv) {
            perror("malloc");
            exit(-1);
        }
        char *input;
        char *dirName;
        system("clear");
        printf("Welcome. To see available commands, write `help`.\n\n");
        while (true) {
            dirName = getCurrentDir();
            printf(BLUE_TEXT"%s\n"RESET_COLOR, dirName);
            printf("> "); input = getInput(&argc, argv); 
            if (!strcmp(input, "exit")) break;
            errorCode code = doCommand(input, argc, argv);
            showError(code, input);
        }
        printf("\nFinishing program...\n");
        free(input);
        free(dirName);
    } else {
        if (argc < 3) {
            showError(NOT_ENOUGH_ARGS, "");
            return -1;
        } else {
            char **localArgv = (char **) malloc(sizeof(char *) * argc);
            if (!localArgv) {
                perror("malloc");
                exit(-1);
            }
            for (int i = 0; i < argc; ++i) {
                localArgv[i] = (char *) malloc(strlen(argv[i]) + 1);
                if (!localArgv[i]) {
                    perror("malloc");
                    exit(-1);
                }
                strcpy(localArgv[i], argv[i]);
            }
            char *input = getCommandByFlag(&argc, localArgv);
            errorCode code = doCommand(input, argc, localArgv);
            showError(code, input);
        }
    }
    return 0;
}
