#include "shell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

/**
 * read_input - reads the input
 * @line: the input
 * @len: the length of the input
 * Return: void
 */
void read_input(char **line, size_t *len)
{
	if (getline(line, len, stdin) == -1)
	{
		perror("getline");
		exit(EXIT_FAILURE);
	}
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
 * Return: void
 */
void execute_command(char **args, char *path_copy)
{
	struct stat st;
	char *dir;
	char full_path[1024];

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
	char *path = getenv("PATH");
	char *path_copy = _strdup(path);

	while (1)
	{
		printf("$ ");
		read_input(&line, &len);
		if (_strcmp(line, "exit\n") == 0)
			break;
		pid = fork();
		if (pid == -1)
		{
			perror("Fork is not created");
			return (1);
		}
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
