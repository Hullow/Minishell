/* ************************************************************************** */
/*	                                                                    */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:35:29 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/15 20:18:47 by cmegret          ###   ########.fr       */
/*   Updated: 2024/11/01 13:18:40 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// probably not necessary, likely done before 
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

// Initializes our cmd_sequence (everything to NULL except input, output)
void	ft_initialize_cmd_sequence(t_command *cmd_sequence)
{
	cmd_sequence->cmd_name = NULL;
	cmd_sequence->args = NULL;
	cmd_sequence->arg_list = NULL;
	cmd_sequence->input = STDIN;
	cmd_sequence->output = STDOUT;
	cmd_sequence->redir_list = NULL;
	cmd_sequence->next = NULL;
}

// add a command sequence/pipe to our linked list of commands
t_command	*ft_add_pipe(t_command *cmd_sequence)
{
	cmd_sequence->next = malloc(sizeof(t_command)); // malloc a node to our list of commands (cmd_sequence)
	if (!(cmd_sequence->next))
		return (NULL);
	cmd_sequence = cmd_sequence->next;
	ft_initialize_cmd_sequence(cmd_sequence);
	return (cmd_sequence);
}

// Parses our linked list of tokens, starting from left (head)
// Extracts the command and the arguments 
// Outputs a struct command with the command name and the arguments
t_command	*ft_parse(t_token *tok, t_shell_state *shell_state)
{
	t_command	*cmd_sequence;
	t_command	*head;

	(void)shell_state; // for envp and variables (exit status: $?, other variables)
	cmd_sequence = malloc(sizeof(t_command)); // malloc a node to our list of commands (cmd_sequence)
	if (!cmd_sequence)
		return (NULL);
	head = cmd_sequence;
	ft_initialize_cmd_sequence(cmd_sequence);
	ft_parse_operators(tok);
	while (tok)
	{
		if (ft_token_is_redir(tok->type))
			ft_add_redir(&tok, cmd_sequence); // add redirections to our redirections list
		else if (ft_token_is_word(tok->type))
			ft_add_cmd_arg(tok->str, cmd_sequence); // add WORD tokens to argument list
		else if (ft_token_is_pipe(tok->type))
			cmd_sequence = ft_add_pipe(cmd_sequence); // add new command sequence tokens to argument list
		tok = tok->next;
	}
	if (ft_allocate_args(head) == -1) // need to modify this to go over the whole cmd_list (all pipes)
		return (NULL);
	ft_print_command_sequences(head);
	return (head);
}
