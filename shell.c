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
			_strcmp(cmd, "unsetenv") == 0 ||
			_strcmp(cmd, "help") == 0);
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
	char *comment = _strchr(line, '#');

	if (comment != NULL)
		*comment = '\0';

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
	char *path_copy_local = _strdup(path_copy);

	if (path_copy_local == NULL)
	{
		perror("Memory allocation error");
		exit(1);
	}

	if (_strchr(args[0], '/') != NULL)
	{
		execute_direct_command(args, argv, linecount, path_copy_local);
	}
	else
	{
		execute_path_command(args, path_copy_local, argv, linecount);
	}
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
	if (_strcmp(args[0], "help") == 0)
	{
		print_help(args[1]);
		return;
	}
}
/**
 * process_command - Process a command
 * @args: Array of arguments
 * @argv: Array of arguments passed to the program
 * @linecount: Line count
 * @status: Exit status
 * @line: Input line
 * @path_copy: Copy of the PATH environment variable
 * Return: Nothing
 */
void process_command(char **args, char **argv, int linecount, int *status,
					 char *line, char *path_copy)
{
	if (is_builtin(args[0]))
	{
		handle_command(args, argv, linecount, status, line, path_copy);
	}
	else
	{
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
			cleanup_resources(line, path_copy);
			exit(1);
		}
		else if (pid == 0)
		{
			char *new_path_copy = handle_path();

			if (new_path_copy == NULL)
			{
				fprintf(stderr, "Failed to get PATH\n");
				cleanup_resources(line, path_copy);
				exit(1);
			}
			execute_command(args, new_path_copy, argv, linecount);
			free(new_path_copy);
		}
		else
		{
			wait(status);
		}
	}
}
