#include <stdio.h>
#include <unistd.h>

/**
 * main - PID
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t my_pid;

	while (1)
	{
		my_pid = fork();
		if (my_pid == -1)
			break;
	}
	my_pid = getpid();
	printf("%u\n", my_pid);
	return (0);
}
