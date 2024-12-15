/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_heredocs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:43:04 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/15 15:04:18 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

void	fill_table_heredocs(t_command *cmd_list, t_shell_state *shell_state)
{
	t_heredoc	*current;
	t_heredoc	*next;
	char		*new_line;

	current = cmd_list->redir_list->heredoc;
	while (current && current->line)
	{
		next = current->next;
		if (next && next->line)
		{
			new_line = process_single_arg(current->line, shell_state);
			free(current->line);
			current->line = new_line;
		}
		current = next;
	}
}
