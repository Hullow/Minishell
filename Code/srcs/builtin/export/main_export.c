/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:18:01 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/27 14:58:02 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/Minishell.h"

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
		error_and_exit("malloc failed");
	ft_strlcpy(name, var, name_len + 1);
	name[name_len] = '\0';
	return (name);
}

void	ft_export(char ***envp, const char *var)
{
	char	*name;

	name = get_var_name(var);
	if (!is_valid_name(name))
	{
		ft_printf("export: '%s': not a valid identifier\n", var);
		free(name);
		return ;
	}
	if (!update_existing_var(envp, name, var))
		add_new_var(envp, var);
	free(name);
}
