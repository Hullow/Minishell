/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:36:39 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/11 21:25:03 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

 // memory allocation (getcwd)
void	ft_initialize(int argc, char **argv, struct s_shell_state *shell_state)
{
	if (argc > 1)
	{
		fprintf(stderr, "Usage: %s\n", argv[0]);
		fprintf(stderr, "No arguments are allowed\n");
		exit(EXIT_FAILURE);
	}
	shell_state->current_directory = getcwd(NULL, 0);
	if (!shell_state->current_directory)
		error_and_exit("getcwd failed");
}

void	error_and_exit(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}
