/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:40:07 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/20 18:24:44 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

int	g_signal = SIGNAL_NONE;

void	process_signals(void)
{
	if (g_signal == SIGNAL_HEREDOC)
		g_signal = SIGNAL_NONE;
}

int	event(void)
{
	return (0);
}

// Gestionnaire pour SIGINT (CTRL+C)
void	handle_sigint(int sig)
{
	extern int	rl_done;

	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!rl_done)
			rl_redisplay();
		g_signal = SIGNAL_INT + sig;
	}
}

// Gestionnaire pour SIGQUIT (CTRL+\)
void	handle_sigquit(int sig)
{
	(void)sig;
}

void	handle_sigint_heredoc(int sig)
{
	extern int	rl_done;

	(void)sig;
	g_signal = SIGNAL_HEREDOC + sig;
	rl_done = 1;
}
