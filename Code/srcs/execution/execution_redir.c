/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:39:48 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/03 10:06:14 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Configures the redirections for a command and saves
 * the original file descriptors.
 *
 * This function sets up the file descriptors for input and output redirections
 * based on the redirection list of the command and saves
 * the original file descriptors.
 *
 * @param cmd The command containing the redirection list.
 * @param saved_stdin Pointer to save the original stdin file descriptor.
 * @param saved_stdout Pointer to save the original stdout file descriptor.
 */
void	configure_redirections(t_command *cmd, int *saved_stdin,
	int *saved_stdout, t_shell_state *shell_state)
{
	t_redir	*redir;
	int		fd;

	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);

	redir = cmd->redir_list;
	while (redir)
	{
		if (redir->str == NULL || redir->str[0] == '\0')
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			shell_state->last_exit_status = 1;
			return ;
		}
		if (redir->type == REDIR_OUTPUT)
		{
			fd = open(redir->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("open");
				shell_state->last_exit_status = 1;
				return ;
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_APPEND)
		{
			fd = open(redir->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror("open");
				shell_state->last_exit_status = 1;
				return ;
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_INPUT)
		{
			fd = open(redir->str, O_RDONLY);
			if (fd == -1)
			{
				perror("open");
				shell_state->last_exit_status = 1;
				return ;
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
}

/**
 * @brief Restores the original file descriptors.
 *
 * This function restores the original file descriptors for stdin and stdout.
 *
 * @param saved_stdin The original stdin file descriptor.
 * @param saved_stdout The original stdout file descriptor.
 */
void	restore_redirections(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
