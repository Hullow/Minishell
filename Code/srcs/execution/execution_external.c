/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_external.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 08:36:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/06 15:08:06 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Checks the access rights for a command path.
 *
 * This function checks if the command path exists and if it is executable.
 * If the command path does not exist,
 * it prints an error message and exits with status 127.
 * If the command path is not executable,
 * it prints an error message and exits with status 126.
 *
 * @param cmd_path The path of the command to check.
 * @param cmd_name The name of the command.
 */
void	check_access_rights(char *cmd_path, char *cmd_name)
{
	if (access(cmd_path, F_OK) != 0)
	{
		printf("%s: No such file or directory\n", cmd_name);
		exit(127);
	}
	else if (access(cmd_path, X_OK) != 0)
	{
		printf("minishell: %s: Permission denied\n", cmd_name);
		exit(126);
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
char	*resolve_cmd_path(char *cmd_name, char **envp)
{
	char	*cmd_path;

	if (ft_strchr(cmd_name, '/') != NULL)
		return (cmd_name);
	cmd_path = get_cmd_path(cmd_name, envp);
	if (cmd_path == NULL)
	{
		printf("%s: command not found\n", cmd_name);
		exit(127);
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
void	handle_child_process(t_command *cmd_list, char **envp)
{
	char	*cmd_path;

	printf("DEBUG CHILD: Entrée dans handle_child_process\n");
	printf("DEBUG CHILD: cmd_list->cmd_name: %s\n", cmd_list->cmd_name);
	cmd_path = resolve_cmd_path(cmd_list->cmd_name, envp);
	printf("DEBUG CHILD: cmd_path après resolve_cmd_path: %s\n", cmd_path);
	check_access_rights(cmd_path, cmd_list->cmd_name);
	printf("DEBUG CHILD: Après check_access_rights\n");
	printf("DEBUG CHILD: Appel de execve avec cmd_path: %s\n", cmd_path);
	if (execve(cmd_path, cmd_list->args, envp) == -1)
	{
		free(cmd_path);
		perror("minishell");
		printf("DEBUG CHILD: execve a échoué\n");
		exit(1);
	}
	printf("DEBUG CHILD: Sortie de handle_child_process\n");
}
