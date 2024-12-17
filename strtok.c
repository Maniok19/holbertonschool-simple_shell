#include <stdio.h>
#include <string.h>
#include <stdarg.h>
/**
 * _strtok - Entry point
 * @str: The number of command line arguments
 * @delim: An array containing the program command line arguments
 * Return: Always 0
 */
char *_strtok(char *str, const char *delim)
{
	char *token;

	token = strtok(str, delim);
	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, delim);
	}
	return (str);
}
/**
 * main - Entry point
 * @argc: The number of command line arguments
 * @argv: An array containing the program command line arguments
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char str[] = "Hello,my name is Ben";
	char *delim = " ,";

	_strtok(str, delim);
	return (0);
}
