/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:48:18 by francis           #+#    #+#             */
/*   Updated: 2024/09/05 13:56:53 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

static int	ft_is_builtin(struct s_command *cmd)
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

int	execute_cmd(struct s_command *cmd, char **envp)
{
	int		pid;
	char	*cmd_path;
	int		status;

	if (cmd == NULL || envp == NULL)
		return (1);
	cmd_path = NULL;
	if (ft_is_builtin(cmd)) // if not a builtin, search
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (1);
		}
		if (pid == 0)
		{
			cmd_path = get_cmd_path(cmd->cmd_name, envp);
			if (cmd_path == NULL)
			{
				perror("get_cmd_path");
				exit(1);
			}
			else if (execve(cmd_path, cmd->args, envp) == -1)
			{
				perror("execve");
				free(cmd_path);
				exit(1);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
			{
				//printf("Child exited with status %d\n", WEXITSTATUS(status));
				return WEXITSTATUS(status);
			}
			else
			{
				//printf("Child terminated abnormally\n");
				free(cmd_path);
				return 1;
			}
		}
	}
	return (0);
}
