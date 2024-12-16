/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/03 08:38:01 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Implementation of the echo builtin command
 *
 * Writes its arguments to standard output. Arguments are separated
 * by a single space character and followed by a newline by default.
 *
 * Options:
 * -n : Suppresses the trailing newline
 *      Multiple consecutive -n options are treated as one
 *
 * Examples:
 * - echo hello world     -> prints "hello world\n"
 * - echo -n hello world  -> prints "hello world" (no newline)
 *
 * @param args Array of arguments (args[0] is "echo")
 * @param shell_state Current state of the shell
 *
 * @note Always returns success (sets last_exit_status to 0)
 */
void	ft_echo(char **args, t_shell_state *shell_state)
{
	int	i;
	int	n_option;

	i = 1;
	n_option = 0;
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		n_option = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_option)
		printf("\n");
	shell_state->last_exit_status = 0;
}
