/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:44:36 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/20 12:16:41 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "Minishell.h"

// Signal
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	handle_sigint_heredoc(int sig);
int		event(void);
void	process_signals(void);

#endif