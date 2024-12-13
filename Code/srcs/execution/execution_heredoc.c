/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:01:29 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/13 19:02:01 by cmegret          ###   ########.fr       */
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
	t_redir	*redir;
	int		pipe_fd[2];
	t_token	*content;

	redir = cmd->redir_list;
	while (redir && redir->type != REDIR_HEREDOC)
		redir = redir->next;
	if (!redir || pipe(pipe_fd) == -1)
		return (-1);
	content = redir->heredoc->contents;
	while (content)
	{
		write(pipe_fd[1], content->str, ft_strlen(content->str));
		write(pipe_fd[1], "\n", 1);
		content = content->next;
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (0);
}
