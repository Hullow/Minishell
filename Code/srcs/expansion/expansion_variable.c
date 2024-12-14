/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:41:17 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/14 20:55:32 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Checks if the provided token is an environment variable.
 *
 * Determines if the first character of the token is a '$', indicating
 * it's an environment variable.
 *
 * @param token The token to check.
 * @return true if the token is an environment variable, false otherwise.
 */
bool	is_env_variable(const char *token)
{
	if (!token)
		return (false);
	return (token[0] == '$');
}

/**
 * @brief Retrieves the value of an environment variable from the environment.
 *
 * This function searches for the environment variable key in the envp array
 * and returns its corresponding value. If the variable is not found, it returns
 * an empty string.
 *
 * @param token The token representing the environment variable (e.g., "$PATH").
 * @param envp The array of environment variables.
 * @return A newly allocated string containing
 * the value of the environment variable,
 *         or an empty string if not found.
 */
char	*get_env_value(const char *token, char **envp)
{
	char	*env_key;
	char	*env_value;
	size_t	key_len;
	int		i;

	if (!token || token[0] != '$')
		return (ft_strdup(""));
	env_key = (char *)token + 1;
	key_len = ft_strlen(env_key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], env_key, key_len) == 0
			&& envp[i][key_len] == '=')
		{
			env_value = ft_strdup(envp[i] + key_len + 1);
			return (env_value);
		}
		i++;
	}
	return (ft_strdup(""));
}

/**
 * @brief Calculates the total length required to join subtokens with spaces.
 *
 * This function sums the lengths of all subtokens and adds space for separators
 * between them.
 *
 * @param subtokens The array of subtokens to be joined.
 * @return The total length required for the joined string.
 */
size_t	calculate_total_length(char **subtokens)
{
	size_t	i;
	size_t	total_length;

	if (!subtokens)
		return (0);
	total_length = 0;
	i = 0;
	while (subtokens[i])
		total_length += ft_strlen(subtokens[i++]);
	return (total_length);
}

/**
 * @brief Joins an array of subtokens into a single string separated by spaces.
 *
 * Allocates memory for the joined string and
 * concatenates each subtoken with a space.
 *
 * @param subtokens The array of substrings to join.
 * @param total_length The total length of the resulting string.
 * @return A newly allocated string containing all subtokens joined by spaces,
 *         or NULL if memory allocation fails.
 */
char	*perform_join(char **subtokens, size_t total_length)
{
	size_t	i;
	char	*joined;
	char	*temp;

	joined = malloc(total_length + 1);
	if (!joined)
		return (NULL);
	joined[0] = '\0';
	i = 0;
	while (subtokens[i])
	{
		temp = ft_strjoin(joined, subtokens[i]);
		free(joined);
		joined = temp;
		i++;
	}
	return (joined);
}

/**
 * @brief Joins subtokens into a single argument string.
 *
 * Calculates the necessary length and performs the join operation.
 *
 * @param subtokens The array of substrings to join.
 * @return A newly allocated string with all subtokens joined by spaces.
 */
char	*join_subtokens(char **subtokens)
{
	size_t	total_length;
	char	*joined;

	total_length = calculate_total_length(subtokens);
	joined = perform_join(subtokens, total_length);
	return (joined);
}

char	**split_with_quotes(const char *str)
{
	char	**result;
	char	*temp;
	int		i;
	int		j;
	int		count;

	count = 0;
	temp = malloc(ft_strlen(str) + 1);
	result = malloc(sizeof(char *) * ((ft_strlen(str) * 2) + 1));
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			temp[0] = str[i];
			temp[1] = '\0';
			result[count++] = ft_strdup(temp);
			i++;
		}
		else if (str[i] == ' ')
		{
			temp[0] = str[i];
			temp[1] = '\0';
			result[count++] = ft_strdup(temp);
			i++;
		}
		else
		{
			j = 0;
			while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
				temp[j++] = str[i++];
			temp[j] = '\0';
			if (j > 0)
				result[count++] = ft_strdup(temp);
		}
	}
	result[count] = NULL;
	free(temp);
	return (result);
}

void	process_argument(t_cmd_args *current_arg, t_shell_state *shell_state)
{
	char	**subtokens;
	int		i;
	char	*env_value;

	subtokens = split_with_quotes(current_arg->arg_string);
	i = 0;
	while (subtokens[i])
	{
		if (is_env_variable(subtokens[i]))
		{
			env_value = get_env_value(subtokens[i], shell_state->envp);
			free(subtokens[i]);
			subtokens[i] = strdup(env_value);
			free(env_value);
		}
		i++;
	}
	free(current_arg->arg_string);
	current_arg->arg_string = join_subtokens(subtokens);
	ft_free_array(subtokens);
}

/**
 * @brief Fills heredoc tables with expanded variables from the command list.
 *
 * Iterates through each command and its arguments to process heredoc entries.
 *
 * @param cmd_list The list of commands to process.
 * @param shell_state The current state of the shell.
 */
void	fill_table_heredocs(t_command *cmd_list, t_shell_state *shell_state)
{
	t_command	*current_cmd;
	t_cmd_args	*current_arg;

	while (cmd_list)
	{
		current_cmd = cmd_list;
		current_arg = current_cmd->arg_list;
		while (current_arg)
		{
			process_argument(current_arg, shell_state);
			current_arg = current_arg->next;
		}
		cmd_list = cmd_list->next;
	}
}

/**
 * @brief Fills the table with expanded values from the command list.
 *
 * Iterates over each word in the command arguments, expanding variables
 * and adding the resulting words to the table.
 *
 * @param table The table to fill with expanded values.
 * @param cmd_list The command list containing the arguments.
 * @param shell_state The current state of the shell.
 */
void	fill_table_values(char **table, t_command *cmd_list,
	t_shell_state *shell_state)
{
	int			i;
	int			j;
	int			word_count;
	t_params	params;

	i = 0;
	word_count = 0;
	while (cmd_list->args[i])
	{
		j = 0;
		while (cmd_list->args[i][j])
		{
			params.arg = cmd_list->args[i];
			params.j = &j;
			params.table = table;
			params.word_count = &word_count;
			if (cmd_list->args[i][j] == '$')
				process_variable(&params, shell_state);
			else
				process_non_variable(&params);
		}
		i++;
	}
	table[word_count] = NULL;
}

/**
 * @brief Fills the command table with expanded values.
 *
 * This function iterates over the command list, counts the total number of words
 * for each command, allocates memory for the table,
 * fills the table with expanded
 * values, and updates the command arguments and command name.
 *
 * @param cmd_list The list of commands to process.
 * @param shell_state The current state of the shell.
 */
void	fill_table(t_command *cmd_list, t_shell_state *shell_state)
{
	t_command	*current_cmd;
	char		**table;
	int			word_count;

	current_cmd = cmd_list;
	while (current_cmd)
	{
		word_count = count_total_words(current_cmd, shell_state);
		table = malloc(sizeof(char *) * (word_count + 1));
		if (!table)
		{
			printf("Error: Memory allocation failed in fill_table\n");
			shell_state->last_exit_status = EXIT_FAILURE;
			exit(shell_state->last_exit_status);
		}
		fill_table_values(table, current_cmd, shell_state);
		ft_free_array(current_cmd->args);
		current_cmd->args = table;
		current_cmd->cmd_name = table[0];
		expand_redir_variables(current_cmd->redir_list, shell_state);
		current_cmd = current_cmd->next;
	}
}

/**
 * @brief Expands the variables in the command list and updates the arguments.
 *
 * This function replaces the arguments in the command list with the expanded
 * values from the table and updates the command name.
 * It also handles heredoc expansions.
 *
 * @param cmd_list The command list containing the arguments.
 * @param shell_state The current state of the shell.
 */
void	expand_command_variables(t_command *cmd_list,
	t_shell_state *shell_state)
{
	if (!cmd_list)
		return ;
	if (!cmd_list->args || !cmd_list->args[0])
		return ;
	if (cmd_list->redir_list && cmd_list->redir_list->heredoc)
		fill_table_heredocs(cmd_list, shell_state);
	else
		fill_table(cmd_list, shell_state);
}
