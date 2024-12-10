/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:41:17 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/10 12:42:01 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Expands an environment variable and fills the table with its words.
 * 
 * This function retrieves the value of the environment variable, splits it
 * into words, and adds each word to the table.
 * 
 * @param var The environment variable name.
 * @param table The table to fill with the words.
 * @param word_count A pointer to the current word count in the table.
 * @return int The number of words added to the table.
 */
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

/**
 * @brief Processes a variable in the argument string.
 * 
 * This function checks if the variable is a special variable (e.g., $?),
 * or an environment variable, and processes it accordingly, adding the
 * resulting words to the table.
 * 
 * @param params A pointer to the structure containing the parameters.
 * @param shell_state The current state of the shell.
 * @return int The number of words added to the table.
 */
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

/**
 * @brief Processes a non-variable part of the argument string.
 * 
 * This function extracts a word from the argument string that is not a
 * variable and adds it to the table.
 * 
 * @param params A pointer to the structure containing the parameters.
 * @return int 1 if a word was added to the table, 0 otherwise.
 */
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
