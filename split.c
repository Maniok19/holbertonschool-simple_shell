#include "shell.h"
#include <stdlib.h>
#include <string.h>

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
	int i = 0;

	if (line == NULL || count == NULL)
		return (NULL);
	*count = 0;
	for (i = 0; line[i]; i++)
	{
		if (line[i] == ';')
			(*count)++;
	}
	(*count)++;
	commands = malloc(sizeof(char *) * (*count + 1));
	if (commands == NULL)
		return (NULL);
	i = 0;
	token = strtok(line, ";");
	while (token != NULL)
	{
		commands[i] = strdup(token);
		if (commands[i] == NULL)
		{
			for (int j = 0; j < i; j++)
				free(commands[j]);
			free(commands);
			return (NULL);
		}
		i++;
		token = strtok(NULL, ";");
	}
	commands[i] = NULL;
	return (commands);
}
