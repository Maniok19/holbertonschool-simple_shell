#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

extern char **environ;

int _strcmp(char *s1, char *s2);
int _strcat(char *dest, char *src);
int _strcpy(char *dest, char *src);
char *_strdup(char *str);
int _strlen(char *str);
char *_strchr(char *s, char c);
void print_env(void);
char *_getenv(const char *name);
void panneau_bienvenue(void);
char *handle_path(void);


#endif
