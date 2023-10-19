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
int _strcmp(const char *s1, const char *s2);
char *_strtok(char *str, const char *delim);
char *_strconcat(const char *s1, const char *s2);
int _strlen(const char *s);
char *_strchr(char *s, char c);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Shell interface */
char **get_input(void);

char *_getenv(const char *name);
int execute_command(char **args);

/* Converts string to integer */
int string_to_int_conv(const char *str);
int env_builtin(void);
/* Function execution */
void setenv_builtin(char **args);
void unsetenv_builtin(char **args);

char *custom_getenv(const char *var);
void cd_builtin(char **args);
int custom_setenv(const char *name, const char *value);

int _setenv(const char *name, const char *value, int overwrite);

char *_strconcats(const char *str1, const char *str2);

#endif
