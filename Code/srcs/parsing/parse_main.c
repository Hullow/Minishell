/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:36:57 by francis           #+#    #+#             */
/*   Updated: 2024/12/11 13:58:17 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// parses operator tokens and assigns them the appropriate token type
t_token	*ft_parse_operators(t_token *head)
{
	t_token	*iterator;

	iterator = head;
	while (iterator)
	{
		if (!(iterator->type))
		{
			if (!iterator->str)
				return (head);
			if (!(ft_strncmp(iterator->str, ">", 2)))
				iterator->type = REDIR_OUTPUT;
			else if (!(ft_strncmp(iterator->str, "<", 2)))
				iterator->type = REDIR_INPUT;
			else if (!(ft_strncmp(iterator->str, ">>", 3)))
				iterator->type = REDIR_APPEND;
			else if (!(ft_strncmp(iterator->str, "<<", 3)))
				iterator->type = REDIR_HEREDOC;
			else if (!(ft_strncmp(iterator->str, "|", 2)))
				iterator->type = PIPE;
		}
		iterator = iterator->next;
	}
	return (head);
}

// Initializes our cmd_list (everything to NULL except input, output)
void	ft_initialize_cmd_list(t_command *cmd_list)
{
	cmd_list->cmd_name = NULL;
	cmd_list->args = NULL;
	cmd_list->arg_list = NULL;
	cmd_list->saved_input = STDIN;
	cmd_list->saved_output = STDOUT;
	cmd_list->redir_list = NULL;
	cmd_list->next = NULL;
}

// add a command sequence/pipe to our linked list of commands
t_command	*ft_add_pipe(t_command *cmd_list)
{
	cmd_list->next = malloc(sizeof(t_command));
	if (!(cmd_list->next))
		return (NULL);
	cmd_list = cmd_list->next;
	ft_initialize_cmd_list(cmd_list);
	return (cmd_list);
}

// Parses our linked list of tokens, starting from left (head)
// Extracts the command and the arguments 
// Outputs a struct command with the command name and the arguments
// NEED TO ADD ERROR HANDLING !
// shell_state: for envp and variables (exit status: $?, other variables)
// while() loop:
// 	- goes over each token of our token list
//	- checks token type
//	- then, depending on type:
//		- adds a redirection to our redirection list
//		- adds a command argument to our command arguments list
//		- adds a new command (/pipe) to our list of commands
// after the while() loop, copy command arguments from the list to the array
// with ft_allocate_cmd_args_to_array (n.b.: for each command/pipe)
// return the first node of our list of commands (t_command	*head_cmd)
t_command	*ft_parse(t_token *tok, t_shell_state *shell_state)
{
	t_command	*cmd_list;
	t_command	*head_cmd;
	t_token		*head_tok;

	(void)shell_state;
	cmd_list = malloc(sizeof(t_command));
	if (!cmd_list)
		return (NULL);
	ft_initialize_cmd_list(cmd_list);
	ft_parse_operators(tok);
	head_cmd = cmd_list;
	head_tok = tok;
	while (tok)
	{
		if (ft_token_is_redir(tok->type))
			ft_add_redir(&tok, cmd_list, NULL);
		else if (ft_token_is_word(tok->type))
			ft_add_cmd_arg_to_list(tok->str, &(cmd_list->arg_list));
		else if (ft_token_is_pipe(tok->type))
			cmd_list = ft_add_pipe(cmd_list);
		tok = tok->next;
	}
	ft_free_token_list(head_tok);
	if (ft_allocate_cmd_args_to_array(head_cmd) == -1)
		return (NULL);
	return (head_cmd);
}
