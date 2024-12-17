/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:41:47 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/17 12:49:23 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

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

void	fill_table(t_command *cmd_list, t_shell_state *shell_state)
{
	char		*new_arg;
	t_cmd_args	*current;
	t_command	*cmd;

	cmd = cmd_list;
	while (cmd)
	{
		current = cmd->arg_list;
		while (current)
		{
			new_arg = process_single_arg(current, shell_state);
			free(current->arg_string);
			current->arg_string = new_arg;
			current = current->next;
		}
		cmd = cmd->next;
	}
}

void	expand_command_variables(t_command *cmd_list,
	t_shell_state *shell_state)
{
	if (!cmd_list)
		return ;
	if (!cmd_list->arg_list || !cmd_list->arg_list->arg_string)
		return ;
	if (cmd_list->redir_list && cmd_list->redir_list->heredoc)
		fill_table_heredocs(cmd_list, shell_state);
	fill_table(cmd_list, shell_state);
	ft_allocate_cmd_args_to_array(cmd_list);
}
