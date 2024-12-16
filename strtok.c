#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int _strtok(char *str, char *delim)
{
	char *token;
	token = strtok(str, delim);
	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, delim);
	}

	return (0);
}

int main (void)
{
	char str[] = "Hello, World! This is a test";
	char *delim = " ,!";

	_strtok(str, delim);
	return (0);
}