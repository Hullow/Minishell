/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_heredocs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:43:04 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/16 16:10:54 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"
/* 
void	fill_table_heredocs(t_command *cmd_list,
	t_shell_state *shell_state)
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
					new_line = process_single_arg(current->line, shell_state);
					free(current->line);
					current->line = new_line;
				}
				current = current->next;
			}
		}
		redir = redir->next;
	}
}
 */