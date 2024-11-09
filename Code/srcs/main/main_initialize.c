/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_initialize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:31:30 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/09 10:28:00 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"
/**
 * @brief Checks the command-line arguments.
 *
 * This function checks if any command-line arguments are provided.
 * If arguments are provided, it prints a usage message and exits the program.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 */
static void	check_arguments(int argc, char **argv)
{
	if (argc > 1)
	{
		printf("Usage: %s\n", argv[0]);
		printf("No arguments are allowed\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief Counts the number of environment variables.
 *
 * This function counts the number of environment variables provided in the
 * envp array.
 *
 * @param envp An array of environment variables.
 * @return The number of environment variables.
 */
static int	count_env_variables(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

/**
 * @brief Duplicates the environment variables.
 *
 * This function duplicates the environment variables from the envp array
 * into the shell_state structure.
 *
 * @param shell_state A pointer to the shell state structure.
 * @param envp An array of environment variables.
 * @param count The number of environment variables.
 */
static void	duplicate_env(t_shell_state *shell_state,
	char **envp, int count)
{
	int	i;

	i = 0;
	shell_state->envp = malloc(sizeof(char *) * (count + 1));
	if (!shell_state->envp)
		error_and_exit("malloc failed");
	while (i < count)
	{
		shell_state->envp[i] = ft_strdup(envp[i]);
		if (!shell_state->envp[i])
		{
			while (i-- > 0)
				free(shell_state->envp[i]);
			free(shell_state->envp);
			error_and_exit("ft_strdup failed");
		}
		i++;
	}
	shell_state->envp[count] = NULL;
}

/**
 * @brief Initializes the shell state.
 *
 * This function initializes the shell state by setting up signal handlers,
 * checking command-line arguments, counting environment variables, and
 * duplicating the environment variables into the shell state structure.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 * @param shell_state A pointer to the shell state structure.
 * @param envp An array of environment variables.
 */
void	ft_initialize(int argc, char **argv,
	t_shell_state *shell_state, char **envp)
{
	int	count;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	check_arguments(argc, argv);
	count = count_env_variables(envp);
	duplicate_env(shell_state, envp, count);
}
