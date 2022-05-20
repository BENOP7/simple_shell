#include <stdlib.h>
#include <unistd.h>
#include "main.h"

/**
 * _printenv - print environment variables of the current program
 * @args: command
 * Return: 0 on success
 */
int _printenv(char **args)
{
	unsigned int i = 0;

	if (!args || !args[0])
		return (-1);

	if (_strcmp(args[0], "env") == 0)
	{
		while (environ[i])
		{
			_puts(environ[i]);
			_putchar('\n');
			++i;
		}
	}
	return (0);
}
