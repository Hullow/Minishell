/* ************************************************************************** */
/*	                                                                    */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:35:29 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/01 13:18:40 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// probably not necessary, likely done before 
struct s_token	*ft_parse_operators(struct s_token *head)
{
	struct s_token	*iterator;

	iterator = head;
	while (iterator)
	{
		if (!(iterator->type))
		{
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

void	ft_initialize_cmd_sequence(struct s_command *cmd_sequence)
{
	cmd_sequence->cmd_name = NULL;
	cmd_sequence->args = NULL;
	cmd_sequence->input = 0;
	cmd_sequence->output = 1;
	cmd_sequence->redir_list = NULL;
	cmd_sequence->next = NULL;
}

// Parses our linked list of tokens, starting from left (head)
// Extracts the command and the arguments 
// Outputs a struct command with the command name and the arguments
struct s_command	*ft_parse(struct s_token *tok)
{
	struct s_command	*cmd_sequence;
	s_cmd_args			*arg_list = NULL;
	s_redir				*redir_list = NULL;

	cmd_sequence = malloc(sizeof(struct s_command)); // malloc a node to our list of commands (cmd_sequence)
	if (!cmd_sequence)
		return (NULL);
	ft_initialize_cmd_sequence(cmd_sequence);
	ft_parse_operators(tok);
	while (tok)
	{
		if (ft_token_is_redir(tok->type))
			ft_add_redir(&tok, redir_list); // add redirections to our redirections list
		else if (ft_token_is_word(tok->type)) // add WORD tokens to argument list
			ft_add_cmd_arg(tok->str, cmd_sequence, arg_list); // before: cmd_sequence->cmd_name = strdup(tok->str);
		tok = tok->next;
	}
	if (ft_allocate_args(cmd_sequence, arg_list) == -1)
		return (NULL);
	return (cmd_sequence);
}
