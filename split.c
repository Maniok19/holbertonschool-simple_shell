#include "shell.h"
/**
 * split_commands - Split a line into multiple commands
 * @line: The line to split
 * @count: The number of commands
 * Return: An array of commands
 */
char **split_commands(char *line, int *count)
{
	char **commands = NULL;
	char *token;
	int i = 0, j = 0;

	*count = 0;
	commands = malloc(sizeof(char *) * 100);
	if (!commands)
	{
		free(commands);
		return (NULL);
	}
	token = strtok(line, ";");
	while (token != NULL)
	{
		commands[i] = _strdup(token);
		if (!commands[i])
		{
			for (j = 0; j < i; j++)
				free(commands[j]);
			free(commands);
			return (NULL);
		}
		i++;
		token = strtok(NULL, ";");
	}
	commands[i] = NULL;
	*count = i;

	return (commands);
}
