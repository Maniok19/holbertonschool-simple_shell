#include "shell.h"
/**
 * handle_path - Get the PATH environment variable
 * Return: A copy of the PATH environment variable
 */
char *handle_path(void)
{
	char *path = _getenv("PATH");
	char *path_copy = NULL;

	if (path == NULL)
	{
		fprintf(stderr, "Error: PATH environment variable not found\n");
		return (NULL);
	}
	path_copy = _strdup(path);
	if (path_copy == NULL)
	{
		fprintf(stderr, "Error: Memory allocation error\n");
		return (NULL);
	}
	return (path_copy);
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
		write(STDOUT_FILENO, "$ ", 2);
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
	char *line = NULL, *args[100] = {NULL}, *path_copy = handle_path(), **cmds;
	size_t len = 0;
	int linecount = 0, status = 0, i, command_count;
	ssize_t read_bytes;

	while (1)
	{
		prompt_user(interactive);
		linecount++;
		read_bytes = getline(&line, &len, stdin);
		if (read_bytes == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		if (read_bytes == 1 && line[0] == '\n')
			continue;
		line[strcspn(line, "\n")] = 0;
		cmds = split_commands(line, &command_count);
		if (!cmds)
		{
			continue;
		}
		for (i = 0; i < command_count; i++)
		{
			tokenize_input(cmds[i], args);
			if (args[0] == NULL)
				continue;
			process_command(args, argv, linecount, &status, line, path_copy);
		}
		for (i = 0; i < command_count; i++)
			free(cmds[i]);
		free(cmds);
		if (!interactive)
			continue;
	}
	free(line);
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
