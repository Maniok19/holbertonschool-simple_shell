#include <stdio.h>
#include <unistd.h>

extern char **environ;

/**
 * main - prints the environment
 * @ac: Argument count
 * @av: Argument vector
 * @env: Environment variables
 *
 * Return: Always 0.
 */

int main(int ac, char **av, char **env)
{
printf("Address of env    : %p\n", (void *)env);
printf("Address of environ: %p\n", (void *)environ);
}
