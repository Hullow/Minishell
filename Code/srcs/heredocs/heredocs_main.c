/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:27:25 by fallan            #+#    #+#             */
/*   Updated: 2024/12/13 21:51:04 by cmegret          ###   ########.fr       */
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

	if (!redir_list || !redir_list->str)
		return ;
	heredoc_line = initialize_heredoc(redir_list);
	if (!heredoc_line)
		return ;
	while (1)
	{
		delimiter_found = read_and_process_line(&heredoc_line, redir_list);
		if (delimiter_found)
			break ;
	}
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

/**
 * @brief Affiche le contenu de tous les heredocs dans la liste de commandes.
 *
 * Pour chaque heredoc, affiche son contenu.
 *
 * @param cmd_list La liste des commandes contenant les heredocs.
 */
void	ft_print_heredocs(t_command *cmd_list)
{
	t_redir		*redir_list;
	t_heredoc	*heredoc;

	if (!cmd_list)
		return ;
	while (cmd_list)
	{
		redir_list = cmd_list->redir_list;
		while (redir_list)
		{
			if (redir_list->type == REDIR_HEREDOC
				&& redir_list->str_type == WORD)
			{
				heredoc = redir_list->heredoc;
				if (!heredoc)
				{
					redir_list = redir_list->next;
					continue ;
				}
				printf("Contenu du heredoc pour %s:\n", redir_list->str);
				while (heredoc)
				{
					printf("{%s}\n", heredoc->line);
					heredoc = heredoc->next;
				}
			}
			redir_list = redir_list->next;
		}
		cmd_list = cmd_list->next;
	}
}
