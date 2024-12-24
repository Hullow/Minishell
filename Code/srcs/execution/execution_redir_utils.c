/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redir_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:37:29 by francis           #+#    #+#             */
/*   Updated: 2024/12/24 13:35:16 by cmegret          ###   ########.fr       */
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
