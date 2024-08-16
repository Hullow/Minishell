/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:08:31 by fallan            #+#    #+#             */
/*   Updated: 2024/08/16 12:08:58 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

char ft_find_env(char *input, int i, int j)
{
	// return the env variable in the env list or NULL
}

char get_exit_status()
{
	// return the last exit status
}

int is_question_mark(char c)
{
	if (c == '?')
		return (1);
	return (0);
}

int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char *ft_check_export(char *input, int i, int *end)
{
	int j;

	j = i + 1;
	*end = j; // Définition de la valeur de end
	if (is_digit(input[j])) // Correction: ajout de la condition if
		return ('\0'); // or return (NULL);
	if (is_question_mark(input[j])) // Correction: ajout de la condition if
		return (get_exit_status());
	while (input[j] && (is_digit(input[j]) || is_alpha(input[j]) || input[j] == '_')) // Correction: ajout de parenthèses pour clarifier la condition
		j++;
	*end = j; // Définition de la valeur de end en dehors des conditions pour couvrir tous les cas
	return (ft_find_env(input, i, j));
}

void set_env_value(char *input, char *env)
{
	// replace the env variable by its value
	
	
}

void parsing(char *input)
{
	int i;
	int end;
	char *env;

	i = 0;

	while (input[i])
	{
		if (input[i] == '$')
		{
			env = ft_check_export(input, i, &end); // Passage de l'adresse de end
			if (env)
			{
				replace_value(input, env);
				i = end; // Mise à jour de i pour reprendre après le dernier caractère traité
			}
		}
		else
		{
			i++; // Incrémentation de i déplacée dans le else pour éviter de sauter des caractères
		}
	}
}