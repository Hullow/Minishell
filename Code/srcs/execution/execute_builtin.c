/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:23:09 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/15 18:48:15 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

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

int	ft_execute_builtin(t_command *cmd, t_shell_state *shell_state)
{
	if (ft_is_builtin(cmd->cmd_name) == 0)
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
		return (0);
	}
	else
		return (1);
}
