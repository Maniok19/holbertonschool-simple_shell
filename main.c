#include "shell.h"
/**
 * handle_path - Get the PATH environment variable
 * Return: A copy of the PATH environment variable
 */
char *handle_path(void)
{
	char *path = _getenv("PATH");
	char *path_copy = _strdup(path);

	if (path == NULL || path_copy == NULL)
	{
		perror("Error");
		return (NULL);
	}
	return (path_copy);
}
/**
 * read_input - Read input from the user
 * @line: Pointer to the input line
 * @len: Pointer to the length of the input line
 * Return: 1 if the input was read successfully, 0 otherwise
 */
int read_input(char **line, size_t *len)
{
	return (getline(line, len, stdin) != -1);
}
/**
 * prompt_user - Print the prompt to the user
 * @interactive: Flag to indicate if the shell is interactive
 * Return: Nothing
 */
void prompt_user(int interactive)
{
	if (interactive)
	{
		printf("$ ");
		fflush(stdout);
	}
}
/**
 * main_loop - Main loop of the shell
 * @argv: Array of arguments
 * @interactive: Flag to indicate if the shell is interactive
 * Return: Nothing
 */
void main_loop(char **argv, int interactive)
{
	char *line = NULL;
	char *args[100] = {NULL};
	char *path_copy = handle_path();
	size_t len = 0;
	int linecount = 0, status = 0, i = 0;
	char **commands;
	int command_count;

	while (1)
	{
		prompt_user(interactive);
		if (!read_input(&line, &len))
		{
			free(line);
			break;
		}
		linecount++;
		commands = split_commands(line, &command_count);
		if (!commands)
		{
			fprintf(stderr, "Memory allocation error\n");
			continue;
		}
		for (i = 0; i < command_count; i++)
		{
			tokenize_input(commands[i], args);
			if (args[0] == NULL)
				continue;
			process_command(args, argv, linecount, &status, line, path_copy);
		}
		for (i = 0; i < command_count; i++)
			free(commands[i]);
		free(commands);
		if (!interactive)
			break;
	}
	free(line);
	if (path_copy)
		free(path_copy);
	exit(WEXITSTATUS(status));
}
/**
 * main - Entry point
 * @argc: Argument count
 * @argv: Array of arguments
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char **argv)
{
	int interactive = isatty(STDIN_FILENO);

	(void)argc;

	signal(SIGINT, handle_sigint);

	main_loop(argv, interactive);

	return (0);
}
