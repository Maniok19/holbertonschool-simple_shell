#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

extern char **environ;

/**
 * struct path_s - singly linked list
 * @p: string - (malloc'ed string)
 * @next: points to the next node
 */

typedef struct path_s
{
	char *p;
	struct path_s *next;
} path_t;

int _strcmp(char *s1, char *s2);
char *_getenv(const char *name);


#endif
