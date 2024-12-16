#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>


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
			execve(args[0], args, NULL);
			perror("execve");
		}
		else
		{
			wait(NULL);
		}
	}

	free(line);
	return (0);
}
