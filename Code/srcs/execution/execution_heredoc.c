/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:01:29 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/13 20:06:05 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Checks if a command has a heredoc redirection
 * @param cmd Command to check
 * @return true if command has heredoc, false otherwise
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
 * @brief Sets up heredoc input for a command
 * @param cmd Command with heredoc
 * @return 0 on success, -1 on error
 */
int	setup_heredoc_input(t_command *cmd)
{
	t_redir		*redir;
	int			pipe_fd[2];
	t_heredoc	*heredoc;
	size_t		total_len;
	char		*buffer;
	int			pos;

	redir = cmd->redir_list;
	while (redir && redir->type != REDIR_HEREDOC)
		redir = redir->next;
	if (!redir || pipe(pipe_fd) == -1)
		return (-1);

	// Calculer la taille totale
	total_len = 0;
	heredoc = redir->heredoc;
	while (heredoc)
	{
		total_len += ft_strlen(heredoc->line) + 1;
		heredoc = heredoc->next;
	}

	// Allouer un buffer pour le contenu du heredoc
	buffer = (char *)malloc(total_len + 1);
	if (!buffer)
		return (-1);

	// Copier le contenu du heredoc dans le buffer
	pos = 0;
	heredoc = redir->heredoc;
	while (heredoc)
	{
		ft_strlcpy(buffer + pos, heredoc->line, total_len - pos);
		pos += ft_strlen(heredoc->line);
		buffer[pos++] = '\n';
		heredoc = heredoc->next;
	}
	buffer[pos] = '\0';

	// Écrire et nettoyer
	write(pipe_fd[1], buffer, pos);
	free(buffer);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (0);
}
