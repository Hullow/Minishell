/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_count_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:41:17 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/10 12:08:30 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// Fonction pour compter les mots dans une variable d'environnement
int	count_env_variable_words(char *var)
{
	char	*env_value;
	char	**split_env;
	int		count;
	int		k;

	count = 0;
	k = 0;
	env_value = getenv(var);
	if (env_value)
	{
		split_env = ft_split(env_value, ' ');
		while (split_env[k])
		{
			count++;
			k++;
		}
		ft_free_array(split_env);
	}
	return (count);
}

// Fonction pour compter les mots d'une variable
int	count_variable_words(char *arg, int *j)
{
	int	word_count;

	word_count = 0;
	if (arg[*j + 1] == '?')
	{
		word_count++;
		*j += 2;
	}
	else
	{
		word_count += count_env_variable_words(&arg[*j + 1]);
		(*j)++;
		while (arg[*j] && !ft_isspace(arg[*j]))
			(*j)++;
	}
	return (word_count);
}

// Fonction pour compter les mots non variables
int	count_non_variable_words(char *arg, int *j)
{
	int	word_count;

	word_count = 1;
	while (arg[*j] && arg[*j] != '$')
		(*j)++;
	return (word_count);
}

// Fonction pour compter les mots dans un argument
int	count_words_in_arg(char *arg)
{
	int	j;
	int	word_count;

	j = 0;
	word_count = 0;
	while (arg[j])
	{
		if (arg[j] == '$')
			word_count += count_variable_words(arg, &j);
		else
			word_count += count_non_variable_words(arg, &j);
	}
	return (word_count);
}

// Fonction pour compter le nombre total de mots
int	count_total_words(t_command *cmd_list)
{
	int	word_count;
	int	i;

	word_count = 0;
	i = 0;
	while (cmd_list->args[i])
	{
		word_count += count_words_in_arg(cmd_list->args[i]);
		i++;
	}
	return (word_count);
}
