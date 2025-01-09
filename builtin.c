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

	if (dir == NULL || _strcmp(dir, "~") == 0)
		dir = _getenv("HOME");
	else if (_strcmp(dir, "-") == 0)
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
		fprintf(stderr, "%s: %d: %s: can't cd to %s\n", argv[0], linecount,
		args[0], dir);
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
		status = _atoi(args[1]);
		if (status < 0)
		{
			fprintf(stderr, "./shell: 1: exit: Illegal number: %s\n", args[1]);
			return (2);
		}
	}
	return (status);
}
