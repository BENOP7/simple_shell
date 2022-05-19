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
int main(int argc, char **argv, char **env __attribute__((unused)))
{
	pid_t my_pid;
	int status;
	char *buf = NULL;
	size_t n = 90;
	char **args = NULL;
	struct stat st;

	if (argc == 1)
	{
		interactive(&my_pid, buf, &n, args, &status, &st);
	}
	else
		non_interactive_op(argv, &st);
	free_variables(buf);
	return (0);
}
/**
 * non_interactive_op - non-interactive mode
 * @argv: argument list
 * @st: stat structure
 * Return: void
 */
void non_interactive_op(char **argv, struct stat *st)
{
	if (stat(argv[1], st) == 0)
	{
		if (execve(argv[1], argv + 1, NULL) == -1)
		{
			perror("Error");
			exit(1);
		}
	}
}

void interactive(pid_t *my_pid, char *buf, size_t *n, char **args,
		int *status, struct stat *st)
{
	while (1)
	{
		buf = malloc(*n);
		if (!buf)
			exit(1);
		_puts("$ ");
		if (getline(&buf, n, stdin) == -1)
		{
			free_variables(buf);
			exit(1);
		}
		args = split(buf, " ");
		if (strcmp(args[0], "exit") == 0)
		{
			free_variables(buf);
			exit(0);
		}
		*my_pid = fork();
		if (*my_pid == 0 && !stat(args[0], st))
		{
			if (execve(args[0], args, NULL) == -1)
			{
				free_variables(buf);
				perror("Execve");
				exit(1);
			}
		}
		else if (*my_pid == 0)
		{
			free_variables(buf);
			perror("Command not found");
			exit(1);
		}
		else
		{
			free(buf);
			wait(status);
		}
	}
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
