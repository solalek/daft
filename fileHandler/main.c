#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

FILE *file;

enum Options {
    EDIT = 1,
    READ = 2
};

bool isHaveNewLine(char *str) {
    char newLine[] = "\n";
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == newLine[0]) {
            return true;
        }
    }
    return false;
}

bool isEqual(char *str1, char *str2) {
    if (strlen(str1) != strlen(str2)) {
        return false;
    }
    for (int i = 0; i < strlen(str1); i++) {
        if (str1[i] != str2[i]) {
            return false;
        }
    }
    return true;
}

int editFile(char *PATH) {
    file = fopen(PATH, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }
    system("clear");
    printf("Enter text to write in file(exit to quit):\n");
    char buffer[100];
    int i = 1;
    fgets(buffer, 100, stdin);
    while (true) {
        printf("%d line: ", i);
        fgets(buffer, 100, stdin);
        if (isEqual(buffer, "exit\n")) {
            printf("\nExiting...\n");
            break;
        }
        fprintf(file, "%s", buffer);
        i++;
    }
    fclose(file);
    return 1;
}

int readFile(char *PATH) {
    file = fopen(PATH, "r");
    char ch;
    while ((ch = getc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
    return 1;
}

int main() {
    system("clear");
    printf("1. Write file.\n2. Read file.\nEnter your option: ");
    int UserOption;
    scanf("%d", &UserOption);
    char buffer[100];
    printf("\nEnter file name: ");
    scanf("%s", buffer);
    char PATH[strlen(buffer)];
    strcpy(PATH, buffer);
    if (UserOption == EDIT) {
        editFile(PATH);
    } else if (UserOption == READ) {
        readFile(PATH);
    }
    return 0;
}
