/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:40:07 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/22 16:29:01 by francis          ###   ########.fr       */
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
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_done = 1;
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
