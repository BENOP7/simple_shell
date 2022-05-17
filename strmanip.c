#include <string.h>
#include <stdlib.h>

/**
 * split - split a string into different tokens using a given delimiter
 * @s: string
 * @delim: delimiter
 * Return: pointer to buffer that holds different strings
 */
char **split(char *s, const char *delim)
{
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int n = 0;
	unsigned int k = 0;
	char **tokens = NULL;

	tokens = malloc(sizeof(*tokens) * strlen(s));
	if (!tokens)
		return (NULL);
	while (s[i])
	{
		if (i == 0)
			tokens[n++] = &s[i];
		else
		{
			if (i && s[i - 1] == '\0')
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
