/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_count_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:41:17 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/10 18:04:05 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Counts the number of words in an environment variable.
 * 
 * This function retrieves the value of the environment variable, splits it
 * into words, and counts the number of words.
 * 
 * @param var The environment variable name.
 * @param shell_state The current state of the shell.
 * @return int The number of words in the environment variable value.
 */
int	count_env_variable_words(char *var, t_shell_state *shell_state)
{
	char	*env_value;
	char	**split_env;
	int		count;
	int		k;

	count = 0;
	k = 0;
	env_value = get_env_var(shell_state->envp, var);
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

/**
 * @brief Counts the number of words in a variable.
 * 
 * This function checks if the variable is a special variable (e.g., $?),
 * or an environment variable, and counts the number of words accordingly.
 * 
 * @param arg The argument string containing the variable.
 * @param j A pointer to the current index in the argument string.
 * @param shell_state The current state of the shell.
 * @return int The number of words in the variable.
 */
int	count_variable_words(char *arg, int *j, t_shell_state *shell_state)
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
		word_count += count_env_variable_words(&arg[*j + 1], shell_state);
		(*j)++;
		while (arg[*j] && !ft_isspace(arg[*j]))
			(*j)++;
	}
	return (word_count);
}

/**
 * @brief Counts the number of non-variable words in an argument.
 * 
 * This function counts the number of words in the argument string that are
 * not variables.
 * 
 * @param arg The argument string.
 * @param j A pointer to the current index in the argument string.
 * @return int The number of non-variable words in the argument.
 */
int	count_non_variable_words(char *arg, int *j)
{
	int	word_count;

	word_count = 1;
	while (arg[*j] && arg[*j] != '$')
		(*j)++;
	return (word_count);
}

/**
 * @brief Counts the number of words in an argument.
 * 
 * This function iterates over the argument string and counts the number of
 * words, including both variables and non-variable words.
 * 
 * @param arg The argument string.
 * @param shell_state The current state of the shell.
 * @return int The number of words in the argument.
 */
int	count_words_in_arg(char *arg, t_shell_state *shell_state)
{
	int	j;
	int	word_count;

	j = 0;
	word_count = 0;
	while (arg[j])
	{
		if (arg[j] == '$')
			word_count += count_variable_words(arg, &j, shell_state);
		else
			word_count += count_non_variable_words(arg, &j);
	}
	return (word_count);
}

/**
 * @brief Counts the total number of words in the command list.
 * 
 * This function iterates over the command list and counts the total number
 * of words in all arguments.
 * 
 * @param cmd_list The command list containing the arguments.
 * @param shell_state The current state of the shell.
 * @return int The total number of words in the command list.
 */
int	count_total_words(t_command *cmd_list, t_shell_state *shell_state)
{
	int	word_count;
	int	i;

	word_count = 0;
	i = 0;
	while (cmd_list->args[i])
	{
		word_count += count_words_in_arg(cmd_list->args[i], shell_state);
		i++;
	}
	return (word_count);
}
