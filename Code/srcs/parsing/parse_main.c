/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:35:01 by francis           #+#    #+#             */
/*   Updated: 2024/12/17 17:20:09 by francis          ###   ########.fr       */
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

// MAIN PARSING FUNCTION
// Mallocs and returns a linked list of commands t_command *
// 
// Each node of t_command * corresponds to a pipe
// Each node contains:
//  - Command name (char *cmd_name)
//  - Command arguments (t_cmd_args* arg_list)
//   (n.b.: parsing stores argument in the list t_cmd_args* arg_list;
//   after parsing, arguments are expanded, and finally, copied in char **args
//   which is actually used to execute the command using execve()
//  - Redirections (t_redir *redir_list), which include heredocs
//	 (n.b.: heredocs are opened and filled right after parsing)
//  - File descriptors to save stdin and stdout before redirections/pipes
//
// HOW IT WORKS:
// Parses our linked list of tokens, starting from left (head)
// Extracts the command, its arguments, redirections, and pipes(other commands)
//
// STEP BY STEP:
// ft_parse_operators assigns the correct token type to operator tokens
// while() loop:
// 	- goes over each token of our tokenized prompt (t_token *tok: linked list)
//	- checks token type
//	- then, depending on type:
//		- adds a redirection to our redirection list
//		- adds a command name/arguments to our command arguments list
//		- adds a new command (pipe) to our list of commands
// return: the first node of our list of commands (t_command *head_cmd)
t_command	*ft_parse(t_token *tok)
{
	t_command	*cmd_list;
	t_command	*head_cmd;

	cmd_list = malloc(sizeof(t_command));
	if (!cmd_list)
		return (NULL);
	ft_initialize_cmd_list(cmd_list);
	head_cmd = cmd_list;
	ft_parse_operators(tok);
	while (tok)
	{
		if (ft_token_is_redir(tok->type))
			ft_add_redir(&tok, cmd_list, NULL);
		else if (ft_token_is_word(tok->type))
			ft_add_cmd_arg_to_list(tok, &(cmd_list->arg_list), NULL);
		else if (ft_token_is_pipe(tok->type))
			cmd_list = ft_add_pipe(cmd_list);
		tok = tok->next;
	}
	return (head_cmd);
}
