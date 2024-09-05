/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:36:39 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/04 20:41:31 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

void	ft_check_args(int argc, char **argv)
{
	if (argc > 1)
	{
		fprintf(stderr, "Usage: %s\n", argv[0]);
		fprintf(stderr, "No arguments are allowed\n");
		exit(EXIT_FAILURE);
	}
}

void	error_and_exit(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}
