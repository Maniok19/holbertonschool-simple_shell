#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

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
void panneau_bienvenue2(void);


#endif
