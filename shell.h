#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>

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
void tokenize_input(char *line, char **args);
int handle_exit(char **args);
int handle_cd(char **args, int linecount, char **argv);
void handle_sigint(int sig);
void execute_command(char **args, char *path, char **argv, int linecount);
void handle_command(char **args, char **argv, int linecount, int *status,
					char *line, char *path_copy);
int handle_setenv(char **args);
int handle_unsetenv(char **args);
void main_loop(char **argv, int interactive);
int is_builtin(char *cmd);


#endif
