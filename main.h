#ifndef MAIN_H
#define MAIN_H

#include <sys/stat.h>

char **split(char *s, const char *delim);
char *_getenv(char *);
char *strjoin(const char *, const char *); 
int _strlen(char *);
char *_strdup(char *);
int _strcmp(const char *, const char *);
char *_getenv(char *);
int _setenv(const char *, const char *, int);
int _unsetenv(const char *);
void non_interactive_op(char **, struct stat *);
void interactive(pid_t *, char *, size_t *, char **, int *, struct stat *);

extern char **environ;

#endif
