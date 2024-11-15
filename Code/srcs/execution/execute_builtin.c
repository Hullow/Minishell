/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:23:09 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/15 14:50:09 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

int	ft_is_builtin(char *cmd_name)
{
	if (ft_strncmp(cmd_name, "echo", 4) == 0)
		return (0);
	else if (ft_strncmp(cmd_name, "unset", 5) == 0)
		return (0);
	else if (ft_strncmp(cmd_name, "export", 6) == 0)
		return (0);
	else if (ft_strncmp(cmd_name, "pwd", 3) == 0)
		return (0);
	else if (ft_strncmp(cmd_name, "cd", 2) == 0)
		return (0);
	else if (ft_strncmp(cmd_name, "exit", 4) == 0)
		return (0);
	else if (ft_strncmp(cmd_name, "env", 3) == 0)
		return (0);
	return (1);
}

int	ft_execute_builtin(t_command *cmd, t_shell_state *shell_state)
{
	if (ft_is_builtin(cmd->cmd_name) == 0)
	{
		if (ft_strncmp(cmd->cmd_name, "echo", 4) == 0)
			ft_echo(cmd->args, shell_state);
		else if (ft_strncmp(cmd->cmd_name, "unset", 5) == 0)
			ft_unset(shell_state, cmd->args);
		else if (ft_strncmp(cmd->cmd_name, "export", 6) == 0)
			ft_export(shell_state, cmd->args);
		else if (ft_strncmp(cmd->cmd_name, "pwd", 3) == 0)
			ft_pwd(shell_state);
		else if (ft_strncmp(cmd->cmd_name, "cd", 2) == 0)
			ft_cd(cmd, shell_state);
		else if (ft_strncmp(cmd->cmd_name, "exit", 4) == 0)
			ft_exit(shell_state, cmd->args);
		else if (ft_strncmp(cmd->cmd_name, "env", 3) == 0)
			ft_env(shell_state);
		return (0);
	}
	else
		return (1);
}
