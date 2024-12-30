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
        char *input;
        char *dirName;
        char *args;
        system("clear");
        printf("Welcome. To see available commands, write `help`.\n\n");
        while (true) {
            dirName = getCurrentDir();
            printf(BLUE_TEXT"%s\n"RESET_COLOR, dirName);
            printf("> ");
            input = getInput(&argc, argv);
            // printf("User Input: %s\nUser Argc: %d\nUser Argv: ", input, argc);
            // printf("[ ");
            // for (int i = 0; i < argc; ++i) {
            //     printf("'%s',", argv[i]);
            // } 
            // printf(" ]\n");
            if (!strcmp(input, "exit")) break;
            errorCode code = doCommand(input, argc, argv);
            showError(code, input);
        }
        printf("\nFinishing program...\n");
        free(input);
        free(dirName);
    }
    return 0;
}
