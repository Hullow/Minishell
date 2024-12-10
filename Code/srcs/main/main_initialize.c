/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_initialize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:36:57 by francis           #+#    #+#             */
/*   Updated: 2024/12/10 17:15:14 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

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
static void	duplicate_env(t_shell_state *shell_state, char **envp, int count)
{
	int	i;

	i = 0;
	shell_state->envp = malloc(sizeof(char *) * (count + 1));
	if (!shell_state->envp)
		error_and_exit("malloc failed", 1);
	while (i < count)
	{
		shell_state->envp[i] = ft_strdup(envp[i]);
		if (!shell_state->envp[i])
		{
			while (i-- > 0)
				free(shell_state->envp[i]);
			free(shell_state->envp);
			error_and_exit("ft_strdup failed", 1);
		}
		i++;
	}
	shell_state->envp[count] = NULL;
}

/**
 * @brief Configure le terminal pour désactiver l'écho du caractère ^C.
 *
 * Cette fonction obtient les attributs actuels du terminal, modifie les
 * attributs pour désactiver l'écho du caractère ^C (généré par Ctrl+C),
 * et applique les nouveaux attributs immédiatement.
 */
static void	setup_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

/**
 * @brief Initializes the shell state.
 *
 * This function initializes the shell state by
 * counting the environment variables,
 * duplicating the environment variables,
 * and setting the initial last exit status to 0.
 *
 * @param shell_state The shell state to initialize.
 * @param envp The environment variables.
 */
static void	initialize_shell_state(t_shell_state *shell_state, char **envp)
{
	int	count;

	count = count_env_variables(envp);
	duplicate_env(shell_state, envp, count);
	shell_state->last_exit_status = 0;
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
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	check_arguments(argc, argv);
	initialize_shell_state(shell_state, envp);
	setup_terminal();
}
