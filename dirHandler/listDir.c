#include "listDir.h"
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int listDir(int argc, char *argv[]) {
    if (argc < 2) {
        struct dirent *entry;
        char *PATH;
        if (argc == 0) {
            PATH = (char *) malloc(strlen(".") + 1);
            strcpy(PATH, ".");
        } else {
            PATH = (char *) malloc(strlen(argv[0]) + 1);
            strcpy(PATH, argv[0]);
        }
        DIR *dir = opendir(PATH);
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
    }
    return 0;
}
