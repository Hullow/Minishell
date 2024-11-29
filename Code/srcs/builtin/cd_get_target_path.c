/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_get_target_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:45:06 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/28 11:11:07 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

char	*handle_special_paths(char *path)
{
	if (!path || ft_strncmp(path, "~", 2) == 0)
		return (getenv("HOME"));
	else if (ft_strncmp(path, "-", 2) == 0)
	{
		path = getenv("OLDPWD");
		if (path)
			printf("%s\n", path);
		return (path);
	}
	return (NULL);
}

char	*resolve_path(char *path)
{
	char	*resolved_path;

	resolved_path = realpath(path, NULL);
	if (!resolved_path)
	{
		fprintf(stderr, "cd: %s\n", path);
		return (NULL);
	}
	return (resolved_path);
}

char	*get_target_path(char **args)
{
	char	*path;
	char	*resolved_path;
	char	cwd[PATH_MAX];

	path = handle_special_paths(args[1]);
	if (path)
		return (strdup(path));
	if (args[1][0] == '/')
		return (resolve_path(args[1]));
	if (!getcwd(cwd, sizeof(cwd)))
		return (NULL);
	path = malloc(strlen(cwd) + strlen(args[1]) + 2);
	if (!path)
		return (NULL);
	ft_strlcpy(path, cwd, strlen(cwd) + 1);
	ft_strlcat(path, "/", strlen(cwd) + 2);
	ft_strlcat(path, args[1], strlen(cwd) + strlen(args[1]) + 2);
	resolved_path = resolve_path(path);
	free(path);
	return (resolved_path);
}
