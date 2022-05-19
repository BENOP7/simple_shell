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
	size_t n = 90;
	char **args = NULL;
	struct stat st;

	buf = malloc(n * sizeof(*buf));
	if (!buf)
		return (EXIT_FAILURE);
	if (argc == 1)
	{
		while (k != EOF)
		{
			if (isatty(STDIN_FILENO))
				_puts("$ ");
			if ((k = getline(&buf, &n, stdin)) == -1)
			{
				return (0);
			}
			args = split(buf, " ");
			if (strcmp(args[0], "exit") == 0)
			{
				free_variables(buf);
				return (EXIT_SUCCESS);
			}
			my_pid = fork();
			if (my_pid == 0 && !stat(args[0], &st))
			{
				if (execve(args[0], args, NULL) == -1)
				{
					free_variables(buf);
					perror(args[0]);
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
 * Return: void
 */
void free_variables(char *buf)
{
	free(buf);
}
