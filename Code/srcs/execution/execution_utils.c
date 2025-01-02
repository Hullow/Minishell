/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:31:48 by cmegret           #+#    #+#             */
/*   Updated: 2025/01/02 16:43:52 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Handles heredoc input processing for a command
 *
 * This function checks if the command has heredoc redirections and sets up
 * the necessary input handling. The heredoc input is processed and stored
 * for later use by the command.
 *
 * @param cmd_list Pointer to the command structure containing
 * heredoc information
 *
 * @return int Status of heredoc handling:
 *         - 0: Success or no heredoc present
 *         - 1: Error during heredoc setup
 */
int	handle_heredoc(t_command *cmd_list)
{
	int	heredoc_status;

	if (!has_heredoc(cmd_list))
		return (0);
	heredoc_status = setup_heredoc_input(cmd_list);
	if (heredoc_status == -1)
		return (1);
	return (0);
}
