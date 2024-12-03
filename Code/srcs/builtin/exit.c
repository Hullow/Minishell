/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:31:14 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/03 08:37:00 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Exits the shell.
 *
 * This function exits the shell with the specified exit status.
 * If a numeric argument is provided, it uses that as the exit status.
 * If the argument is not numeric,
 * it prints an error message and exits with status 2.
 *
 * @param shell_state The current state of the shell.
 * @param args The arguments containing the exit status.
 */
void	ft_exit(t_shell_state *shell_state, char **args)
{
	int	exit_status;
	int	i;

	exit_status = shell_state->last_exit_status;
	i = 0;
	if (args[1])
	{
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				write(STDERR_FILENO, "exit: numeric argument required\n", 32);
				exit(2);
			}
			i++;
		}
		exit_status = ft_atoi(args[1]);
	}
	write(STDOUT_FILENO, "exit\n", 5);
	exit(exit_status);
}
