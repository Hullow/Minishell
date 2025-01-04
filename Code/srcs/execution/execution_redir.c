/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:37:29 by francis           #+#    #+#             */
/*   Updated: 2025/01/04 10:47:02 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Handles output redirection.
 * 
 * This function opens the file specified in the redirection structure
 * for writing, truncating it if it already exists. It then duplicates
 * the file descriptor to STDOUT_FILENO.
 * 
 * @param redir The redirection structure containing the file information.
 * @param shell_state The current state of the shell.
 * @return 0 on success, -1 on failure.
 */
int	handle_redir_output(t_redir *redir, t_shell_state *shell_state)
{
	int	fd;

	fd = open(redir->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_print_error(redir->str, NULL, "No such file or directory");
		shell_state->last_exit_status = 1;
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

/**
 * @brief Handles append redirection.
 * 
 * This function opens the file specified in the redirection structure
 * for writing, appending to it if it already exists. It then duplicates
 * the file descriptor to STDOUT_FILENO.
 * 
 * @param redir The redirection structure containing the file information.
 * @param shell_state The current state of the shell.
 * @return 0 on success, -1 on failure.
 */
int	handle_redir_append(t_redir *redir, t_shell_state *shell_state)
{
	int	fd;

	fd = open(redir->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_print_error(redir->str, NULL, "No such file or directory");
		shell_state->last_exit_status = 1;
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

/**
 * @brief Handles input redirection.
 * 
 * This function opens the file specified in the redirection structure
 * for reading. It then duplicates the file descriptor to STDIN_FILENO.
 * 
 * @param redir The redirection structure containing the file information.
 * @param shell_state The current state of the shell.
 * @return 0 on success, -1 on failure.
 */
int	handle_redir_input(t_redir *redir, t_shell_state *shell_state)
{
	int	fd;

	fd = open(redir->str, O_RDONLY);
	if (fd == -1)
	{
		ft_print_error(redir->str, NULL, "No such file or directory");
		shell_state->last_exit_status = 1;
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

/**
 * @brief Validates a redirection.
 * 
 * This function checks if the redirection string is valid and if the
 * redirection type is correct.
 * 
 * @param redir The redirection structure to validate.
 * @param shell_state The current state of the shell.
 * @return 0 if valid, -1 if invalid.
 */
int	validate_redirection(t_redir *redir, t_shell_state *shell_state)
{
	if (redir->str == NULL || redir->str[0] == '\0')
	{
		ft_print_error(NULL, NULL, SYNTAX_ERR_NEW_LINE);
		shell_state->last_exit_status = 1;
		return (-1);
	}
	if (redir->str && !is_valid_filename(redir->str))
	{
		shell_state->last_exit_status = 1;
		return (-1);
	}
	if (redir->str && redir->str_type != WORD)
	{
		ft_print_error(NULL, redir->str, "syntax error near unexpected token");
		shell_state->last_exit_status = 1;
		return (-1);
	}
	return (0);
}

/**
 * @brief Configures redirections for a command
 *
 * Processes all redirections in the command's redirection list:
 * - Saves current standard file descriptors
 * - Processes each redirection except heredocs
 * - Handles redirection errors
 *
 * @param cmd Command structure containing redirection list
 * @param shell_state Current shell state for error handling
 */
void	configure_redirections(t_command *cmd, t_shell_state *shell_state)
{
	t_redir	*redir;

	if (save_standard_fds(cmd) == -1)
		return ;
	redir = cmd->redir_list;
	while (redir)
	{
		if (redir->type != REDIR_HEREDOC)
			if (process_single_redirection(redir, shell_state) == -1)
				return ;
		redir = redir->next;
	}
}
