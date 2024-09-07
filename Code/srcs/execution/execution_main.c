/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:23:09 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/07 19:18:57 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// Builtin checker: checks if the command corresponds to a builtin
int	ft_is_builtin(struct s_command *cmd)
{
	if (ft_strncmp(cmd->cmd_name, "echo", 4) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd_name, "cd", 2) == 0)
		return (0);
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

static int	handle_parent_process(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		error_and_exit("waitpid");
	return (status);
}

int	execute_cmd(struct s_command *cmd, char **envp)
{
	pid_t	pid;

	if (cmd == NULL || cmd->cmd_name == NULL)
		return (-1);
	pid = fork();
	if (pid == 0)
		handle_child_process(cmd, envp);
	else if (pid < 0)
		error_and_exit("fork");
	else
		return (handle_parent_process(pid));
	return (0);
}
