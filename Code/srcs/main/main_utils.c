/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:36:39 by cmegret           #+#    #+#             */
/*   Updated: 2024/10/18 20:04:38 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Minishell.h"

// memory allocation (getcwd)
/**
 * ft_initialize - Initializes the shell state.
 *
 * This function initializes the shell state by checking the command-line
 * arguments and setting the current working directory. If more than one
 * argument is provided, it prints usage information and exits the program.
 * It also sets the current working directory in the shell state.
 *
 * Parameters:
 *   argc - The number of command-line arguments.
 *   argv - The array of command-line arguments.
 *   shell_state - A pointer to the shell state structure to be initialized.
 *
 * Notes:
 *   - If more than one argument is provided, the function prints usage
 *     information and exits the program.
 *   - If the current working directory cannot be obtained, the function
 *     calls error_and_exit with an appropriate error message.
 */
void	ft_initialize(int argc, char **argv, struct s_shell_state *shell_state)
{
	if (argc > 1)
	{
		printf("Usage: %s\n", argv[0]);
		printf("No arguments are allowed\n");
		exit(EXIT_FAILURE);
	}
	shell_state->current_directory = getcwd(NULL, 0);
	if (!shell_state->current_directory)
		error_and_exit("getcwd failed");
}

/**
 * ft_prompt - Generates a custom command prompt for the shell.
 *
 * This function creates a command prompt using the last folder
 * of the current working directory (CWD). If the CWD cannot be obtained,
 * it uses a default prompt "Minishell : ".
 *
 * Returns:
 *   A pointer to a string containing the command prompt.
 *   The string must be freed by the caller to avoid memory leaks.
 *
 * Notes:
 *   - Uses the getcwd function to obtain the CWD.
 *   - Uses the readline function to read user input.
 *   - On memory allocation error, the function prints an error message and
 *     terminates the program.
 */
char	*ft_prompt(void)
{
	char	*prompt;
	char	*message;
	char	cwd[1024];
	char	*last_folder;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		last_folder = ft_strrchr(cwd, '/');
		if (last_folder != NULL)
			last_folder++;
		message = ft_strjoin(last_folder, " - Minishell : ");
		if (message == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		prompt = readline(message);
		free(message);
	}
	else
	{
		perror("getcwd");
		prompt = readline("Minishell : ");
	}
	return (prompt);
}

/**
 * error_and_exit - Prints an error message and exits the program.
 *
 * This function prints the provided error message using perror and then
 * exits the program with a failure status.
 *
 * Parameters:
 *   message - A pointer to a string containing the error message to be printed.
 *
 * Notes:
 *   - The function uses perror to print the error message, which includes
 *     the string pointed to by message followed by a description of the
 *     current error condition.
 *   - The function then calls exit with EXIT_FAILURE to terminate the program.
 */
void	error_and_exit(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}
