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
 * _getenv - gets the environment
 * @name: the name of the environment
 * Return: the value of the environment variable
 */
