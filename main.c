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
 * handle_commands - Handle multiple commands
 * @cmds: Array of commands
 * @command_count: Number of commands
 * @args: Array of arguments
 * @argv: Array of arguments passed to the program
 * @linecount: Line count
 * @status: Exit status
 * @line: Input line
 * @path_copy: Copy of the PATH environment variable
 * Return: Nothing
 */
void handle_commands(char **cmds, int command_count, char **args, char **argv,
					int linecount, int *status, char *line, char *path_copy)
{
	int i;

	for (i = 0; i < command_count; i++)
	{
		tokenize_input(cmds[i], args);
		if (args[0] == NULL)
			continue;
		if (is_builtin(args[0]) && _strcmp(args[0], "exit") == 0)
		{
			*status = handle_exit(args);
			cleanup_commands(cmds, command_count);
			cleanup_resources(line, path_copy);
			exit(*status);
		}
		process_command(args, argv, linecount, status, line, path_copy);
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
	int linecount = 0, status = 0, command_count;
	ssize_t read_bytes;

	if (!path_copy)
	{
		fprintf(stderr, "Failed to get PATH\n");
		return;
	}
	while (1)
	{
		prompt_user(interactive);
		read_bytes = getline(&line, &len, stdin);
		if (read_bytes == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		if (read_bytes == 1 && line[0] == '\n')
			continue;
		linecount++;
		cmds = split_commands(line, &command_count);
		if (!cmds)
		{
			fprintf(stderr, "Memory allocation error\n");
			continue;
		}
		handle_commands(cmds, command_count, args, argv,
						 linecount, &status, line, path_copy);
		cleanup_commands(cmds, command_count);
		if (!interactive)
			break;
	}
	cleanup_resources(line, path_copy);
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
