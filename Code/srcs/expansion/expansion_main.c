/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:41:47 by cmegret           #+#    #+#             */
/*   Updated: 2025/01/03 18:22:03 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Processes and expands variables in heredoc content
 *
 * Iterates through all heredoc redirections in a command.
 * For each heredoc marked for expansion, processes its content line by line
 * replacing variables with their values from the shell environment.
 *
 * @param cmd_list Command structure containing heredoc redirections
 * @param shell_state Current shell state with environment variables
 */
void	fill_table_heredocs(t_command *cmd_list, t_shell_state *shell_state)
{
	t_redir		*redir;
	t_heredoc	*current;
	char		*new_line;

	redir = cmd_list->redir_list;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			current = redir->heredoc;
			while (current && current->line)
			{
				if (current->next == NULL)
					break ;
				if (redir->expand_heredoc)
				{
					new_line = process_heredoc_line(current->line, shell_state);
					free(current->line);
					current->line = new_line;
				}
				current = current->next;
			}
		}
		redir = redir->next;
	}
}

void	process_command_redirections(t_command *cmd, t_shell_state *sh)
{
	t_redir	*redir;
	char	*new_arg;

	redir = cmd->redir_list;
	while (redir)
	{
		if (redir->type != REDIR_HEREDOC)
		{
			if (redir->str)
			{
				new_arg = process_single_arg(redir->str, redir->to_expand, sh);
				if (new_arg && ft_strlen(new_arg) == 0)
				{
					ft_print_error(redir->str, NULL, "ambiguous redirect");
					sh->last_exit_status = 1;
					free(new_arg);
					cmd->skip_execution = 1;
					return ;
				}
				free(redir->str);
				redir->str = new_arg;
			}
		}
		redir = redir->next;
	}
}

void	process_command_args(t_command *cmd, t_shell_state *shell_state)
{
	t_cmd_args	*current;
	char		*new_arg;
	int			i;

	current = cmd->arg_list;
	i = 0;
	while (current)
	{
		new_arg = process_single_arg(current->arg_string,
				current->to_expand, shell_state);
		free(current->arg_string);
		current->arg_string = new_arg;
		current = current->next;
		if (i == 0)
			cmd->cmd_name = ft_strdup(new_arg);
		i++;
	}
}

void	fill_table(t_command *cmd_list, t_shell_state *shell_state)
{
	t_command	*cmd;

	cmd = cmd_list;
	while (cmd)
	{
		process_command_args(cmd, shell_state);
		process_command_redirections(cmd, shell_state);
		cmd = cmd->next;
	}
}

/**
 * @brief Main function for variable expansion in commands
 *
 * Coordinates the expansion process for both heredocs and command arguments.
 * Steps:
 * 1. Validate input command list
 * 2. Process heredocs if present
 * 3. Expand variables in command arguments
 * 4. Convert argument lists to arrays
 *
 * @param cmd_list List of commands to process
 * @param shell_state Current shell state with environment variables
 */
void	expand_command_variables(t_command *cmd_list,
	t_shell_state *shell_state)
{
	if (!cmd_list)
		return ;
	if (cmd_list->redir_list && cmd_list->redir_list->heredoc)
		fill_table_heredocs(cmd_list, shell_state);
	fill_table(cmd_list, shell_state);
	ft_allocate_cmd_args_to_array(cmd_list);
}
