#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include "main.h"



/**
 * main - a simple version of the shell
 * @argc: number of arguments in the argument list
 * @argv: argument list
 * @env: enviroment variable list
 *
 * Return: 0 on success
 */
int main(int argc, char **argv __attribute__((unused)),
		char **env __attribute__((unused)))
{
	pid_t my_pid;
	int status;
	ssize_t k = 0;
	char *buf = NULL;
	size_t n = 0;
	char **args = NULL;
	struct stat st;

	if (argc == 1)
	{
		while (k >= 0)
		{
			if (isatty(STDIN_FILENO))
				_puts("$ ");
			k = getline(&buf, &n, stdin);
			check_EOF(k, buf, args);
			args = split(buf, " ");
			check_exit(args);
			if(_printenv(args) == 0)
				continue;
			my_pid = fork();
			if (my_pid == 0 && !stat(args[0], &st))
			{
				if (execve(args[0], args, NULL) == -1)
				{
					char *nm = *args;

					free_variables(buf, args);
					perror(nm);
					return (EXIT_FAILURE);
				}
			}
			else if (my_pid == 0)
			{
				/*free_variables(buf);*/
				perror(args[0]);
				return (EXIT_FAILURE);
			}
			wait(&status);
		}
	}
	return (0);
}

/**
 * free_variables - free all memory allocations in the program
 * @buf: pointer to the memory buffer
 * @args: argument list
 */
void free_variables(char *buf, char **args)
{
	free(buf);
	free(args);
}

/**
 * check_EOF - check end of file
 * @k: return value of getline
 * @buf: buffer
 * @args: argument list
 */
void check_EOF(ssize_t k, char *buf, char **args)
{

	if (k == EOF)
	{
		free_variables(buf, args);
		exit(EXIT_SUCCESS);
	}
}

/**
 * check_exit - check if the program should stop
 * @args: argument list
 */
void check_exit(char **args)
{
	if (_strcmp(args[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
}
