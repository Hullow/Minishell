/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:31:14 by cmegret           #+#    #+#             */
/*   Updated: 2025/01/04 10:44:57 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Prints exit error messages to stderr
 *
 * @param input String that caused the error (for numeric arg error)
 * @param issue Type of error (NUMERIC_ARG_REQUIRED or TOO_MANY_ARGUMENTS)  
 * @param status_to_return Exit status to return
 * @return Status code to be used as exit status
 */
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

/**
 * @brief Handles exit with non-digit argument
 * Prints error message and exits with status 255
 *
 * @param arg The invalid argument string
 */
static void	ft_exit_non_digit_argument(char *arg)
{
	print_exit_error(arg, NUMERIC_ARG_REQUIRED, 0);
	exit(255);
}

/**
 * @brief Handles exit with non-digit argument
 * Prints error message and exits with status 255
 *
 * @param arg The invalid argument string
 */
static void	ft_no_exit_too_many_arguments(t_shell_state *shell_state)
{
	print_exit_error(NULL, TOO_MANY_ARGUMENTS, 0);
	shell_state->last_exit_status = 1;
}

/**
 * @brief Performs final cleanup and exits the shell
 * Clears history, frees environment variables array
 * and exits with provided status
 *
 * @param shell_state Current shell state to cleanup
 * @param exit_stat Exit status to use
 */
void	ft_finalize_exit(t_shell_state *shell_state, int exit_stat)
{
	clear_history();
	ft_free_array_of_strings(shell_state->envp);
	if (exit_stat != 255)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(exit_stat);
}

/**
 * @brief Main exit builtin implementation
 * Handles argument validation and exit status calculation
 *
 * @param shell_state Current shell state
 * @param args Array of command arguments
 * @param exit_stat Default exit status 
 * @param i Index for argument parsing
 */
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
