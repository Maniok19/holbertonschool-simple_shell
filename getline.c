#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

		printf("$ ");
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			return (-1);
		}
		printf("%s", line);

	free(line);
	return (0);
}