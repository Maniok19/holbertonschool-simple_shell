#include "shell.h"

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
 * Return: void
 */

void execute_command(char **args, char *path_copy)
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
			exit(1);
		}
		perror("Command not found");
		exit(1);
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
			break;
		}
		dir = strtok(NULL, ":");
	}
	perror("Command not found");
	exit(1);
}

/**
 * main - the main function
 * Return: 0
 */

int main(void)
{
	pid_t pid;
	char *line = NULL;
	size_t len = 0;
	char *args[100] = {NULL};
	char *path = _getenv("PATH");
	char *path_copy = _strdup(path);

	panneau_bienvenue();
	while (1)
	{
		printf("$ ");
		if (getline(&line, &len, stdin) == -1)
			break;
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
			execute_command(args, path_copy);
		}
		else
			wait(NULL);
	}
	free(line);
	free(path_copy);
	return (0);
}
