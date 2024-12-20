#include "shell.h"

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
	int i;

	printf("\033[2J\033[H");
	for (i = 0; i < nombreLignes; i++)
	{
		printf("%s\n", lignes[i]);
	}

	printf("\n");
}
