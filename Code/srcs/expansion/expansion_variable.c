/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:28:35 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/17 12:45:01 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

char	*expand_variable(char *new_arg,
	t_shell_state *shell_state, char *var_name)
{
	char	*env_value;
	char	*result;

	if (ft_strcmp(var_name, "?") == 0)
	{
		env_value = convert_exit_status(shell_state->last_exit_status);
		result = ft_strjoin_free(new_arg, env_value);
		free(env_value);
		return (result);
	}
	env_value = get_env_var(shell_state->envp, var_name);
	if (env_value)
		return (ft_strjoin_free(new_arg, env_value));
	return (new_arg);
}
