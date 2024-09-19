#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
	char *input;
	int i;
	
	i = 1;
	while ((input = readline("Minishell : ")) != NULL)
	{
		if (*input) // Vérifie si la chaîne n'est pas vide
			add_history(input); // Traiter la commande
		// if (i % 5 == 0)
		// 	clear_history();
		rl_redisplay();
		if (i % 5 == 0)
			rl_on_new_line();
		if (!(ft_strncmp(input, "clear", 6))) // remplace with ft_strcmp
			rl_clear_history();
		free(input); // Libérer la mémoire allouée par readline
		i++;
	}

	return 0;
}