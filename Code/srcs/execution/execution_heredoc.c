/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:01:29 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/13 21:03:11 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Vérifie si une commande contient un heredoc.
 *
 * Cette fonction parcourt la liste des redirections d'une commande pour
 * déterminer si l'une d'elles est un heredoc.
 *
 * @param cmd La commande à vérifier.
 * @return true si un heredoc est trouvé, false sinon.
 */
bool	has_heredoc(t_command *cmd)
{
	t_redir	*redir;

	if (!cmd || !cmd->redir_list)
		return (false);
	redir = cmd->redir_list;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
			return (true);
		redir = redir->next;
	}
	return (false);
}

/**
 * @brief Trouve la première redirection de type heredoc dans une commande.
 *
 * Cette fonction parcourt la liste des redirections d'une commande et retourne
 * la première redirection qui est un heredoc.
 *
 * @param cmd La commande contenant les redirections.
 * @return Un pointeur vers la redirection heredoc trouvée,
 * ou NULL si aucune n'est trouvée.
 */
t_redir	*find_heredoc(t_command *cmd)
{
	t_redir	*redir;

	redir = cmd->redir_list;
	while (redir && redir->type != REDIR_HEREDOC)
		redir = redir->next;
	return (redir);
}

/**
 * @brief Calcule la taille totale des contenus d'un heredoc
 * en excluant le délimiteur.
 *
 * Cette fonction parcourt la liste des lignes d'un heredoc et calcule la
 * taille totale nécessaire pour stocker toutes les lignes sauf le délimiteur.
 *
 * @param heredoc La liste des lignes du heredoc.
 * @param delim Le délimiteur du heredoc.
 * @return La taille totale en octets.
 */
size_t	calculate_heredoc_size(t_heredoc *heredoc, char *delim)
{
	size_t	total_len;

	total_len = 0;
	while (heredoc && heredoc->line)
	{
		if (ft_strcmp(heredoc->line, delim) != 0)
			total_len += ft_strlen(heredoc->line) + 1;
		heredoc = heredoc->next;
	}
	return (total_len);
}

/**
 * @brief Prépare un buffer contenant toutes les lignes
 * du heredoc sauf le délimiteur.
 *
 * Cette fonction alloue un buffer et copie chaque
 * ligne du heredoc dans ce buffer,
 * en ajoutant une nouvelle ligne après chaque commande.
 *
 * @param heredoc La liste des lignes du heredoc.
 * @param delim Le délimiteur du heredoc.
 * @param size La taille totale du buffer.
 * @return Un pointeur vers le buffer préparé,
 * ou NULL en cas d'erreur d'allocation.
 */
char	*prepare_heredoc_buffer(t_heredoc *heredoc, char *delim, size_t size)
{
	char	*buffer;
	int		pos;

	buffer = (char *)malloc(size + 1);
	if (!buffer)
		return (NULL);
	pos = 0;
	while (heredoc && heredoc->line)
	{
		if (ft_strcmp(heredoc->line, delim) != 0)
		{
			ft_strlcpy(buffer + pos, heredoc->line, size - pos + 1);
			pos += ft_strlen(heredoc->line);
			buffer[pos++] = '\n';
		}
		heredoc = heredoc->next;
	}
	buffer[size] = '\0';
	return (buffer);
}

/**
 * @brief Configure l'entrée standard d'une commande à partir d'un heredoc.
 *
 * Cette fonction crée un pipe, prépare le buffer contenant
 * les lignes du heredoc,
 * écrit ce buffer dans le pipe, et redirige l'entrée standard
 * de la commande vers le pipe.
 *
 * @param cmd La commande dont l'entrée standard doit être redirigée.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int	setup_heredoc_input(t_command *cmd)
{
	t_redir		*redir;
	int			pipe_fd[2];
	char		*buffer;
	size_t		total_len;

	redir = find_heredoc(cmd);
	if (!redir || !redir->heredoc || pipe(pipe_fd) == -1)
		return (-1);
	total_len = calculate_heredoc_size(redir->heredoc, redir->str);
	buffer = prepare_heredoc_buffer(redir->heredoc, redir->str, total_len);
	if (!buffer)
		return (-1);
	write(pipe_fd[1], buffer, total_len);
	free(buffer);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (0);
}
