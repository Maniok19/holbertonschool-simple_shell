#include "shell.h"
/**
 * print_help - prints help information for built-in commands
 * @command: the command to print help for (or NULL for general help)
 */
void print_help(char *command)
{
	if (command == NULL)
	{
		printf("Simple Shell by Seb and Mano\n");
		printf("Type 'help name' to find out more about the function 'name'.\n\n");
		printf(" help [BUILTIN]\n");
	}
	else if (strcmp(command, "help") == 0)
	{
		printf("help: help [BUILTIN]\n");
		printf("    Display information about builtin commands.\n");
	}
	else if (strcmp(command, "env") == 0)
	{
		printf("env: env\n");
		printf("    Print the environment.\n");
	}
	else if (strcmp(command, "exit") == 0)
	{
		printf("exit: exit [STATUS]\n");
		printf("    Exit the shell with a status of N.\n");
		printf("    is that of the last command executed.\n");
	}
	else if (strcmp(command, "cd") == 0)
	{
		printf("cd: cd [DIRECTORY]\n");
		printf("    Change the shell working directory.\n");
	}
	else if (strcmp(command, "setenv") == 0)
	{
		printf("setenv: setenv [VARIABLE] [VALUE]\n");
		printf("    Set an environment variable.\n");
	}
	else if (strcmp(command, "unsetenv") == 0)
	{
		printf("unsetenv: unsetenv [VARIABLE]\n");
		printf("    Unset an environment variable.\n");
	}
	else
		printf("help: no help topics match '%s'. Try 'help'.\n", command);
}
