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
	ssize_t c = 0;
	char *buf = NULL;
	size_t n = 0;
	char **args = NULL;

	/*struct stat st;*/
	if (argc == 1)
	{
		while (c != EOF)
		{
			if (isatty(STDIN_FILENO))
				_puts("$ ");
			c = getline(&buf, &n, stdin);
			if (c < 0)
				break;
			args = split(rmspc(buf), " ");
			execute(args);

		}
	}
	free(buf);
	return (0);
}

/**
 * free_variables - free all memory allocations in the program
 * buf: pointer to the memory buffer
 * args: argument list
 */
void free_variables(void)
{

}

/**
 * check_EOF - check end of file
 * k: return value of getline (ssize_t)
 * buf: buffer
 * args: argument list
 */
void check_EOF(void)
{
}

/**
 * check_exit - check if the program should stop
 * args: argument list
 */
void check_exit(void)
{
}

void execute(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	switch (pid)
	{
		case 0:
			if (execve(args[0], args, NULL) == -1)
			{
				perror(args[0]);
				exit(1);
			}
			break;
		case -1:
			perror(args[0]);
			break;
		default:
			free(args);
			wait(&status);
			break;
	}
}
