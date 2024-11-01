/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:31:14 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/01 18:35:33 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/Minishell.h"

void	ft_exit(char ***envp, t_shell_state *shell_state)
{
	(void)envp;
	(void)shell_state;
	exit(shell_state->last_exit_status);
}
