#ifndef UTILS_H
#define UTILS_H

typedef enum {
    SUCCESS,
    TOO_MANY_ARGS,
    NOT_ENOUGH_ARGS,
    UNKNOWN_COMMAND,
} errorCode;

char *getInput(int *argc, char *args[]);

void helpCommand();

int doCommand(char *command, int argc, char *args[]);

void showError(errorCode code, char *input);

char *getCommandByFlag(int *argc, char *argv[]);

#endif
