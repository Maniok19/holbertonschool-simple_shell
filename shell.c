#include "shell.h"

/**
 * handle_path - handles the PATH
 * Return: the path
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
 * tokenize_input - tokenizes the input
 * @line: the input
 * @args: the tokenized input
 * Return: void
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
 * execute_command - executes the command
 * @args: the command
 * @path_copy: the path
 * @argv: the argument vector
 * @linecount: the line count
 * Return: void
 */

void execute_command(char **args, char *path_copy, char **argv, int linecount)
{
	struct stat st;
	char *dir;
	char full_path[1024];

	/*Check if the command contains a slash*/
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
 * handle_command - handles the command
 * @args: the command
 * @argv: the argument vector
 * @linecount: the line count
 * @status: the exit status
 * @line: the input
 * @path_copy: the path
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
 * main_loop - the main loop
 * @argv: the argument vector
 * @interactive: the interactive mode
 */

void main_loop(char **argv, int interactive)
{
	pid_t pid;
	char *line = NULL, *args[100] = {NULL}, *path_copy = handle_path();
	size_t len = 0;
	int linecount = 0, status = 0;

	while (1)
	{
		if (interactive)
			printf("$ ");
		fflush(stdout);
		if (getline(&line, &len, stdin) == -1)
		{
			free(line);
			break;
		}
		linecount++;
		tokenize_input(line, args);
		if (args[0] == NULL)
			continue;
		if (is_builtin(args[0]))
		{
			handle_command(args, argv, linecount, &status, line, path_copy);
			continue;
		}
		pid = fork();
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
			wait(&status);
		if (!interactive)
			break;
	}
	free(line);
	if (path_copy)
		free(path_copy);
	exit(WEXITSTATUS(status));
}
