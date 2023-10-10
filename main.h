#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_ARGS 10

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

/* Custom functions */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char *_strcpy(char *dest, const char *src);

/* Shell interface */
char **get_input(void);
char *_strtok(char *str, const char *delim);

#endif
