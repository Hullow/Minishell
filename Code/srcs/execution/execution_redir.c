/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:37:29 by francis           #+#    #+#             */
/*   Updated: 2024/12/10 14:28:57 by francis          ###   ########.fr       */
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
* @param shell_state The shell state containing the last exit status.
*/
void	configure_redirections(t_command *cmd, t_shell_state *shell_state)
{
	t_redir	*redir;
	int		fd;

	cmd->saved_input = dup(STDIN_FILENO);
	cmd->saved_output = dup(STDOUT_FILENO);
	redir = cmd->redir_list;
	while (redir)
	{
		if (redir->str == NULL || redir->str[0] == '\0')
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			shell_state->last_exit_status = 1;
			return ;
		}
		if (redir->str && redir->str_type != WORD)
		{
			printf("minishell: syntax error near unexpected token `%s'\n", redir->str);
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
 * This function restores the original file descriptors for stdin and stdout
 * that were saved in the command structure.
 *
 * @param cmd_list The command list containing the saved file descriptors.
 */
void	restore_redirections(t_command *cmd_list)
{
    dup2(cmd_list->saved_input, STDIN_FILENO);
    dup2(cmd_list->saved_output, STDOUT_FILENO);
    close(cmd_list->saved_input);
    close(cmd_list->saved_output);
}
