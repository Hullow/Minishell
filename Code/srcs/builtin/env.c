/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:31:14 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/09 16:24:52 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/Minishell.h"

void	update_env_var(char ***envp, char *key, const char *value)
{
	int		i;
	size_t	key_len;
	char	*new_var;

	i = 0;
	key_len = ft_strlen(key);
	new_var = malloc(key_len + ft_strlen(value) + 2);
	if (!new_var)
		return ;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], key, key_len) == 0
			&& (*envp)[i][key_len] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = new_var;
			return ;
		}
		i++;
	}
	free(new_var);
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
		ft_printf("%s\n", shell_state->envp[i]);
		i++;
	}
	shell_state->last_exit_status = 0;
}
