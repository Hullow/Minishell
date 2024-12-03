/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/03 08:56:56 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Finds the index of an environment variable.
 *
 * This function searches for an environment variable in the environment
 * variables array and returns its index.
 *
 * @param envp The environment variables array.
 * @param key The key of the variable to find.
 * @param key_len The length of the key.
 * @return The index of the variable, or -1 if not found.
 */
int	find_var_index(char **envp, char *key, size_t key_len)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

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
 * @brief Adds a new environment variable.
 *
 * This function adds a new environment variable to the environment variables
 * array.
 *
 * @param envp The environment variables array.
 * @param new_var The new variable to add.
 */
void	add_new_env_var(char ***envp, char *new_var)
{
	int		i;
	char	**new_envp;

	i = 0;
	while ((*envp)[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
	{
		free(new_var);
		return ;
	}
	copy_env_vars(new_envp, *envp, i);
	new_envp[i] = new_var;
	new_envp[i + 1] = NULL;
	free(*envp);
	*envp = new_envp;
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

/**
 * @brief Updates an existing environment variable.
 *
 * This function updates the value of an existing environment variable.
 *
 * @param envp The environment variables array.
 * @param name The name of the variable to update.
 * @param new_value The new value of the variable.
 * @return 1 if the variable was updated, 0 otherwise.
 */
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
