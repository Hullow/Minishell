/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:37:29 by francis           #+#    #+#             */
/*   Updated: 2024/12/24 13:34:01 by cmegret          ###   ########.fr       */
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
static int	handle_redir_output(t_redir *redir, t_shell_state *shell_state)
{
	int	fd;

	fd = open(redir->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
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
static int	handle_redir_append(t_redir *redir, t_shell_state *shell_state)
{
	int	fd;

	fd = open(redir->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
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
static int	handle_redir_input(t_redir *redir, t_shell_state *shell_state)
{
	int	fd;

	fd = open(redir->str, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
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
static int	validate_redirection(t_redir *redir, t_shell_state *shell_state)
{
	if (redir->str == NULL || redir->str[0] == '\0')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
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
		printf("minishell: syntax error near unexpected token`%s'\n",
			redir->str);
		shell_state->last_exit_status = 1;
		return (-1);
	}
	return (0);
}

/**
 * @brief Configures redirections for a command
 * 
 * This function:
 * 1. Saves original stdin and stdout file descriptors
 * 2. Processes each redirection in the command's redirection list
 * 3. Validates redirection syntax and filenames
 * 4. Sets up input/output according to redirection type
 * 5. Handles errors by setting appropriate exit status
 * 
 * @param cmd The command structure containing the redirections
 * @param shell_state The current state of the shell
 * @note Original file descriptors are saved for later restoration
 */
void	configure_redirections(t_command *cmd, t_shell_state *shell_state)
{
	t_redir	*redir;

	cmd->saved_input = dup(STDIN_FILENO);
	if (cmd->saved_input == -1)
		return ;
	cmd->saved_output = dup(STDOUT_FILENO);
	if (cmd->saved_output == -1)
	{
		close(cmd->saved_input);
		return ;
	}
	redir = cmd->redir_list;
	while (redir)
	{
		if (redir->type != REDIR_HEREDOC)
		{
			if (validate_redirection(redir, shell_state) == -1)
				return ;
			if (redir->type == REDIR_OUTPUT)
				if (handle_redir_output(redir, shell_state) == -1)
					return ;
			if (redir->type == REDIR_APPEND)
				if (handle_redir_append(redir, shell_state) == -1)
					return ;
			if (redir->type == REDIR_INPUT)
				if (handle_redir_input(redir, shell_state) == -1)
					return ;
		}
		redir = redir->next;
	}
}
