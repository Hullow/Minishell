/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:59:44 by fallan            #+#    #+#             */
/*   Updated: 2024/12/16 16:12:40 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// frees our linked list of tokens, and when it exists, each token string
// frees our linked list of commands
// n.b.: the list of redirections in the command list is freed previously
// by ft_allocate_cmd_args_to_array (called by ft_parse in parse_main.c)
void	ft_free_token_and_cmd_list(t_token *token_list, t_command *head_cmd)
{
	t_command	*temp_cmd;
	t_token		*temp_tok;
	int			i;

	if (!token_list)
		return ;
	while (token_list)
	{
		temp_tok = token_list;
		token_list = token_list->next;
		if (temp_tok->str)
			free(temp_tok->str);
		free(temp_tok);
	}
	i = 0;
	while (head_cmd)
	{
		temp_cmd = head_cmd;
		head_cmd = head_cmd->next;
		if (temp_cmd->args)
		{
			while (temp_cmd->args[i])
			{
				free(temp_cmd->args[i]);
				i++;
			}
		}
		free(temp_cmd->args);
		free(temp_cmd);
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
