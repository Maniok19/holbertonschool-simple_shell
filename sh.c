#include "shell.h"

/**
 * is_builtin - checks if a command is a builtin
 * @cmd: the command
 * Return: 1 if builtin, 0 if not
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
 * main - the main function
 * @argc: the argument count
 * @argv: the argument vector
 * Return: 0 on success
 */

int main(int argc, char **argv)
{
	int interactive = isatty(STDIN_FILENO);

	(void)argc;
	signal(SIGINT, handle_sigint);
	main_loop(argv, interactive);
	return (0);
}
