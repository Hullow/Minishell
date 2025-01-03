/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:36:57 by francis           #+#    #+#             */
/*   Updated: 2025/01/03 21:51:32 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Checks if a command is a builtin command.
 *
 * This function checks if the given command name
 * matches any of the builtin commands.
 *
 * @param cmd_name The name of the command to check.
 * @return 0 if the command is a builtin, 1 otherwise.
 */
int	ft_is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (1);
	if (ft_strncmp(cmd_name, "echo", 5) == 0)
		return (0);
	else if (ft_strncmp(cmd_name, "unset", 6) == 0)
		return (0);
	else if (ft_strncmp(cmd_name, "export", 7) == 0)
		return (0);
	else if (ft_strncmp(cmd_name, "pwd", 4) == 0)
		return (0);
	else if (ft_strncmp(cmd_name, "cd", 3) == 0)
		return (0);
	else if (ft_strncmp(cmd_name, "exit", 5) == 0)
		return (0);
	else if (ft_strncmp(cmd_name, "env", 4) == 0)
		return (0);
	return (1);
}

/**
 * @brief Executes a builtin command
 *
 * This function executes one of the following builtin commands:
 * - echo: Display text with optional -n flag
 * - unset: Remove environment variables
 * - export: Set or modify environment variables
 * - pwd: Print working directory
 * - cd: Change directory
 * - exit: Exit the shell
 * - env: Display environment variables
 *
 * @param cmd The command structure containing name and arguments
 * @param shell_state The current state of the shell
 */
void	ft_execute_builtin(t_command *cmd, t_shell_state *shell_state)
{
	if (ft_strncmp(cmd->cmd_name, "echo", 5) == 0)
		ft_echo(cmd->args, shell_state);
	else if (ft_strncmp(cmd->cmd_name, "unset", 6) == 0)
		ft_unset(shell_state, cmd->args);
	else if (ft_strncmp(cmd->cmd_name, "export", 7) == 0)
		ft_export(shell_state, cmd->args);
	else if (ft_strncmp(cmd->cmd_name, "pwd", 4) == 0)
		ft_pwd(shell_state);
	else if (ft_strncmp(cmd->cmd_name, "cd", 3) == 0)
		ft_cd(cmd, shell_state);
	else if (ft_strncmp(cmd->cmd_name, "exit", 5) == 0)
		ft_exit(shell_state, cmd->args, shell_state->last_exit_status, 0);
	else if (ft_strncmp(cmd->cmd_name, "env", 4) == 0)
		ft_env(shell_state);
}

/**
 * @brief Handles the execution of a builtin command in the parent process.
 *
 * This function checks if the command is a builtin
 * and if it is the last command in the pipeline.
 * If both conditions are met,
 * it executes the builtin command in the parent process.
 *
 * @param cmd_list The list of commands to execute.
 * @param shell_state The current state of the shell.
 * @return 0 if a builtin command was executed, 1 otherwise.
 */
int	handle_parent_builtin(t_command *cmd_list, t_shell_state *shell_state)
{
	if (cmd_list->cmd_index == 1 && cmd_list->next == NULL && ft_is_builtin(cmd_list->cmd_name) == 0)
	{
		shell_state->last_exit_status = 0;
		configure_redirections(cmd_list, shell_state);
		if (shell_state->last_exit_status != 0)
		{
			restore_redirections(cmd_list);
			return (0);
		}
		ft_execute_builtin(cmd_list, shell_state);
		restore_redirections(cmd_list);
		return (0);
	}
	return (1);
}
