/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_env_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:02:56 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/23 23:17:25 by francis          ###   ########.fr       */
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
 * Returns NULL if the PATH variable is not found.
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
 * @brief Constructs the full path of a command by searching through PATH
 *
 * This function:
 * 1. Gets paths from PATH environment variable
 * 2. Constructs full path by appending command to each directory
 * 3. Tests each path for executability
 * 4. Frees all allocated memory properly
 *
 * @param cmd The command to find the full path for
 * @param envp An array of environment variables
 * @return Full path of command if found and executable, NULL if not found
 * @note The returned string must be freed by the caller
 * @note Exits with error if:
 *       - cmd or envp is NULL
 *       - Memory allocation fails
 *       - PATH retrieval fails
 */
char	*get_cmd_path(char *cmd, char **envp, int i, char *temp)
{
	char	**paths;
	char	*full_path;

	if (cmd == NULL || envp == NULL)
		error_and_exit("cmd or envp is NULL", 1);
	paths = get_env_paths(envp);
	if (!paths)
		error_and_exit("get_env_paths failed", 1);
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		if (!full_path)
			error_and_exit("ft_strjoin failed", 1);
		if (access(full_path, F_OK) == 0)
		{
			ft_free_array_of_strings(paths);
			free(temp);
			return (full_path);
		}
		free(temp);
		free(full_path);
	}
	ft_free_array_of_strings(paths);
	return (NULL);
}
