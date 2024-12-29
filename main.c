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
        char *input;
        char *args = (char *) malloc(1);
        char *dirName;
        system("clear");
        printf("Welcome. To see available commands, write `help`.\n\n");
        while (true) {
            dirName = getCurrentDir();
            printf(BLUE_TEXT"%s\n"RESET_COLOR, dirName);
            printf("> ");
            input = getInput(args);
            // printf("User Input: %s\nUser Args: %s\n", input, args);
            if (!strcmp(input, "exit")) break;
            if (doCommand(input, args) == -1) {
                printf("'%s': Invalid command.\n", input);
            }
        }
        printf("\nFinishing program...\n");
        free(input);
        free(args);
        free(dirName);
    }
    return 0;
}
