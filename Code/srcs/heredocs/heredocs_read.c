/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:59:00 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/17 15:59:27 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Alloue une nouvelle ligne de heredoc et l'ajoute à la liste.
 *
 * @param heredoc_line La ligne actuelle du heredoc.
 * @return Un pointeur vers la nouvelle ligne de heredoc,
 * ou NULL en cas d'erreur.
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
 * @brief Lit une ligne de heredoc et la traite.
 *
 * @param heredoc_line Le pointeur vers la ligne actuelle de heredoc.
 * @param redir_list La redirection heredoc à traiter.
 * @return true si le délimiteur a été trouvé, false sinon.
 */
bool	read_and_process_line(t_heredoc **heredoc_line, t_redir *redir_list)
{
	char	*prompt;

	prompt = ft_prompt(REDIR_HEREDOC);
	if (!prompt)
	{
		printf("\n");
		return (true);
	}
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
