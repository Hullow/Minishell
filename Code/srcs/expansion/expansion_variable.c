/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:41:17 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/10 12:40:25 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Fills the table with expanded values from the command list.
 * 
 * This function iterates over the arguments in the command list, expanding
 * any variables found and adding the resulting words to the table.
 * 
 * @param table The table to fill with expanded values.
 * @param cmd_list The command list containing the arguments.
 * @param shell_state The current state of the shell.
 */
void	fill_table_values(char **table,
	t_command *cmd_list, t_shell_state *shell_state)
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
 * @brief Creates and fills a table with expanded values from the command list.
 * 
 * This function allocates memory for the table based on the total number of
 * words, then fills the table with expanded values.
 * 
 * @param cmd_list The command list containing the arguments.
 * @param shell_state The current state of the shell.
 * @return char** The filled table with expanded values.
 */
char	**fill_table(t_command *cmd_list, t_shell_state *shell_state)
{
	char	**table;
	int		word_count;

	word_count = count_total_words(cmd_list);
	table = malloc(sizeof(char *) * (word_count + 1));
	if (!table)
		return (NULL);
	fill_table_values(table, cmd_list, shell_state);
	return (table);
}

/**
 * @brief Expands the variables in the command list and updates the arguments.
 * 
 * This function replaces the arguments in the command list with the expanded
 * values from the table, and updates the command name.
 * 
 * @param cmd_list The command list containing the arguments.
 * @param shell_state The current state of the shell.
 */
void	expand_command_variables(t_command *cmd_list,
	t_shell_state *shell_state)
{
	char	**table;
	int		i;

	if (!cmd_list->args || !cmd_list->args[0])
		return ;
	table = fill_table(cmd_list, shell_state);
	if (table)
	{
		i = 0;
		while (table[i])
		{
			printf("table[%d]: %s\n", i, table[i]);
			i++;
		}
		ft_free_array(cmd_list->args);
		cmd_list->args = table;
		cmd_list->cmd_name = table[0];
		i = 0;
		while (cmd_list->args[i])
		{
			printf("cmd_list->args[%d]: %s\n", i, cmd_list->args[i]);
			i++;
		}
	}
}
