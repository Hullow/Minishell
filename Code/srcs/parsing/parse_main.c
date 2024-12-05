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
// NEED TO ADD ERROR HANDLING !
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
			ft_add_redir(&tok, cmd_sequence, NULL); // add redirection to our redirections list
		else if (ft_token_is_word(tok->type))
			ft_add_cmd_arg_to_list(tok->str, cmd_sequence); // add command name if missing, else add command argument to argument list
		else if (ft_token_is_pipe(tok->type))
			cmd_sequence = ft_add_pipe(cmd_sequence); // add new command to command sequence (=> create new pipe)
		tok = tok->next;
	}
	if (ft_allocate_cmd_args_to_array(head) == -1) // copy arguments from argument list to argument array (for each command)
		return (NULL);
	// if (cmd_sequence->cmd_name == NULL || ft_strlen(cmd_sequence->cmd_name) == 0)
	// 	return (NULL); // what if redirection creates file(s) ?
	return (head);
}
