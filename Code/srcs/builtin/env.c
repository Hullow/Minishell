/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/03 08:41:56 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

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
