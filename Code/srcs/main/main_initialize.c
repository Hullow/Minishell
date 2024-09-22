/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_initialize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:31:30 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/22 17:33:06 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

static void	check_arguments(int argc, char **argv)
{
	if (argc > 1)
	{
		printf("Usage: %s\n", argv[0]);
		printf("No arguments are allowed\n");
		exit(EXIT_FAILURE);
	}
}

static void	init_current_directory(struct s_shell_state *shell_state)
{
	shell_state->current_directory = getcwd(NULL, 0);
	if (!shell_state->current_directory)
		error_and_exit("getcwd failed");
}

static int	count_env_variables(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

static void	duplicate_env(struct s_shell_state *shell_state,
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

void	ft_initialize(int argc, char **argv,
	struct s_shell_state *shell_state, char **envp)
{
	int	count;

	check_arguments(argc, argv);
	init_current_directory(shell_state);
	count = count_env_variables(envp);
	duplicate_env(shell_state, envp, count);
}
