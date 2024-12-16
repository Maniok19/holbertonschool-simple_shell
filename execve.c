#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - execve example
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t pid;
	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
	int i;

	for (i = 0; i < 5; i++)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (1);
		}
		else if (pid == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("execve");
				return (1);
			}
		}
		else
		{
			wait(NULL);
		}
	}
	return (0);
}
