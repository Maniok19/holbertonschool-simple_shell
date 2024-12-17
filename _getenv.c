#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
extern char **environ;

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
/**
 * print_path_dirs - prints each directory in the PATH environment variable
 */
void print_path_dirs(void)
{
	char *path = _getenv("PATH");
	char *token;

	if (path == NULL)
	{
		printf("PATH environment variable not found\n");
		return;
	}

	token = strtok(path, ":");
	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, ":");
	}
}
void linked_path(void)
{
	
}
/**
 * main - entry point of the program
 *
 * Return: 0 on success
 */
int main(void)
{
	char *value = _getenv("USER");

	if (value)
		printf("%s\n", value);
	else
		printf("Environment variable not found\n");
	print_path_dirs();
	linked_path();
	return (0);
}
