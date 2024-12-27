/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:31:14 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/27 17:19:12 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

static int	print_exit_error(char *input, int issue, int status_to_return)
{
	if (issue == NUMERIC_ARG_REQUIRED)
	{
		ft_putstr_fd("exit\nMinishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(input, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	}
	else if (issue == TOO_MANY_ARGUMENTS)
	{
		ft_putstr_fd("exit\nMinishell: exit: too many arguments\n", \
			STDERR_FILENO);
	}
	return (status_to_return);
}

static void	ft_exit_non_digit_argument(char *arg)
{
	print_exit_error(arg, NUMERIC_ARG_REQUIRED, 0);
	exit(255);
}

static void	ft_no_exit_too_many_arguments(t_shell_state *shell_state)
{
	print_exit_error(NULL, TOO_MANY_ARGUMENTS, 0);
	shell_state->last_exit_status = 1;
}

// clears history, frees the shell_state struct, writes "exit" and exits
void	ft_finalize_exit(t_shell_state *shell_state, int exit_stat)
{
	clear_history();
	ft_free_array_of_strings(shell_state->envp);
	if (exit_stat != 255)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(exit_stat);
}

// see exit-value.c in Example-code for reference and testing
//	if (exit_input == -1 && ft_strcmp(args[1], "-1"))
//		=> if we have something else than -1 as input resulting in exit_input -1
// if first char is '-', it could be negative number => continue
// if any other character is not a digit, we exit with an error message
// if we have more than one argument, we print an error message and return
// else, we atoi the argument to set the exit status value:
//		- if atoi returns -1 and the argument was not -1,
//			-> that is an error (number too large or small) -> exit status 255
// 		- if atoi returns a positive number -> exit status is number module 256
//		- if atoi returns a negative number -> (number modulo 256) + 256
void	ft_exit(t_shell_state *shell_state, char **args, int exit_stat, int i)
{
	pid_t	exit_input;

	if (args[1])
	{
		if (args[1][0] == '\0')
			ft_exit_non_digit_argument(args[1]);
		if (args[1][0] == '-')
			i++;
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
				ft_exit_non_digit_argument(args[1]);
			i++;
		}
		if (args[2])
			return (ft_no_exit_too_many_arguments(shell_state));
		exit_input = ft_atoi_adapted(args[1]);
		exit_stat = exit_input % 256;
		if (exit_input == -1 && ft_strcmp(args[1], "-1"))
			exit_stat = print_exit_error(args[1], NUMERIC_ARG_REQUIRED, 255);
		else if (exit_input < 0)
			exit_stat += 256;
	}
	ft_finalize_exit(shell_state, exit_stat);
}
