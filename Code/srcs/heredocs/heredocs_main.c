/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:27:25 by fallan            #+#    #+#             */
/*   Updated: 2024/12/20 12:48:19 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Gère l'entrée d'un heredoc.
 *
 * Cette fonction :
 * - Initialise la structure de heredoc.
 * - Ouvre le prompt heredoc.
 * - Lit les lignes jusqu'au délimiteur.
 * - Stocke les lignes dans la liste de heredoc.
 *
 * @param redir_list La redirection heredoc à traiter.
 */
void	ft_handle_heredoc_input(t_redir *redir_list)
{
	t_heredoc	*heredoc_line;
	bool		delimiter_found;

	if (!redir_list || !(redir_list->str))
		return ;
	signal(SIGINT, handle_sigint_heredoc);
	heredoc_line = initialize_heredoc(redir_list);
	if (!heredoc_line)
	{
		signal(SIGINT, handle_sigint);
		return ;
	}
	g_signal = 0;
	while (!g_signal)
	{
		delimiter_found = read_and_process_line(&heredoc_line, redir_list);
		if (delimiter_found || g_signal)
			break ;
	}
	signal(SIGINT, handle_sigint);
}

/**
 * @brief Traite tous les heredocs dans la liste de commandes.
 *
 * Parcourt chaque commande et ses redirections pour gérer les heredocs.
 *
 * @param cmd_list La liste des commandes à traiter.
 */
void	ft_open_heredocs(t_command *cmd_list)
{
	t_redir		*redir_list;

	while (cmd_list)
	{
		redir_list = cmd_list->redir_list;
		while (redir_list)
		{
			if (redir_list->type == REDIR_HEREDOC
				&& redir_list->str_type == WORD)
				ft_handle_heredoc_input(redir_list);
			redir_list = redir_list->next;
		}
		cmd_list = cmd_list->next;
	}
}
