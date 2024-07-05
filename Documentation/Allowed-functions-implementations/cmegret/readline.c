#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
	char *line;

	// Lire une ligne de l'entrée standard
	line = readline("Minishell: ");

	// Vérifier si la ligne est NULL
	if (line == NULL)
	{
		printf("Aucune entrée détectée ou erreur.\n");
	}
	else {
		// Afficher la ligne lue
		printf("Vous avez entré: %s\n", line);
		// Libérer la mémoire allouée
		free(line);
	}

	return 0;
}