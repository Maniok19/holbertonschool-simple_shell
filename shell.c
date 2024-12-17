#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/**
 * main - Write a program that prints "$ ", waits for the user to a command,
 * and prints it on the next line.
 * Return: Always 0 (Success)
 */
int main(void)
{
	ssize_t read;
	char *line = NULL;
	size_t len = 0;
	pid_t pid;
	char *args[100] = {NULL};
	char *token;
	int i = 0;

	while (1)
	{
		printf("$ ");

		read = getline(&line, &len, stdin);
		if (read == -1)
			break;

		if (strcmp(line, "exit\n") == 0)
		{
			break;
		}
		pid = fork();
		if (pid == 0)
		{
			token = strtok(line, " \n");
			i = 0;
			while (token != NULL)
			{
				args[i++] = token;
				token = strtok(NULL, " \n");
			}
			args[i] = NULL;
			if (args[0] == NULL)
				exit(0);
			if (execve(args[0], args, NULL) == -1)
				perror("execve");
		}
		else
			wait(NULL);
	}
	free(line);
	return (0);
}
