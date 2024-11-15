/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_env_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:02:56 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/12 15:54:15 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Retrieves the PATH environment variable and splits
 * it into an array of paths.
 *
 * This function searches through the provided environment
 * variables to find the PATH variable.
 * Once found, it splits the PATH variable into an array of
 * individual paths using ':' as the delimiter.
 *
 * @param envp An array of environment variables.
 * @return An array of strings, each representing a path from
 * the PATH environment variable.
 *         Returns NULL if the PATH variable is not found.
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

/**
 * @brief Constructs the full path of a command by searching through
 * the PATH environment variable.
 *
 * This function retrieves the PATH environment variable and constructs the
 * full path for the given command.
 * It checks each path in the PATH variable to see if the command exists
 * and is executable.
 *
 * @param cmd The command to find the full path for.
 * @param envp An array of environment variables.
 * @return A string containing the full path of the command if found and
 *         executable.
 *         Returns NULL if the command is not found in any of the paths.
 *
 * @note The returned string must be freed by the caller to avoid memory leaks.
 * @note If cmd or envp is NULL, the function calls error_and_exit with
 * an appropriate error message.
 * @note If any memory allocation fails, the function calls error_and_exit with
 * an appropriate error message.
 */
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
