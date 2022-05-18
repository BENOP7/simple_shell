#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "main.h"

/**
 * _getenv - get value of an environment variable as a string
 * @name: variable name
 * Return: value of variable
 */
char *_getenv(char *name)
{
	unsigned int i = 0;
	unsigned int j = 0;
	int match = 1;

	while (environ[i])
	{
		match = 1;
		for (j = 0; name[j]; j++)
		{
			if (name[j] != environ[i][j])
			{
				match = 0;
				break;
			}
		}
		if (match)
		{
			if (environ[i][j++] == '=')
				return (&environ[i][j]);
		}
		++i;
	}
	return (NULL);
}

/**
 * _unsetenv - deletes a variable from the list of environment variables
 * @name: name of environment variable
 * Return: 0 if SUCCESS; -1 on FAILURE
 */
int _unsetenv(const char *name)
{
	unsigned int i = 0;
	unsigned int j = 0;

	while (environ[i])
	{
		for (j = 0; name[j]; j++)
		{
			if (name[j] != environ[i][j])
				break;
		}

		if (!name[j])
		{
			environ[i] = '\0';
			return (0);
		}
		++i;
	}

	return (-1);
}

/**
 * _setenv - add a new environment variable or modify an existing one
 * @name: name of environment variable
 * @value: value of variable
 * @overwrite: overwrite flag
 * Return: returns 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	unsigned int i = 0;
	unsigned int j;
	char *var;
	int match;

	if (!name || !value)
		return (-1);
	if (!name && *value == '\0')
		return (0);
	while (environ[i])
	{
		match = 1; /* flag turned on */
		/* check for a mismatch */
		for (j = 0; environ[i][j] != '='; j++)
		{
			if (environ[i][j] != name[j])
			{
				match = 0;
				break;
			}
		}
		if (match)
		{
			if (!overwrite)
				return (0);
			var = strjoin(name, value);
			if (!var)
				return (-1);
			environ[i] = var;
			return (0);
		}
		++i;
	}
	var = strjoin(name, value);
	if (!var)
		return (-1);
	environ[i] = var;
	environ[++i] = NULL;
	return (0);
}
