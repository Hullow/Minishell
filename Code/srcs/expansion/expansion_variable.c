/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:41:17 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/10 18:05:59 by cmegret          ###   ########.fr       */
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
 * for each command, allocates memory for the table, fills
 * the table with expanded
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
			exit(EXIT_FAILURE);
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
 * values from the table, and updates the command name.
 * 
 * @param cmd_list The command list containing the arguments.
 * @param shell_state The current state of the shell.
 */
void	expand_command_variables(t_command *cmd_list,
	t_shell_state *shell_state)
{
	if (!cmd_list->args || !cmd_list->args[0])
		return ;
	fill_table(cmd_list, shell_state);
}
