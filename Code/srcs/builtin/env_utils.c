/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/03 09:10:36 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Copies environment variables.
 *
 * This function copies the environment variables from one array to another.
 *
 * @param new_envp The new environment variables array.
 * @param envp The original environment variables array.
 * @param count The number of variables to copy.
 */
void	copy_env_vars(char **new_envp, char **envp, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		new_envp[j] = envp[j];
		j++;
	}
}

/**
 * @brief Extracts the value from a variable string.
 *
 * This function extracts the value part from a string in the format
 * "name=value".
 *
 * @param new_value The string containing the variable.
 * @return The extracted value.
 */
const char	*extract_value(const char *new_value)
{
	const char	*value;

	value = ft_strchr(new_value, '=');
	if (value == NULL)
		return (NULL);
	return (value + 1);
}

/**
 * @brief Builds a new variable string.
 *
 * This function constructs a new variable string in the format "name=value".
 *
 * @param name The name of the variable.
 * @param value The value of the variable.
 * @return The constructed variable string.
 */
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

/**
 * @brief Adds a new environment variable.
 *
 * This function adds a new environment variable to the environment variables
 * array.
 *
 * @param envp The environment variables array.
 * @param var The new variable to add.
 */
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
	*envp = new_envp;
}
