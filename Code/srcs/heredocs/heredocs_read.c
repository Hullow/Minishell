/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:59:00 by cmegret           #+#    #+#             */
/*   Updated: 2025/01/04 10:50:03 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Allocates a new heredoc line and adds it to the list
 *
 * @param heredoc_line Current heredoc line
 * @return Pointer to the new heredoc line, NULL if error
 */
t_heredoc	*ft_malloc_new_heredoc_line(t_heredoc *heredoc_line)
{
	heredoc_line->next = malloc(sizeof(t_heredoc));
	if (!heredoc_line->next)
		return (NULL);
	heredoc_line = heredoc_line->next;
	heredoc_line->line = NULL;
	heredoc_line->next = NULL;
	return (heredoc_line);
}

/**
 * @brief Reads and processes a heredoc line
 *
 * @param heredoc_line Pointer to current heredoc line
 * @param redir_list Heredoc redirection to process
 * @param shell_state Current shell state
 * @return true if delimiter found, false otherwise
 */
bool	read_and_process_line(t_heredoc **heredoc_line, t_redir *redir_list,
			t_shell_state *shell_state)
{
	char	*prompt;

	prompt = ft_prompt(REDIR_HEREDOC);
	if (g_signal)
		shell_state->last_exit_status = g_signal;
	if (!prompt)
		return (true);
	if (*prompt)
	{
		(*heredoc_line)->line = ft_strdup(prompt);
		if (ft_match_heredoc_delimiter((*heredoc_line)->line, redir_list->str))
		{
			free(prompt);
			return (true);
		}
		*heredoc_line = ft_malloc_new_heredoc_line(*heredoc_line);
		if (!(*heredoc_line))
		{
			free(prompt);
			return (true);
		}
	}
	free(prompt);
	return (false);
}
