#include "shell.h"


/**
 * main - execve example
 *
 * Return: Always 0.
 */


int main(void)
{
	pid_t pid;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *token;
	char *args[100] = {NULL};
	int i = 0;

	while (1)
	{
		printf("$ ");
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			return (-1);
		}
		if (_strcmp(line, "exit\n") == 0)
		{
			break;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("Fork is not created");
			return (1);
		}
		else if (pid == 0)
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
			{
				free(line);
				exit(0);
			}

			if (execve(args[0], args, NULL) == -1)
			{
				perror("execve");
			}
		}
		else
		{
			wait(NULL);
		}
	}

	free(line);
	return (0);
}
