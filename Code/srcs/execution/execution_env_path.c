/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_env_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:02:56 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/13 19:19:38 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"
/*
### 4.0.1. Shell Execution environment
A shell execution environment consists of the following:
	- Open files inherited upon invocation of the shell, plus open files controlled by exec
	- Working directory as set by `cd`
	- Shell parameters from the environment inherited by the shell when it begins (see the `export` built-in)

Reference: See [Shell Execution Environment](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_12)
*/

char	**get_env_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (cmd == NULL || envp == NULL)
		error_and_exit("cmd or envp is NULL");
	paths = get_env_paths(envp);
	if (!paths)
		error_and_exit("get_env_paths failed");
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
		if (!full_path)
			error_and_exit("ft_strjoin failed");
		if (access(full_path, X_OK) == 0)
		{
			free(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free(paths);
	return (NULL);
}
