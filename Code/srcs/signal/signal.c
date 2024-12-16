/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:40:07 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/16 17:07:45 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"
#include <readline/readline.h>

int	g_signal = 0;

// Gestionnaire pour SIGINT (CTRL+C)
void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0); // comment this out on 42 OS X computers
		rl_redisplay();
	}
}

// Gestionnaire pour SIGQUIT (CTRL+\)
void	handle_sigquit(int sig)
{
	(void)sig;
}
