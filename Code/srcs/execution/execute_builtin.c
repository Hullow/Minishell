/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:23:09 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/01 18:35:36 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Executes the echo builtin command.
 *
 * This function checks if the given command is "echo". If it is, it executes
 * the echo command with the provided arguments and returns 0.
 * Otherwise, it returns 1.
 *
 * @param cmd A pointer to the command structure
 * containing the command to be checked.
 * @return 0 if the command is "echo" and was executed, 1 otherwise.
 */
int	ft_execute_echo(t_command *cmd)
{
	if (ft_strncmp(cmd->cmd_name, "echo", 4) == 0)
	{
		ft_echo(cmd->args);
		return (0);
	}
	return (1);
}

/**
 * @brief Executes the cd builtin command.
 *
 * This function checks if the given command is "cd". If it is, it executes
 * the cd command with the provided arguments and returns 0. Otherwise,
 * it returns 1.
 *
 * @param cmd A pointer to the command structure containing the command
 * to be checked.
 * @return 0 if the command is "cd" and was executed, 1 otherwise.
 */
int	ft_execute_cd(t_command *cmd)
{
	if (ft_strncmp(cmd->cmd_name, "cd", 2) == 0)
	{
		ft_cd(cmd);
		return (0);
	}
	return (1);
}

/**
 * @brief Executes the pwd builtin command.
 *
 * This function checks if the given command is "pwd". If it is, it executes
 * the pwd command and returns 0. Otherwise, it returns 1.
 *
 * @param cmd A pointer to the command structure containing the command
 * to be checked.
 * @return 0 if the command is "pwd" and was executed, 1 otherwise.
 */
int	ft_execute_pwd(t_command *cmd)
{
	if (ft_strncmp(cmd->cmd_name, "pwd", 3) == 0)
	{
		ft_pwd();
		return (0);
	}
	return (1);
}

/**
 * @brief Executes the export builtin command.
 *
 * This function checks if the given command is "export". If it is, it executes
 * the export command with the provided arguments and updates the shell state.
 * It returns 0 if the command was executed, otherwise it returns 1.
 *
 * @param cmd A pointer to the command structure containing the command
 * to be checked.
 * @param shell_state A pointer to the shell state structure.
 * @return 0 if the command is "export" and was executed, 1 otherwise.
 */
int	ft_execute_export(t_command *cmd, t_shell_state *shell_state)
{
	if (ft_strncmp(cmd->cmd_name, "export", 6) == 0)
	{
		ft_export(&shell_state->envp, cmd->args);
		return (0);
	}
	return (1);
}

/**
 * @brief Executes the unset builtin command.
 *
 * This function checks if the given command is "unset". If it is, it executes
 * the unset command with the provided arguments and updates the shell state.
 * It returns 0 if the command was executed, otherwise it returns 1.
 *
 * @param cmd A pointer to the command structure containing the command
 * to be checked.
 * @param shell_state A pointer to the shell state structure.
 * @return 0 if the command is "unset" and was executed, 1 otherwise.
 */
int	ft_execute_unset(t_command *cmd, t_shell_state *shell_state)
{
	if (ft_strncmp(cmd->cmd_name, "unset", 5) == 0)
	{
		ft_unset(&shell_state->envp, cmd->args);
		return (0);
	}
	return (1);
}

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
