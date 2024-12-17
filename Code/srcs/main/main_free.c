/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:59:44 by fallan            #+#    #+#             */
/*   Updated: 2024/12/17 17:24:21 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// frees our linked list of tokens, and when it exists, each token string
// frees our linked list of commands
// n.b.: the list of redirections in the command list is freed previously
// by ft_allocate_cmd_args_to_array (called by ft_parse in parse_main.c)
void	ft_free_token_and_cmd_list(t_token *token_list, t_command *head_cmd)
{

	ft_free_token_list(token_list);
	while (head_cmd)
	{
		ft_free_redir_list(&(head_cmd->redir_list)); // already done ???
		ft_free_arg_list(&(head_cmd->arg_list));
		ft_free_cmd_args(&(head_cmd->args));
		ft_free_cmd_list(head_cmd->);
		ft_free_cmd_list(head_cmd);
	}
}

ft_free_cmd_list(t_command *cmd)
{
	t_command	*temp_cmd;
	int			i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd)
	{
		temp_cmd = cmd;
		ft_free_arg_list(cmd->arg_list);
		// ft_free_arg_list_to_expand => TO ADD !
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
		cmd = cmd->next;
	}
}

void	ft_free_token_list(t_token *token_list)
{
	t_token	*temp_tok;

	if (!token_list)
		return ;
	while (token_list)
	{
		temp_tok = token_list;
		token_list = token_list->next;
		if (temp_tok->str)
			free(temp_tok->str);
		free(temp_tok);
		// SET TO NULL TO PREVENT DOUBLE FREE!
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
