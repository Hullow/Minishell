/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:41:45 by cmegret           #+#    #+#             */
/*   Updated: 2025/01/02 19:40:58 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Handles the expansion of a dollar sign variable in a string
 *
 * This function processes the expansion of environment variables
 * when encountering a '$' character.
 * It extracts the variable name and replaces it with its value.
 *
 * @param new_arg The current string being built
 * @param str The source string being processed
 * @param i Pointer to the current position in the source string
 * @param args Structure containing expansion context (to_expand and shell_state)
 *
 * @return char* The modified string with expanded variable, or NULL on error
 */
char	*handle_dollar_expansion(char *new_arg, const char *str,
	int *i, t_expansion_args *args)
{
	char	var_name[256];
	int		k;

	if (!args->to_expand->check)
		return (append_single_char(new_arg, str[*i]));
	k = 0;
	(*i)++;
	if (args->to_expand->size_to_expand >= 1 && str[*i])
	{
		while (k < args->to_expand->size_to_expand - 1 && str[*i])
			var_name[k++] = str[(*i)++];
		var_name[k] = '\0';
		new_arg = expand_variable(new_arg, args->shell_state, var_name);
		(*i)--;
	}
	else if (str[*i - 1])
		new_arg = append_single_char(new_arg, '$');
	else
		(*i)--;
	return (new_arg);
}

/**
 * @brief Processes a single argument string for variable expansion
 *
 * This function handles the complete processing of a string, expanding all
 * environment variables marked with '$'. It creates a new string with all
 * expansions applied.
 *
 * @param str The input string to process
 * @param to_expand Linked list of expansion markers
 * @param shell_state Current shell state containing environment variables
 *
 * @return char* New string with all expansions applied, or NULL on error
 */
char	*process_single_arg(char *str, t_expand *to_expand,
	t_shell_state *shell_state)
{
	t_expansion_args	args;
	char				*new_arg;
	int					i;

	args.to_expand = to_expand;
	args.shell_state = shell_state;
	new_arg = ft_strdup("");
	if (!new_arg)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && args.to_expand)
		{
			new_arg = handle_dollar_expansion(new_arg, str, &i, &args);
			args.to_expand = args.to_expand->next;
		}
		else
			new_arg = append_single_char(new_arg, str[i]);
		i++;
	}
	return (new_arg);
}

/**
 * @brief Processes a heredoc line for variable expansion
 *
 * Scans the input line for variables (starting with $) and expands them
 * using values from the shell state. Non-variable content is copied
 * directly to the output.
 *
 * @param line Input line from heredoc
 * @param shell_state Current shell state with environment variables
 * @return New string with all variables expanded
 */
char	*process_heredoc_line(char *line, t_shell_state *shell_state)
{
	char	*new_line;
	char	var_name[256];
	char	tmp[2];
	int		j;

	new_line = ft_strdup("");
	j = 0;
	while (line[j])
	{
		if (line[j] == '$')
		{
			extract_var_name(line, &j, var_name);
			new_line = expand_variable(new_line, shell_state, var_name);
		}
		else
		{
			tmp[0] = line[j];
			tmp[1] = '\0';
			new_line = ft_strjoin_free(new_line, tmp);
		}
		j++;
	}
	return (new_line);
}
