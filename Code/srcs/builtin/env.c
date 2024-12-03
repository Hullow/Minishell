/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/03 09:10:27 by cmegret          ###   ########.fr       */
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

/**
 * @brief Prints the environment variables.
 *
 * This function iterates through the environment variables and prints each one.
 *
 * @param shell_state The current state of the shell.
 */
void	ft_env(t_shell_state *shell_state)
{
	int	i;

	i = 0;
	while (shell_state->envp[i])
	{
		printf("%s\n", shell_state->envp[i]);
		i++;
	}
	shell_state->last_exit_status = 0;
}
