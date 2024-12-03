/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_external.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 08:36:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/03 07:37:22 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

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

void	handle_child_process(t_command *cmd_list, char **envp)
{
	char	*cmd_path;

	cmd_path = resolve_cmd_path(cmd_list->cmd_name, envp);
	check_access_rights(cmd_path, cmd_list->cmd_name);
	if (execve(cmd_path, cmd_list->args, envp) == -1)
	{
		free(cmd_path);
		perror("minishell");
		exit(1);
	}
}
