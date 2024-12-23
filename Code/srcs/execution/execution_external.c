/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_external.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanzi <ahanzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 08:36:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/23 18:52:08 by ahanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Checks the access rights for a command path
 *
 * This function checks if the command path exists and if it is executable.
 * If the command path does not exist,
 * it prints an error message and exits with status 127.
 * If the command path is not executable,
 * it prints an error message and exits with status 126.
 *
 * @param cmd_path The path of the command to check
 * @param cmd_name The name of the command
 * @param shell_state Current shell state for error handling
 */
void	check_access_rights(char *cmd_path, char *cmd_name,
	t_shell_state *shell_state)
{
	if (access(cmd_path, F_OK) != 0)
	{
		printf("%s: No such file or directory\n", cmd_name);
		shell_state->last_exit_status = 127;
		exit(shell_state->last_exit_status);
	}
	else if (access(cmd_path, X_OK) != 0)
	{
		printf("minishell: %s: Permission denied\n", cmd_name);
		shell_state->last_exit_status = 126;
		exit(shell_state->last_exit_status);
	}
}

/**
 * @brief Resolves the command path.
 *
 * This function resolves the full path of the command.
 * If the command name contains a '/',
 * it returns the command name as is.
 * Otherwise, it searches for the command in the PATH environment variable.
 * If the command is not found,
 * it prints an error message and exits with status 127.
 *
 * @param cmd_name The name of the command to resolve.
 * @param envp The environment variables.
 * @return The resolved command path.
 */
char	*resolve_cmd_path(char *cmd_name, t_shell_state *shell_state)
{
	char	*cmd_path;

	if (ft_strchr(cmd_name, '/') != NULL)
		return (cmd_name);
	cmd_path = get_cmd_path(cmd_name, shell_state->envp, -1, NULL);
	if (cmd_path == NULL)
	{
		printf("%s: command not found\n", cmd_name);
		shell_state->last_exit_status = 127;
		exit(shell_state->last_exit_status);
	}
	return (cmd_path);
}

/**
 * @brief Handles the execution of a child process.
 *
 * This function resolves the command path, checks the access rights,
 * and executes the command using execve. If execve fails, it prints
 * an error message and exits with status 1.
 *
 * @param cmd_list The list of commands to execute.
 * @param envp The environment variables.
 */
void	handle_child_process(t_command *cmd_list, t_shell_state *shell_state)
{
	char	*cmd_path;

	cmd_path = resolve_cmd_path(cmd_list->cmd_name, shell_state);
	check_access_rights(cmd_path, cmd_list->cmd_name, shell_state);
	if (execve(cmd_path, cmd_list->args, shell_state->envp) == -1)
	{
		free(cmd_path);
		error_and_exit("minishell", 1);
	}
	free(cmd_path);
}
