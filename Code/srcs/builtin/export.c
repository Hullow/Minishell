/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/20 15:43:52 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

int	is_valid_name(const char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Extracts the variable name from a string.
 *
 * This function extracts the variable name from a string in the format
 * "name=value".
 *
 * @param var The string containing the variable.
 * @return The extracted variable name.
 */
char	*get_var_name(const char *var)
{
	size_t	name_len;
	char	*name;

	name_len = 0;
	while (var[name_len] && var[name_len] != '=')
		name_len++;
	name = (char *)malloc(sizeof(char) * (name_len + 1));
	if (!name)
		error_and_exit("malloc failed", 1);
	ft_strlcpy(name, var, name_len + 1);
	return (name);
}

/**
 * @brief Exports environment variables.
 *
 * This function adds or updates environment variables in the shell's
 * environment.
 *
 * @param shell_state The current state of the shell.
 * @param args The arguments containing the variables to export.
 */
void	ft_export(t_shell_state *shell_state, char **args)
{
	char	*name;
	int		i;

	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			name = get_var_name(args[i]);
			if (!is_valid_name(name))
			{
				printf("export: '%s': not a valid identifier\n", args[i]);
				shell_state->last_exit_status = 1;
			}
			else
			{
				if (!update_existing_var(&shell_state->envp, name, args[i]))
					add_new_env_var(&shell_state->envp, ft_strdup(args[i]));
				shell_state->last_exit_status = 0;
			}
			free(name);
		}
		i++;
	}
}
