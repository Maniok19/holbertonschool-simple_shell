#include "shell.h"
/**
 * cleanup_commands - Free the memory allocated for the commands
 * @cmds: Array of commands
 * @command_count: Number of commands
 */
void cleanup_commands(char **cmds, int command_count)
{
	int i;

	if (cmds)
	{
		for (i = 0; i < command_count; i++)
		{
			free(cmds[i]);
		}
		free(cmds);
	}
}
/**
 * cleanup_resources - Free the memory allocated for the line and path_copy
 * @line: Line read from getline
 * @path_copy: Copy of the PATH environment variable
 */
void cleanup_resources(char *line, char *path_copy)
{
	if (line)
		free(line);
	if (path_copy)
		free(path_copy);
}
