#include "listDir.h"
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int listDir(char *PATH) {
    struct dirent *entry;
    DIR *dir;
    if (!strcmp(PATH, "")) {
        dir = opendir(".");
    } else {
        dir = opendir(PATH);
    }
    if (dir == NULL) {
        char *errorMsg = (char *) malloc(strlen("fopen: file \"\"") + strlen(PATH) + 1);
        sprintf(errorMsg, "opendir: file \"%s\"", PATH);
        perror(errorMsg);
        free(errorMsg);
        return 1;
    }
    while ((entry = readdir(dir)) != NULL) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;
        printf("%s\n", entry->d_name);
    }
    printf("\n");
    return 0;
}
