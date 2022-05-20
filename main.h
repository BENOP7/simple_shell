#ifndef MAIN_H
#define MAIN_H

#include <sys/stat.h>

int _putchar(char c);
void _puts(char *);
char **split(char *s, const char *delim);
char *_getenv(char *);
char *strjoin(const char *, const char *);
int _strlen(char *);
char *_strdup(char *);
int _strcmp(const char *, const char *);
char *_getenv(char *);
int _setenv(const char *, const char *, int);
int _unsetenv(const char *);
void free_variables(char *, char **);
void check_EOF(ssize_t, char *, char **);
void check_exit(char **);
int _printenv(char **);

extern char **environ;

#endif
