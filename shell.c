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
			perror("execve");
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
			perror("execve");
			exit(0);
		}
		dir = strtok(NULL, ":");
	}
	printf("%s: %d: %s: not found\n", argv[0], linecount, args[0]);
	exit(127);
}


/**
 * main - the main function
 * @argc: the argument count
 * @argv: the argument vector
 * Return: 0
 */

int main(int argc, char **argv)
{
	pid_t pid;
	char *line = NULL;
	size_t len = 0;
	char *args[100] = {NULL};
	char *path_copy = handle_path();
	int linecount = 0;
	int interactive = isatty(STDIN_FILENO);
	int status = 0;

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
		if (_strcmp(line, "exit\n") == 0)
			break;
		if (_strcmp(line, "env\n") == 0)
		{
			print_env();
			continue;
		}
		pid = fork();
		if (pid == -1)
			return (1);
		else if (pid == 0)
		{
			tokenize_input(line, args);
			if (args[0] == NULL)
			{
				free(line);
				exit(0);
			}
			path_copy = handle_path();
			execute_command(args, path_copy, argv, linecount);
			if (path_copy)
				free(path_copy);
			if (!interactive)
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
		printf("%d\n", status);
	return (WEXITSTATUS(status));
}
