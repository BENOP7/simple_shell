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
	char **args;
	struct stat st;

	if (argc == 1)
	{
	while (1)
	{
		buf = malloc(n);
		if (!buf)
			return (1);
		printf("$ ");
		if (getline(&buf, &n, stdin) == -1)
			return (0);
		args = split(buf, " ");

		if (strcmp(args[0], "cd") == 0)
		{
			chdir(args[1]);
			continue;
		}
		my_pid = fork();

        if (my_pid == 0 && !stat(args[0], &st))
        {
            if (execve(args[0], args, env) == -1)
            {
                perror("Execve");
                return (3);
            }
        }
	else if (my_pid == 0)
	{
		perror("Command not found");
		return (2);
	}
        else
        {
            wait(&status);

        }
    }
	}
	else
	{
		if (stat(argv[1], &st) == 0)
		{
			if (execve(argv[1], argv + 1, env) == -1)
			{
				perror("Error");
				exit(1);
			}	
		}
	}
    return (0);
}
