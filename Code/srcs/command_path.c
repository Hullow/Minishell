/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:21:29 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/04 10:14:40 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

static int	check_cmd_envp(char *cmd, char **envp)
{
	if (cmd == NULL || envp == NULL)
	{
		perror("cmd or envp is NULL");
		return (1);
	}
	return (0);
}

static char	*join_paths(char *path, char *cmd)
{
	char	*full_path;

	full_path = ft_strjoin(ft_strjoin(path, "/"), cmd);
	if (!full_path)
	{
		perror("ft_strjoin failed");
		return (NULL);
	}
	return (full_path);
}

static char	*find_executable_path(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = join_paths(paths[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
		{
			free(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

static char	**get_env_paths(char **envp)
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

	if (check_cmd_envp(cmd, envp))
		return (NULL);
	paths = get_env_paths(envp);
	if (!paths)
	{
		perror("get_env_paths failed");
		return (NULL);
	}
	full_path = find_executable_path(paths, cmd);
	free(paths);
	return (full_path);
}
