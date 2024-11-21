/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:00:25 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/21 14:51:29 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Execute the cd command.
 *
 * Changes the current directory based on the provided command arguments,
 * updates the environment variables, and handles errors appropriately.
 *
 * @param cmd The command structure containing the arguments.
 * @param shell_state The shell state structure.
 */
void	ft_cd(t_command *cmd, t_shell_state *shell_state)
{
	char	*path;
	char	*oldpwd;

	if (handle_cd_init(cmd, shell_state, &oldpwd))
		return ;
	path = get_target_path(cmd->args);
	if (!path)
	{
		fprintf(stderr, "cd: Target path not set\n");
		free(oldpwd);
		shell_state->last_exit_status = 1;
		return ;
	}
	if (change_directory(path))
	{
		free(oldpwd);
		shell_state->last_exit_status = 1;
		return ;
	}
	update_environment(shell_state, oldpwd);
	free(oldpwd);
	shell_state->last_exit_status = 0;
}
