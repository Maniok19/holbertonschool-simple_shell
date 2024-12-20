#include "shell.h"
/**
 * is_builtin - Check if a command is a built-in
 * @cmd: Command to check
 * Return: 1 if the command is a built-in, 0 otherwise
 */
int is_builtin(char *cmd)
{
	return (_strcmp(cmd, "cd") == 0 ||
			_strcmp(cmd, "exit") == 0 ||
			_strcmp(cmd, "env") == 0 ||
			_strcmp(cmd, "setenv") == 0 ||
			_strcmp(cmd, "unsetenv") == 0);
}
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
 * tokenize_input - Tokenize the input line
 * @line: Input line
 * @args: Array to store the tokens
 * Return: Nothing
 */
void tokenize_input(char *line, char **args)
{
	char *token;
	int i = 0;

	token = strtok(line, " \n");
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " \n");
	}
	args[i] = NULL;
}
/**
 * execute_command - Execute a command
 * @args: Array of arguments
 * @path_copy: Copy of the PATH environment variable
 * @argv: Array of arguments passed to the program
 * @linecount: Line count
 * Return: Nothing
 */
void execute_command(char **args, char *path_copy, char **argv, int linecount)
{
	struct stat st;
	char *dir;
	char full_path[1024];

	if (_strchr(args[0], '/') != NULL)
	{
		if (stat(args[0], &st) == 0)
		{
			execve(args[0], args, NULL);
			exit(0);
		}
		printf("%s: %d: %s: not found\n", argv[0], linecount, args[0]);
		exit(127);
	}

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		_strcpy(full_path, dir);
		_strcat(full_path, "/");
		_strcat(full_path, args[0]);
		if (stat(full_path, &st) == 0)
		{
			execve(full_path, args, NULL);
			exit(0);
		}
		dir = strtok(NULL, ":");
	}

	printf("%s: %d: %s: not found\n", argv[0], linecount, args[0]);
	exit(127);
}
/**
 * handle_command - Handle built-in commands
 * @args: Array of arguments
 * @argv: Array of arguments passed to the program
 * @linecount: Line count
 * @status: Exit status
 * @line: Input line
 * @path_copy: Copy of the PATH environment variable
 * Return: Nothing
 */
void handle_command(char **args, char **argv, int linecount, int *status,
					char *line, char *path_copy)
{
	if (_strcmp(args[0], "cd") == 0)
	{
		handle_cd(args, linecount, argv);
		return;
	}
	if (_strcmp(args[0], "exit") == 0)
	{
		*status = handle_exit(args);
		free(line);
		if (path_copy)
			free(path_copy);
		exit(*status);
	}
	if (_strcmp(args[0], "env") == 0)
	{
		print_env();
		return;
	}
	if (_strcmp(args[0], "setenv") == 0)
	{
		*status = handle_setenv(args);
		return;
	}
	if (_strcmp(args[0], "unsetenv") == 0)
	{
		*status = handle_unsetenv(args);
		return;
	}
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
 * read_input - Read input from the user
 * @line: Pointer to the input line
 * @len: Pointer to the length of the input line
 * Return: 1 if the input was read successfully, 0 otherwise
 */
int read_input(char **line, size_t *len)
{
	return (getline(line, len, stdin) != -1);
}

void process_command(char **args, char **argv, int linecount, int *status,
					 char *line, char *path_copy) {
	if (is_builtin(args[0]))
		handle_command(args, argv, linecount, status, line, path_copy);
	else
	{
		pid_t pid = fork();

		if (pid == -1)
			exit(1);
		else if (pid == 0)
		{
			path_copy = handle_path();
			execute_command(args, path_copy, argv, linecount);
			if (path_copy)
				free(path_copy);
			exit(0);
		}
		else
			wait(status);
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
	int linecount = 0;
	int status = 0;

	while (1)
	{
		prompt_user(interactive);

		if (!read_input(&line, &len))
		{
			free(line);
			break;
		}
		linecount++;
		tokenize_input(line, args);
		if (args[0] == NULL)
			continue;
		process_command(args, argv, linecount, &status, line, path_copy);
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
