/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:37:29 by francis           #+#    #+#             */
/*   Updated: 2024/12/10 15:42:46 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Checks if a filename is valid according to naming conventions.
 *
 * This function checks that the filename adheres to length and character constraints.
 * A valid filename must have a length between 1 and NAME_MAX, and must only contain
 * alphanumeric characters, dots (.), hyphens (-), and underscores (_). Additionally,
 * the filename must not start with a hyphen (-).
 *
 * @param filename The filename to check.
 * @return 1 if the filename is valid, 0 otherwise.
 */
int	is_valid_filename(const char *filename)
{
	size_t	len;
	size_t	i;

	if (filename[0] == '-')
		return (0);
	len = ft_strlen(filename);
	if (len == 0 || len > NAME_MAX)
	{
		printf("minishell: %s: File name too long\n", filename);
		return (0);
	}
	i = 0;
	while (i < len)
	{
		if (!ft_isalnum(filename[i]) && filename[i] != '.'
			&& filename[i] != '-' && filename[i] != '_')
		{
			printf("minishell: %s: Invalid file name\n", filename);
			return (0);
		}
		i++;
	}
	return (1);
}

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
		if (redir->str && !is_valid_filename(redir->str))
		{
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
