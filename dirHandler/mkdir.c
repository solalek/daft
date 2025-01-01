#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

void makeDirs(char *PATH) {
    char *delimiter = "/";
    char *pathToGrow = (char *) malloc(strlen(PATH) + 1);
    char *token = strtok(PATH, delimiter);
    strcpy(pathToGrow, "");
    while (token) {
        mkdir(pathToGrow, 0777);
        strcat(pathToGrow, token);
        strcat(pathToGrow, "/");
        token = strtok(NULL, delimiter);
    }
    mkdir(pathToGrow, 0777);
}
