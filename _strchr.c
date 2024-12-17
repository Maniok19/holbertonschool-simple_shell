#include "shell.h"

/**
 * _strchr - locates a character in a string
 * @s: the string
 * @c: the character
 * Return: a pointer to the first occurrence of the character c in the string s
 */
char *_strchr(char *s, char c)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == c)
		{
			return (s + i);
		}
	}
	return (NULL);
}
/**
 * print_env - prints the environment
 * Return: void
 */
void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
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