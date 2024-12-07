/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:36:57 by francis           #+#    #+#             */
/*   Updated: 2024/12/07 14:37:53 by francis          ###   ########.fr       */
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
	cmd_list->next = malloc(sizeof(t_command)); // malloc a node to our list of commands (cmd_list)
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
t_command	*ft_parse(t_token *tok, t_shell_state *shell_state)
{
	t_command	*cmd_list;
	t_command	*head;

	(void)shell_state; // for envp and variables (exit status: $?, other variables)
	cmd_list = malloc(sizeof(t_command)); // malloc a node to our list of commands (cmd_list)
	if (!cmd_list)
		return (NULL);
	head = cmd_list;
	ft_initialize_cmd_list(cmd_list);
	ft_parse_operators(tok);
	while (tok)
	{
		if (ft_token_is_redir(tok->type))
			ft_add_redir(&tok, cmd_list, NULL); // add redirection to our redirections list
		else if (ft_token_is_word(tok->type))
			ft_add_cmd_arg_to_list(tok->str, cmd_list); // add command name if missing, else add command argument to argument list
		else if (ft_token_is_pipe(tok->type))
			cmd_list = ft_add_pipe(cmd_list); // add new command to command sequence (=> create new pipe)
		tok = tok->next;
	}
	// copy arguments from argument list to argument array (for each command)
	if (ft_allocate_cmd_args_to_array(head) == -1)
		return (NULL);
	// if (cmd_list->cmd_name == NULL || ft_strlen(cmd_list->cmd_name) == 0)
	// 	return (NULL); // what if redirection creates file(s) ?
	return (head);
}
