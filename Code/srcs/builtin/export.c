/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/20 15:45:34 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"


/**
 * @brief Checks if a variable name is valid.
 *
 * This function checks if the given variable name contains only alphanumeric
 * characters or underscores.
 *
 * @param name The name of the variable to check.
 * @return 1 if the name is valid, 0 otherwise.
 */
int	is_valid_name(const char *name)
{
	int	i;

	i = 0;
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
		i++;
	}
}
