/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:27:25 by fallan            #+#    #+#             */
/*   Updated: 2025/01/04 10:49:27 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Process a single heredoc input
 *
 * Reads user input until delimiter is found or signal interrupts.
 * Handles signal interruption and sets appropriate flags.
 *
 * @param heredoc_line Double pointer to heredoc structure
 * @param redir_list Redirection list containing heredoc info
 * @param shell_state Current shell state
 * @return 0 on success, -1 on interrupt, 1 on other errors
 */
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

/**
 * @brief Handles heredoc input for a single redirection
 *
 * Sets up signal handling, initializes heredoc structure
 * and processes heredoc input until completion.
 *
 * @param redir_list Current redirection to process
 * @param shell_state Current shell state
 */
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
 * @brief Process all heredocs in the command list
 *
 * Iterates through each command and its redirections
 * to handle heredoc processing. Handles syntax errors
 * and sets execution flags accordingly.
 *
 * @param cmd_list List of commands to process
 * @param shell_state Current shell state
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
			else if (!redir_list->str)
			{
				ft_print_error(NULL, NULL, SYNTAX_ERR_NEW_LINE);
				cmd_list->skip_execution = 1;
			}
			redir_list = redir_list->next;
		}
		cmd_list = cmd_list->next;
	}
}
