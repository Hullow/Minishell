/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:59:44 by fallan            #+#    #+#             */
/*   Updated: 2024/12/14 11:27:09 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// frees our linked list of commands
// n.b.: the list of redirections in the command list is freed previously
// by ft_allocate_cmd_args_to_array (called by ft_parse in parse_main.c)
void	ft_free_cmd_list(t_command *head_cmd)
{
	t_command	*temp;
	int			i;

	i = 0;
	while (head_cmd)
	{
		temp = head_cmd;
		head_cmd = head_cmd->next;
		while (temp->args[i])
		{
			free(temp->args[i]);
			i++;
		}
		free(temp->args);
		free(temp);
	}
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
