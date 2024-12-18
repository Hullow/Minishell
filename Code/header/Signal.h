/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:44:36 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/18 14:47:22 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "Minishell.h"

// Signal
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	handle_sigint_heredoc(int sig);

#endif