/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:36:39 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/05 15:13:28 by francis          ###   ########.fr       */
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

// See Shell-functioning.md, ctrl + f "error"
void	error_and_exit(const char *message)
{
	perror(message);
	/*
	##### 4.2.1.b.2. unsuccessful PATH search
	ELSE<br>
	- search is unsuccessful<br>
		=> command fails with exit status 127<br>
		=> shell writes an error message
	*/
	if (ft_strncmp(message, "runsuccessful PATH search"))
		exit(127);
/* 	else if (ft_strncmp(message, "..."))
		exit(); */
	else
		exit(1);
}
