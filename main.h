#ifndef MAIN_H
#define MAIN_H

#include <sys/stat.h>
#include <stdio.h>

int _putchar(char c);
void _puts(char *);
char **split(char *s, const char *delim);
char *_getenv(char *);
char *strjoin(const char *, const char *);
int _strlen(char *);
char *_strdup(char *);
int _strcmp(const char *, const char *);
void execute(char **);
char *_getenv(char *);
int _setenv(const char *, const char *, int);
int _unsetenv(const char *);
void free_variables(void);
void check_EOF(void);
void check_exit(void);
int _printenv(char **);
int _getline(char **, int *, FILE *);

extern char **environ;

#endif
