/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:40:07 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/20 12:50:58 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

int	g_signal = 0;

void	process_signals(void)
{
	if (g_signal == SIGNAL_HEREDOC)
		g_signal = SIGNAL_NONE;
}

int event(void)
{
	return (0);
}

// Gestionnaire pour SIGINT (CTRL+C)
void	handle_sigint(int sig)
{
	extern int rl_done;

	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!rl_done)
			rl_redisplay();
	}
}

// Gestionnaire pour SIGQUIT (CTRL+\)
void	handle_sigquit(int sig)
{
	(void)sig;
}

void	handle_sigint_heredoc(int sig)
{
	extern int rl_done;

	(void)sig;
	g_signal = SIGNAL_HEREDOC;
	rl_done = 1;
}
