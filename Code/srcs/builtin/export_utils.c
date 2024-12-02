/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/02 14:42:58 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

const char	*extract_value(const char *new_value)
{
	const char	*value;

	value = ft_strchr(new_value, '=');
	if (value == NULL)
		return (NULL);
	return (value + 1);
}

char	*build_new_var(const char *name, const char *value)
{
	char	*new_var;
	size_t	name_len;
	size_t	value_len;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	new_var = malloc(name_len + value_len + 2);
	if (new_var == NULL)
		return (NULL);
	ft_strlcpy(new_var, name, name_len + 1);
	ft_strlcat(new_var, "=", name_len + 2);
	ft_strlcat(new_var, value, name_len + value_len + 2);
	return (new_var);
}

int	find_var_index(char **envp, char *name, size_t name_len)
{
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], name, name_len) == 0
			&& envp[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	update_existing_var(char ***envp, char *name, const char *new_value)
{
	size_t		name_len;
	char		*new_var;
	int			index;
	const char	*value;

	name_len = ft_strlen(name);
	value = extract_value(new_value);
	if (value == NULL)
		return (0);
	index = find_var_index(*envp, name, name_len);
	if (index == -1)
		return (0);
	free((*envp)[index]);
	new_var = build_new_var(name, value);
	if (new_var == NULL)
		return (0);
	(*envp)[index] = new_var;
	return (1);
}

void	add_new_var(char ***envp, const char *var)
{
	int		i;
	char	**new_envp;

	i = 0;
	while ((*envp)[i] != NULL)
		i++;
	new_envp = (char **)ft_calloc(i + 2, sizeof(char *));
	if (!new_envp)
		error_and_exit("ft_calloc failed", 1);
	i = 0;
	while ((*envp)[i] != NULL)
	{
		new_envp[i] = (*envp)[i];
		i++;
	}
	new_envp[i] = ft_strdup(var);
	if (!new_envp[i])
		error_and_exit("ft_strdup failed", 1);
	free(*envp);
	// free each element of the environment ?
	*envp = new_envp;
}
