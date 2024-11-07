/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:57:58 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/07 13:58:33 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Executes the env builtin command.
 *
 * This function checks if the given command is "env". If it is, it executes
 * the env command and returns 0. Otherwise, it returns 1.
 *
 * @param cmd A pointer to the command structure containing the command
 * to be checked.
 * @param shell_state A pointer to the shell state structure.
 * @return 0 if the command is "env" and was executed, 1 otherwise.
 */
int	ft_execute_env(t_command *cmd, t_shell_state *shell_state)
{
	if (ft_strncmp(cmd->cmd_name, "env", 3) == 0)
	{
		ft_env(shell_state->envp);
		return (0);
	}
	return (1);
}

/**
 * @brief Executes the exit builtin command.
 *
 * This function checks if the given command is "exit". If it is, it executes
 * the exit command and updates the shell state. It returns 0 if the command
 * was executed, otherwise it returns 1.
 *
 * @param cmd A pointer to the command structure containing the command
 * to be checked.
 * @param shell_state A pointer to the shell state structure.
 * @return 0 if the command is "exit" and was executed, 1 otherwise.
 */
int	ft_execute_exit(t_command *cmd, t_shell_state *shell_state)
{
	if (ft_strncmp(cmd->cmd_name, "exit", 4) == 0)
	{
		ft_exit(&shell_state->envp, shell_state);
		return (0);
	}
	return (1);
}
