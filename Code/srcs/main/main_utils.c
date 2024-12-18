/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:11:02 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/18 16:11:07 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Prints an error message and exits the program with the specified
 * status.
 *
 * This function uses perror to print the provided error message, followed by
 * a description of the current error condition. It then exits the program
 * with the given exit status.
 *
 * @param message A pointer to a string containing the error message to be
 * printed.
 * @param last_exit_status The exit status to use when terminating the program.
 *
 * @note This function is designed to be called when a critical error occurs
 *       that prevents the program from continuing.
 */
void	error_and_exit(const char *message, int last_exit_status)
{
	if (message != NULL)
		perror(message);
	else
		write(STDERR_FILENO, "Unknown error\n", 14);
	exit(last_exit_status);
}

/**
 * @brief Frees all allocated memory used by the shell
 *
 * Deallocates memory for:
 * - The prompt string
 * - The token list
 * - The command list and all its components
 *
 * @param prompt The prompt string to free
 * @param token_list The list of tokens to free
 * @param cmd The command list to free
 */
void	ft_free_all(char *prompt, t_token *token_list, t_command *cmd)
{
	free(prompt);
	ft_free_token_list(token_list);
	ft_free_cmd_list(cmd);
}

/**
 * @brief Checks the command-line arguments.
 *
 * This function checks if any command-line arguments are provided.
 * If arguments are provided, it prints a usage message and exits the program.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 */
void	check_arguments(int argc, char **argv, t_shell_state *shell_state)
{
	if (argc > 1)
	{
		printf("Usage: %s\n", argv[0]);
		printf("No arguments are allowed\n");
		shell_state->last_exit_status = EXIT_FAILURE;
		error_and_exit(NULL, shell_state->last_exit_status);
	}
}
