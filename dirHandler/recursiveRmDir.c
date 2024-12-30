#include "../utils.h"
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int rrmdir(char *PATH) {
    DIR *dir = opendir(PATH);
    if (dir == NULL) {
        perror("opendir failed");
        return -1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;

        // Формируем полный путь
        char *fullPath = (char *) malloc(strlen(PATH) + strlen(entry->d_name) + 2);
        if (fullPath == NULL) {
            perror("malloc failed");
            closedir(dir);
            return -1;
        }
        sprintf(fullPath, "%s/%s", PATH, entry->d_name);

        // Рекурсивно вызываем rrmdir для вложенной директории или удаляем файл
        struct stat statbuf;
        if (stat(fullPath, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
            rrmdir(fullPath);  // Рекурсивно удаляем содержимое подкаталога
        } else {
            remove(fullPath);  // Удаляем файл
        }

        free(fullPath);
    }

    closedir(dir);

    if (isEmptyDir(opendir(PATH))) {
        if (rmdir(PATH) != 0) {
            perror("rmdir failed");
            return -1;
        }
    }

    return SUCCESS;
}
