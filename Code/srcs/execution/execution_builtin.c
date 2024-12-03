/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/03 10:39:00 by cmegret          ###   ########.fr       */
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
 * @brief Executes a builtin command.
 *
 * This function executes the appropriate builtin command
 * based on the command name.
 *
 * @param cmd The command to execute.
 * @param shell_state The current state of the shell.
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
		ft_exit(shell_state, cmd->args);
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
	int	saved_stdin;
	int	saved_stdout;

	if (cmd_list->next == NULL && ft_is_builtin(cmd_list->cmd_name) == 0)
	{
		shell_state->last_exit_status = 0;
		configure_redirections(cmd_list, &saved_stdin,
			&saved_stdout, shell_state);
		if (shell_state->last_exit_status != 0)
		{
			restore_redirections(saved_stdin, saved_stdout);
			return (0);
		}
		ft_execute_builtin(cmd_list, shell_state);
		restore_redirections(saved_stdin, saved_stdout);
		return (0);
	}
	return (1);
}
