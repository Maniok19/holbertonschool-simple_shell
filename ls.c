#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - Entry point of the program
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	pid_t pid;
	int status;
	int i = 0;
	char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};

	while (i < 5)
	{
		pid = fork();
		if (pid == 0)
			execve(argv[0], argv, NULL);
		else
			wait(&status);
		i++;
	}
	return (0);
}
