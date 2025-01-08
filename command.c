#include "shell.h"

/**
 * execute_direct_command - Execute a command with a direct path
 * @args: Array of arguments
 * @argv: Array of arguments passed to the program
 * @linecount: Line count
 * @path_copy_local: Copy of the PATH environment variable
 */
void execute_direct_command(char **args, char **argv,
							int linecount, char *path_copy_local)
{
	struct stat st;

	if (stat(args[0], &st) == 0)
	{
		execve(args[0], args, environ);
		perror("execve");
		free(path_copy_local);
		exit(1);
	}
	fprintf(stderr, "%s: %d: %s: not found\n", argv[0], linecount, args[0]);
	free(path_copy_local);
	exit(127);
}
/**
 * execute_path_command - Execute a command with a path
 * @args: Array of arguments
 * @path_copy_local: Copy of the PATH environment variable
 * @argv: Array of arguments passed to the program
 * @linecount: Line count
 */
void execute_path_command(char **args, char *path_copy_local,
							char **argv, int linecount)
{
	struct stat st;
	char *dir;
	char full_path[1024];

	dir = strtok(path_copy_local, ":");
	while (dir != NULL)
	{
		_strcpy(full_path, dir);
		_strcat(full_path, "/");
		_strcat(full_path, args[0]);
		if (stat(full_path, &st) == 0)
		{
			execve(full_path, args, environ);
			perror("execve");
			free(path_copy_local);
			exit(1);
		}
		dir = strtok(NULL, ":");
	}
	fprintf(stderr, "%s: %d: %s: not found\n", argv[0], linecount, args[0]);
	free(path_copy_local);
	exit(127);
}
