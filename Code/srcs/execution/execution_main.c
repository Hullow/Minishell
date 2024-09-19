/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:23:09 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/19 13:52:37 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * ft_is_and_execute_builtin - Checks if the command is a builtin and executes it.
 *
 * This function checks if the given command corresponds to a builtin command.
 * If it does, it executes the builtin command and returns 0. Otherwise, it
 * returns 1.
 *
 * Parameters:
 *   cmd - A pointer to the command structure containing
 *   the command to be checked.
 *   shell_state - A pointer to the shell state structure.
 *
 * Returns:
 *   0 if the command is a builtin and was executed, 1 otherwise.
 */
int	ft_is_and_execute_builtin(struct s_command *cmd,
	struct s_shell_state *shell_state)
{
	if (ft_strncmp(cmd->cmd_name, "echo", 4) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd_name, "cd", 2) == 0)
	{
		ft_cd(cmd, shell_state);
		return (0);
	}
	else if (ft_strncmp(cmd->cmd_name, "pwd", 3) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd_name, "export", 6) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd_name, "unset", 5) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd_name, "env", 3) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd_name, "exit", 4) == 0)
		return (0);
	else
		return (1);
}

/**
 * handle_child_process - Handles the execution of a command in a child process.
 *
 * This function is called in the child process after a fork. It attempts to
 * find the path of the command and execute it using execve. If any error
 * occurs, it prints an error message and exits the process.
 *
 * Parameters:
 *   cmd - A pointer to the command structure containing the
 *   command to be executed.
 *   envp - An array of environment variables.
 */
static void	handle_child_process(struct s_command *cmd, char **envp)
{
	char	*cmd_path;

	cmd_path = NULL;
	cmd_path = get_cmd_path(cmd->cmd_name, envp);
	if (cmd_path == NULL)
		error_and_exit("get_cmd_path");
	else if (execve(cmd_path, cmd->args, envp) == -1)
	{
		free(cmd_path);
		error_and_exit("execve");
	}
}

/**
 * handle_parent_process - Handles the parent process after forking.
 *
 * This function is called in the parent process after a fork. It waits for
 * the child process to finish and returns its status. If any error occurs,
 * it prints an error message and exits the process.
 *
 * Parameters:
 *   pid - The process ID of the child process.
 *
 * Returns:
 *   The status of the child process.
 */
static int	handle_parent_process(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		error_and_exit("waitpid");
	return (status);
}

/**
 * execute_cmd - Executes a command.
 *
 * This function checks if the command is a builtin and executes it if it is.
 * If the command is not a builtin, it forks a new process to execute the
 * command. It handles both the child and parent processes appropriately.
 *
 * Parameters:
 *   cmd - A pointer to the command structure containing
 *   the command to be executed.
 *   envp - An array of environment variables.
 *   shell_state - A pointer to the shell state structure.
 *
 * Returns:
 *   0 if the command was executed successfully, -1 if there was an error.
 */
int	execute_cmd(struct s_command *cmd, char **envp,
	struct s_shell_state *shell_state)
{
	pid_t	pid;

	if (cmd == NULL || cmd->cmd_name == NULL)
		return (-1);
	if (ft_is_and_execute_builtin(cmd, shell_state) == 0)
		return (0);
	pid = fork();
	if (pid == 0)
		handle_child_process(cmd, envp);
	else if (pid < 0)
		error_and_exit("fork");
	else
		return (handle_parent_process(pid));
	return (0);
}
