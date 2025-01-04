/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:58:08 by cmegret           #+#    #+#             */
/*   Updated: 2025/01/04 10:50:33 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Compares a heredoc line with its delimiter
 *
 * @param heredoc_line The heredoc line to compare
 * @param delimiter The heredoc delimiter
 * @return true if strings match, false otherwise
 */
bool	ft_match_heredoc_delimiter(char *heredoc_line, char *delimiter)
{
	size_t	len;

	if (!heredoc_line || !delimiter)
		return (false);
	len = ft_strlen(heredoc_line);
	if (!ft_strncmp(heredoc_line, delimiter, len))
		return (true);
	return (false);
}

/**
 * @brief Initializes a new heredoc structure
 *
 * @return Pointer to the new heredoc structure,
 * NULL if allocation fails
 */
t_heredoc	*ft_init_heredoc(void)
{
	t_heredoc	*heredoc_line;

	heredoc_line = malloc(sizeof(t_heredoc));
	if (!heredoc_line)
		return (NULL);
	heredoc_line->line = NULL;
	heredoc_line->next = NULL;
	return (heredoc_line);
}

/**
 * @brief Initializes and assigns heredoc structure to redirection
 *
 * @param redir_list The heredoc redirection to process
 * @return t_heredoc* Pointer to initialized heredoc structure,
 * NULL if initialization fails
 */
t_heredoc	*initialize_heredoc(t_redir *redir_list)
{
	t_heredoc	*heredoc_line;

	heredoc_line = ft_init_heredoc();
	if (!heredoc_line)
		return (NULL);
	redir_list->heredoc = heredoc_line;
	return (heredoc_line);
}
