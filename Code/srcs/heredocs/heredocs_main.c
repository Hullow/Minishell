/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:27:25 by fallan            #+#    #+#             */
/*   Updated: 2024/12/24 13:45:48 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

int	process_heredoc(t_heredoc **heredoc_line, t_redir *redir_list,
	t_shell_state *shell_state)
{
	int	delimiter_found;

	g_signal = SIGNAL_NONE;
	while (!g_signal)
	{
		delimiter_found
			= read_and_process_line(heredoc_line, redir_list, shell_state);
		if (delimiter_found || g_signal)
		{
			if (g_signal)
			{
				redir_list->heredoc_interrupted = true;
				return (-1);
			}
			return (0);
		}
	}
	return (1);
}

void	ft_handle_heredoc_input(t_redir *redir_list, t_shell_state *shell_state)
{
	t_heredoc	*heredoc_line;

	if (!redir_list || !(redir_list->str))
		return ;
	redir_list->heredoc_interrupted = false;
	signal(SIGINT, handle_sigint_heredoc);
	heredoc_line = initialize_heredoc(redir_list);
	if (!heredoc_line)
	{
		signal(SIGINT, handle_sigint);
		return ;
	}
	process_heredoc(&heredoc_line, redir_list, shell_state);
	signal(SIGINT, handle_sigint);
}

/**
 * @brief Traite tous les heredocs dans la liste de commandes.
 *
 * Parcourt chaque commande et ses redirections pour gérer les heredocs.
 *
 * @param cmd_list La liste des commandes à traiter.
 */
void	ft_open_heredocs(t_command *cmd_list, t_shell_state *shell_state)
{
	t_redir		*redir_list;

	while (cmd_list)
	{
		redir_list = cmd_list->redir_list;
		while (redir_list)
		{
			if (redir_list->type == REDIR_HEREDOC
				&& redir_list->str_type == WORD)
				ft_handle_heredoc_input(redir_list, shell_state);
			redir_list = redir_list->next;
		}
		cmd_list = cmd_list->next;
	}
}
