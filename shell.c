#include "shell.h"
/**
 * handle_setenv - handles the setenv builtin command
 * @args: the command arguments
 * Return: 0 on success, 1 on failure
 */
int handle_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (1);
	}
	if (setenv(args[1], args[2], 1) != 0)
	{
		fprintf(stderr, "Failed to set environment variable\n");
		return (1);
	}
	return (0);
}

/**
 * handle_unsetenv - handles the unsetenv builtin command
 * @args: the command arguments
 * Return: 0 on success, 1 on failure
 */
int handle_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (1);
	}
	if (unsetenv(args[1]) != 0)
	{
		fprintf(stderr, "Failed to unset environment variable\n");
		return (1);
	}
	return (0);
}

/**
 * handle_cd - handles the cd command
 * @args: the command arguments
 * @linecount: the line count
 * @argv: the argument vector
 * Return: 0 on success, 1 on failure
 */

int handle_cd(char **args, int linecount, char **argv)
{
	char *dir = args[1];
	char cwd[1024];
	char *old_pwd;

	if (dir == NULL || strcmp(dir, "~") == 0)
		dir = _getenv("HOME");
	else if (strcmp(dir, "-") == 0)
	{
		old_pwd = _getenv("OLDPWD");
		if (old_pwd == NULL || *old_pwd == '\0')
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
				printf("%s\n", cwd);
			else
				perror("getcwd");
			return (0);
		}
		dir = old_pwd;
		printf("%s\n", dir);
	}

	if (chdir(dir) == -1)
	{
		printf("%s: %d: %s: can't cd to %s\n", argv[0], linecount, args[0], dir);
		return (1);
	}

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		setenv("OLDPWD", _getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
	else
	{
		perror("getcwd");
		return (1);
	}
	return (0);
}

/**
 * handle_sigint - handles the SIGINT signal
 * @sig: the signal
 */

void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 3);
	fflush(stdout);
}
/**
 * handle_exit - handles the exit command
 * @args: the command arguments
 * Return: exit status
 */
int handle_exit(char **args)
{
	int status = 0;

	if (args[1] != NULL)
	{
		status = atoi(args[1]);
		if (status < 0)
		{
			fprintf(stderr, "./shell: 1: exit: Illegal number: %s\n", args[1]);
			return (2);
		}
	}
	return (status);
}
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

	(void)argc;
	signal(SIGINT, handle_sigint);

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
		if (_strcmp(args[0], "cd") == 0)
		{
			handle_cd(args, linecount, argv);
			continue;
		}
		if (_strcmp(args[0], "exit") == 0)
		{
			status = handle_exit(args);
			free(line);
			if (path_copy)
				free(path_copy);
			exit(status);
		}
		if (_strcmp(args[0], "env") == 0)
		{
			print_env();
			continue;
		}
		if (_strcmp(args[0], "setenv") == 0)
		{
			status = handle_setenv(args);
			continue;
		}
		if (_strcmp(args[0], "unsetenv") == 0)
		{
			status = handle_unsetenv(args);
			continue;
		}
		pid = fork();
		if (pid == -1)
			return (1);
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
	return (WEXITSTATUS(status));
}
