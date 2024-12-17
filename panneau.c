#include "shell.h"
#include <stdio.h>
/**
 * panneau_bienvenue - affiche le panneau de bienvenue
 * Return: void
 */
void panneau_bienvenue(void)
{
	const char *lignes[] = {
		"╔══════════════════════════════════════════════════════════════════════════════╗",
		"║                                                                              ║",
		"║   ██████╗ ██╗███████╗███╗   ██╗██╗   ██╗███████╗███╗   ██╗██╗   ██╗███████╗  ║",
		"║   ██╔══██╗██║██╔════╝████╗  ██║██║   ██║██╔════╝████╗  ██║██║   ██║██╔════╝  ║",
		"║   ██████╔╝██║█████╗  ██╔██╗ ██║██║   ██║█████╗  ██╔██╗ ██║██║   ██║█████╗    ║",
		"║   ██╔══██╗██║██╔══╝  ██║╚██╗██║╚██╗ ██╔╝██╔══╝  ██║╚██╗██║██║   ██║██╔══╝    ║",
		"║   ██████╔╝██║███████╗██║ ╚████║ ╚████╔╝ ███████╗██║ ╚████║╚██████╔╝███████╗  ║",
		"║   ╚═════╝ ╚═╝╚══════╝╚═╝  ╚═══╝  ╚═══╝  ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚══════╝  ║",
		"║                                                                              ║",
		"║                         Dans le shell de Seb et Mano                         ║",
		"║                                                                              ║",
		"║                           Path ton chemin mortel                             ║",
		"║                                                                              ║",
		"║                                                                              ║",
		"╚══════════════════════════════════════════════════════════════════════════════╝"
	};

	int nombreLignes = sizeof(lignes) / sizeof(lignes[0]);

	for (int i = 0; i < nombreLignes; i++)
	{
		printf("%s\n", lignes[i]);
	}

	printf("\n");
}
