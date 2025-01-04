/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redir_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:37:29 by francis           #+#    #+#             */
/*   Updated: 2025/01/04 10:46:34 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Checks if a filename is valid according to naming conventions.
 *
 * This function checks that the filename adheres to length and character
 * constraints.
 * A valid filename must have a length between 1 and NAME_MAX, and must
 * only contain
 * alphanumeric characters, dots (.), hyphens (-), and underscores (_).
 * Additionally,
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
 * @brief Restores standard input/output file descriptors
 *
 * Restores the saved file descriptors for stdin and stdout
 * and closes the saved descriptors if they were above 2.
 * Resets the saved descriptors to -1.
 *
 * @param cmd_list Command structure containing saved file descriptors
 */
void	restore_redirections(t_command *cmd_list)
{
	if (cmd_list->saved_input > 2)
	{
		if (dup2(cmd_list->saved_input, STDIN_FILENO) != -1)
			close(cmd_list->saved_input);
	}
	if (cmd_list->saved_output > 2)
	{
		if (dup2(cmd_list->saved_output, STDOUT_FILENO) != -1)
			close(cmd_list->saved_output);
	}
	cmd_list->saved_input = -1;
	cmd_list->saved_output = -1;
}

/**
 * @brief Saves the current standard input/output file descriptors
 *
 * Duplicates stdin and stdout file descriptors and stores them
 * in the command structure for later restoration.
 *
 * @param cmd Command structure to store the saved descriptors
 * @return 0 on success, -1 on error
 */
int	save_standard_fds(t_command *cmd)
{
	cmd->saved_input = dup(STDIN_FILENO);
	if (cmd->saved_input == -1)
		return (-1);
	cmd->saved_output = dup(STDOUT_FILENO);
	if (cmd->saved_output == -1)
	{
		close(cmd->saved_input);
		return (-1);
	}
	return (0);
}

/**
 * @brief Processes a single redirection operation
 *
 * Validates and handles a single redirection based on its type:
 * - Output redirection (>)
 * - Append redirection (>>)
 * - Input redirection (<)
 *
 * @param redir Redirection structure to process
 * @param shell_state Current shell state
 * @return 0 on success, -1 on error
 */
int	process_single_redirection(t_redir *redir, t_shell_state *shell_state)
{
	if (validate_redirection(redir, shell_state) == -1)
		return (-1);
	if (redir->type == REDIR_OUTPUT
		&& handle_redir_output(redir, shell_state) == -1)
		return (-1);
	if (redir->type == REDIR_APPEND
		&& handle_redir_append(redir, shell_state) == -1)
		return (-1);
	if (redir->type == REDIR_INPUT
		&& handle_redir_input(redir, shell_state) == -1)
		return (-1);
	return (0);
}
