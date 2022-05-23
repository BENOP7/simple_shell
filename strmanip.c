#include <stdlib.h>
#include "main.h"

/**
 * _strlen - returns number of bytes in a string
 * @str: string
 * Return: number of bytes in @str
 */
int _strlen(char *str)
{
	int l = 0;

	while (str[l++])
		;
	return (l);
}

/**
 * strjoin - concatenates two strings
 * @s1: first string
 * @s2: second string
 * Return: pointer to memory buffer conatining resultant string
 */
char *strjoin(const char *s1, const char *s2)
{
	char *mem;
	int len1 = 0;
	int len2 = 0;
	int k;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";

	while (s1[len1])
		len1++;

	while (s2[len2])
		len2++;

	mem = malloc((len1 + len2 + 2) * sizeof(char));

	if (!mem)
		return (NULL);

	for (k = 0; *s1; k++)
	{
		mem[k] = *s1++;
	}

	mem[k++] = '=';

	for (; *s2; k++)
	{
		mem[k] = *s2++;
	}
	mem[k] = '\0';

	return (mem);
}

/**
 * rmspc - returns a pointer to a memory buffer containing a given string
 * @str: string
 * Return: pointer to memory containing string
 */
char *rmspc(char *str)
{
	char space = ' ';
	char *ptr;
	char *trim = NULL;

	while (*str)
	{
		trim = str;
		if (*str != space)
			break;
		str++;
	}

	while (*str)
	{
		ptr = str;
		str++;
		if (!*str)
		{
			while (*ptr == space || *ptr == '\n')
			{
				--ptr;
				if (*ptr != space && *ptr != '\n')
				{
					*++ptr = '\0';
				}
			}
		}
	}

	return (trim);
}
/**
 * _strcmp - compares two strings
 * @s1: string
 * @s2: string
 * Return: negaive number if s1 < s2, positive number if s1 > s2
 * 0 if s1 equals s2
 */
int _strcmp(const char *s1, const char *s2)
{
	int i = 0;
	int value = 0;

	while (s1[i])
	{
		if (!s2[i])
			return (s1[i]);
		if (s1[i] == s2[i])
		{
			i++;
			continue;
		}
		else
		{
			value = s1[i] - s2[i];
			break;
		}
	}

	if (s1[i] == '\0')
		return (-s2[i]);

	return (value);
}

/**
 * split - split a string into different tokens using a given delimiter
 * @s: string
 * @delim: delimiter
 * Return: pointer to buffer that holds different strings
 */
char **split(char *s, const char *delim)
{
	unsigned int i, j, n, k;
	char **tokens = NULL;
	
	i = j = n = k = 0;
	tokens = malloc(sizeof(*tokens) * _strlen(s));
	if (!tokens)
		return (NULL);
	while (s[i])
	{
		if (i == 0 && s[i] != ' ')
			tokens[n++] = &s[i];
		else
		{
			if (i && s[i - 1] == '\0' && s[i] != ' ')
			{
				tokens[n++] = &s[i];
			}
		}
		if (s[i++] == *delim)
		{
			for (j = 1; delim[j]; j++)
			{
				if (s[i++] != delim[j])
					break;
			}
			if (!delim[j]) /* if there's a match with the delim*/
			{
				for (k = i - j; k < i; k++)
				{
					s[k] = '\0';
				}
			}
		}
		if (s[i + 1] == '\0' && s[i] == '\n')
			s[i] = '\0';
	}
	tokens[n] = NULL;
	return (tokens);
}


