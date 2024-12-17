#include "shell.h"


/**
 * _getenv - gets the value of an environment variable
 * @name: the name of the environment variable
 *
 * Return: the value of the environment variable, or NULL if not found
 */
char *_getenv(const char *name)
{
	char *result = NULL;
	int i = 0, j;

	while (environ[i])
	{
		j = 0;
		while (name[j] && environ[i][j] && name[j] == environ[i][j])
			j++;
		if (name[j] == '\0' && environ[i][j] == '=')
		{
			result = environ[i] + j + 1;
			break;
		}
		i++;
	}
	return (result);
}
