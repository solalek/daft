#include "curDirName.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char *removeHome(char *dirName, int size) {
    int newSize = strlen(dirName) - size + 2;
    char *newName = (char *) malloc(newSize);
    if (newName == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    newName[0] = '~';
    for (int i = 1; i < newSize; i++) {
        newName[i] = dirName[i + size - 1];
    }
    return newName;
}

char *getCurrentDir() {
    char *curDir = getcwd(NULL, 0);
    if (curDir == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    char *userName = getlogin();
    if (userName == NULL) {
        perror("getlogin");
        free(curDir);
        exit(EXIT_FAILURE);
    }

    char *homeName = (char *) malloc(strlen(userName) + strlen("/home/"));
    if (homeName == NULL) {
        perror("malloc");
        free(curDir);
        exit(EXIT_FAILURE);
    }

    strcpy(homeName, "/home/");
    strcat(homeName, userName);

    if (!strncmp(curDir, homeName, strlen(homeName))) {
        char *result = removeHome(curDir, strlen(homeName));
        free(curDir);
        free(homeName);
        return result;
    }

    free(homeName);
    return curDir;
}


