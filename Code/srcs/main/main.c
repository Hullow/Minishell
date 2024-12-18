/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:54:34 by francis           #+#    #+#             */
/*   Updated: 2024/12/18 15:22:42 by cmegret          ###   ########.fr       */
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
		exit(shell_state->last_exit_status);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char			*prompt;
	t_shell_state	shell_state;
	t_command		*cmd_list;
	t_token			*token_list;

	ft_initialize(argc, argv, &shell_state, envp);
	prompt = ft_prompt(0);
	while (prompt != NULL)
	{
		if (*prompt)
			add_history(prompt);
		token_list = ft_tokenize(prompt);
		cmd_list = ft_parse(token_list);
		ft_open_heredocs(cmd_list);
		if (g_signal)
		{
			g_signal = 0;
			ft_free_all(prompt, token_list, cmd_list);
			prompt = ft_prompt(0);
			continue ;
		}
		expand_command_variables(cmd_list, &shell_state);
		execute_cmd(cmd_list, &shell_state);
		ft_free_all(prompt, token_list, cmd_list);
		prompt = ft_prompt(0);
	}
	return (0);
}
