/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:36:43 by francis           #+#    #+#             */
/*   Updated: 2024/12/14 15:40:05 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*prompt;
	t_shell_state	shell_state;
	// t_command		*cmd_list;
	t_token			*token_list;

	ft_initialize(argc, argv, &shell_state, envp);
	prompt = ft_prompt();
	while (prompt != NULL)
	{
		if (*prompt)
			add_history(prompt);
		token_list = ft_parse_operators(ft_tokenize(prompt));
		ft_print_all_token_strings(&token_list);
		// token_list = ft_tokenize(prompt);
		// cmd_list = ft_parse(token_list, &shell_state);
		// expand_command_variables(cmd_list, &shell_state);
		// // ft_exit_bug_print_debugger(cmd_list); // prevents the "exit bug"
		// // ft_print_command_sequences(cmd_list);
		// execute_cmd(cmd_list, &shell_state);
		// ft_free_cmd_list(cmd_list);
		free(prompt);
		prompt = ft_prompt();
	}
	return (0);
}

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
