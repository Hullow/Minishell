/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/02 16:19:14 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

static int	find_env_var_index(char **envp, char *key, size_t key_len)
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

static void	copy_env_vars(char **new_envp, char **envp, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		new_envp[j] = envp[j];
		j++;
	}
}

static void	add_new_env_var(char ***envp, char *new_var)
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

void	update_env_var(char ***envp, char *key, const char *value)
{
	int		i;
	size_t	key_len;
	char	*new_var;

	key_len = ft_strlen(key);
	new_var = ft_strjoin3(key, "=", value);
	if (!new_var)
		return ;
	i = find_env_var_index(*envp, key, key_len);
	if (i >= 0)
	{
		free((*envp)[i]);
		(*envp)[i] = new_var;
	}
	else
		add_new_env_var(envp, new_var);
}

/**
 * @brief Prints the environment variables.
 *
 * This function iterates through the environment variables and prints each one.
 *
 * @param envp An array of environment variables.
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
