/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:01:29 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/18 12:59:46 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Checks if a command contains a heredoc.
 *
 * This function traverses the command's redirection list to determine
 * if any of them is a heredoc.
 *
 * @param cmd The command to check
 * @return true if a heredoc is found, false otherwise
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
 * @brief Finds the first heredoc redirection in a command.
 *
 * This function traverses the command's redirection list and returns
 * the first heredoc redirection found.
 *
 * @param cmd The command containing the redirections
 * @return Pointer to the found heredoc redirection, NULL if none found
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
 * @brief Calculates total size of heredoc content excluding delimiter
 *
 * This function traverses the heredoc line list and calculates
 * the total size needed to store all lines except the delimiter.
 *
 * @param heredoc The list of heredoc lines
 * @param delim The heredoc delimiter
 * @return Total size in bytes
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
 * @brief Prepares a buffer containing all heredoc lines except delimiter
 *
 * This function allocates a buffer and copies each heredoc line into it,
 * adding a newline after each command.
 *
 * @param heredoc The list of heredoc lines
 * @param delim The heredoc delimiter
 * @param size Total buffer size
 * @return Pointer to the prepared buffer, NULL if allocation fails
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
 * @brief Sets up standard input for a command from a heredoc
 *
 * This function:
 * 1. Finds the first heredoc redirection
 * 2. Creates a pipe
 * 3. Calculates total content size
 * 4. Prepares and writes buffer to pipe
 * 5. Sets up standard input from pipe
 *
 * @param cmd Command whose standard input needs to be redirected
 * @return 0 on success, -1 on error (redirection not found,
 *         pipe error, or allocation failure)
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
	if (redir->heredoc_interrupted)
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
