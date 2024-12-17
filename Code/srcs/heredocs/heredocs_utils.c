/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:58:08 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/17 15:58:49 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Compare une ligne de heredoc avec le délimiteur.
 *
 * @param heredoc_line La ligne du heredoc à comparer.
 * @param delimiter Le délimiteur du heredoc.
 * @return true si les deux chaînes sont égales, false sinon.
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
 * @brief Initialise une nouvelle structure de heredoc.
 *
 * @return Un pointeur vers la nouvelle structure heredoc,
 * ou NULL en cas d'erreur.
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
 * @brief Initialise et assigne la structure heredoc à la redirection.
 *
 * @param redir_list La redirection heredoc à traiter.
 * @return t_heredoc* Un pointeur vers la structure heredoc
 * initialisée, ou NULL en cas d'erreur.
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
