/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:56:57 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/03 08:48:44 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Removes an environment variable at a given index.
 *
 * This function removes the environment variable at the specified index
 * from the environment variables array.
 *
 * @param envp The environment variables array.
 * @param index The index of the variable to remove.
 */
void	remove_var(char ***envp, int index)
{
	int		i;
	char	**new_envp;

	i = 0;
	while ((*envp)[i] != NULL)
		i++;
	new_envp = (char **)ft_calloc(i, sizeof(char *));
	if (!new_envp)
		error_and_exit("ft_calloc failed", 1);
	i = 0;
	while (i < index)
	{
		new_envp[i] = (*envp)[i];
		i++;
	}
	free((*envp)[index]);
	while ((*envp)[i + 1] != NULL)
	{
		new_envp[i] = (*envp)[i + 1];
		i++;
	}
	free(*envp);
	*envp = new_envp;
}

/**
 * @brief Unsets environment variables.
 *
 * This function removes the specified environment variables from the shell's
 * environment.
 *
 * @param shell_state The current state of the shell.
 * @param args The arguments containing the names of the variables to unset.
 */
void	ft_unset(t_shell_state *shell_state, char **args)
{
	char	*name;
	int		index;
	int		i;

	i = 1;
	shell_state->last_exit_status = 0;
	while (args[i])
	{
		name = get_var_name(args[i]);
		if (!is_valid_name(name))
		{
			printf("unset: '%s': not a valid identifier\n", args[i]);
			shell_state->last_exit_status = 1;
			free(name);
			return ;
		}
		index = find_var_index(shell_state->envp, name, ft_strlen(name));
		if (index != -1)
			remove_var(&shell_state->envp, index);
		free(name);
		i++;
	}
}
