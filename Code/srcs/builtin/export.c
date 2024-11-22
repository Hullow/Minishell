/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:18:01 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/15 19:45:48 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

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
			ft_printf("export: '%s': not a valid identifier\n", args[i]);
			shell_state->last_exit_status = 1;
		}
		else
		{
			if (!update_existing_var(&shell_state->envp, name, args[i]))
				add_new_var(&shell_state->envp, args[i]);
			shell_state->last_exit_status = 0;
		}
		free(name);
		i++;
	}
}
