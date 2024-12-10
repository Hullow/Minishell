/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:41:17 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/10 12:27:19 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// Fonction pour étendre une variable d'environnement et remplir le tableau
int	expand_env_variable(char *var, char **table, int *word_count)
{
	char	*env_value;
	char	**split_env;
	int		k;

	k = 0;
	env_value = getenv(var);
	if (env_value)
	{
		split_env = ft_split(env_value, ' ');
		while (split_env[k])
		{
			table[*word_count] = ft_strdup(split_env[k]);
			(*word_count)++;
			k++;
		}
		ft_free_array(split_env);
	}
	return (k);
}

// Fonction pour traiter une variable
int	process_variable(t_params *params, t_shell_state *shell_state)
{
	int	count;

	count = 0;
	if (params->arg[*(params->j) + 1] == '?')
	{
		params->table[*(params->word_count)]
			= ft_itoa(shell_state->last_exit_status);
		(*(params->word_count))++;
		*(params->j) += 2;
		count++;
	}
	else
	{
		count += expand_env_variable(&params->arg[*(params->j) + 1],
				params->table, params->word_count);
		(*(params->j))++;
		while (params->arg[*(params->j)]
			&& !ft_isspace(params->arg[*(params->j)]))
			(*(params->j))++;
	}
	return (count);
}

// Fonction pour traiter une partie non variable
int	process_non_variable(t_params *params)
{
	int		start;
	char	*word;

	start = *(params->j);
	while (params->arg[*(params->j)] && params->arg[*(params->j)] != '$')
		(*(params->j))++;
	word = ft_substr(params->arg, start, *(params->j) - start);
	if (word)
	{
		params->table[*(params->word_count)] = word;
		(*(params->word_count))++;
		return (1);
	}
	return (0);
}
