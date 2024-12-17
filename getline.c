#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
/**
 * main - Write a program that prints "$ ", waits for the user to a command,
 * and prints it on the next line.
 * @argc: The number of command-line arguments
 * @argv: An array of command-line arguments
 * Return: Always 0 (Success)
 */
int main(int argc, char *argv[])
{
	char *start = "$ ";
	ssize_t read;
	char *line = NULL;
	size_t len = 10;
	FILE *fp = stdin;

	printf("%s", start);
	read = getline(&line, &len, fp);
	if (read == -1)
		return (0);
	printf("%s", line);
	free(line);
	return (0);
}
