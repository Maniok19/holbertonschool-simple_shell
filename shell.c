#include "shell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

/**
 * main - exemple d'utilisation de execve
 *
 * Return: Toujours 0.
 */

int main(void)
{
	pid_t pid;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *token;
	char *args[100] = {NULL}; /* Tableau pour stocker les arguments */
	int i = 0;
	struct stat st;
	char *path = getenv("PATH"); /* Récupère la variable d'environnement PATH */
	char *path_copy = strdup(path); /* Copie de PATH */
	char *dir;
	char full_path[1024]; /* Buffer pour stocker le chemin complet */

	while (1)
	{
		printf("$ ");
		read = getline(&line, &len, stdin); /* Lit l'entrée utilisateur */
		if (read == -1)
		{
			return (-1);
		}
		if (_strcmp(line, "exit\n") == 0) /* Vérifie si l'utilisateur veut quitter */
		{
			break;
		}
		pid = fork(); /* Crée un nouveau processus */
		if (pid == -1)
		{
			perror("Fork is not created");
			return (1);
		}
		else if (pid == 0) /* Processus enfant */
		{
			token = strtok(line, " \n"); /* Tokenize la ligne d'entrée */
			i = 0;
			while (token != NULL)
			{
				args[i++] = token; /* Stocke les tokens dans args */
				token = strtok(NULL, " \n");
			}
			args[i] = NULL;
			if (args[0] == NULL) /* Vérifie si aucun argument n'est fourni */
			{
				free(line);
				exit(0);
			}

			dir = strtok(path_copy, ":"); /* Tokenize PATH */
			while (dir != NULL)
			{
				strcpy(full_path, dir); /* Construit le chemin complet */
				strcat(full_path, "/");
				strcat(full_path, args[0]);
				if (stat(full_path, &st) == 0) /* Vérifie si le fichier existe */
				{
					execve(full_path, args, NULL); /* Exécute la commande */
					perror("execve");
					break;
				}
				dir = strtok(NULL, ":");
			}
			perror("Command not found");
			exit(1);
		}
		else /* Processus parent */
		{
			wait(NULL); /* Attend la fin du processus enfant */
		}
	}

	free(line); /* Libère la mémoire allouée */
	free(path_copy); /* Libère la copie de PATH */
	return (0);
}
