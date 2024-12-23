/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanzi <ahanzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:31:14 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/23 20:30:57 by ahanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

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
				write(STDERR_FILENO, "Minishell: exit: ", 18);
				ft_putstr_fd(args[1], STDERR_FILENO);
				write(STDERR_FILENO, ": numeric argument required\n", 29);
				exit(255);
			}
			i++;
		}
		if (args[2])
		{
			write(STDOUT_FILENO, "exit\n", 5);
			write(STDERR_FILENO, "Minishell: exit: too many arguments\n", 37);
			shell_state->last_exit_status = 1;
			return ;
		}
		exit_status = ft_atoi(args[1]);
	}
	clear_history(); // on 42 OS X iMacs
	// rl_clear_history();
	ft_free_shell_state(shell_state);
	write(STDOUT_FILENO, "exit\n", 5);
	exit(exit_status);
}
