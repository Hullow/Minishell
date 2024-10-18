/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:35:29 by cmegret           #+#    #+#             */
/*   Updated: 2024/10/18 20:06:48 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Minishell.h"

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

// allocate a single argument to our command sequence :
// command without any arguments
static int	ft_allocate_single_arg(struct s_token *tkn,
	struct s_command *cmd_sequence)
{
	cmd_sequence->args = malloc(2 * sizeof(char *));
	if (!cmd_sequence->args)
		return (-1); // call error function ?
	cmd_sequence->args[0] = ft_strdup(tkn->str);
	cmd_sequence->args[1] = NULL;
	return (0);
}

// allocate arguments to our command sequence :
// command with arguments
static int	ft_allocate_multiple_args(struct s_token *tkn,
	struct s_command *cmd_sequence, int arg_count)
{
	int	i;

	cmd_sequence->args = malloc((arg_count + 1) * sizeof(char *));
	if (!cmd_sequence->args)
		return (-1); // call error function ?
	cmd_sequence->args[0] = ft_strdup(tkn->str);
	tkn = tkn->next;
	i = 1;
	while (tkn)
	{
		if (tkn->type == WORD)
		{
			cmd_sequence->args[i] = ft_strdup(tkn->str);
			if (cmd_sequence->args[i] == NULL)
				return (-1);
			i++;
		}
		tkn = tkn->next;
	}
	cmd_sequence->args[i] = NULL;
	return (0);
}

// calls the appropriate function to allocate arguments to our command sequence
static int	ft_allocate_args(struct s_token *tkn, struct s_command *cmd_sequence)
{
	int	arg_count;

	arg_count = ft_count_token_list_args(tkn);
	if (arg_count == 1)
	{
		if (ft_allocate_single_arg(tkn, cmd_sequence) == -1)
			return (-1);
	}
	else
	{
		if (ft_allocate_multiple_args(tkn, cmd_sequence, arg_count) == -1)
			return (-1);
	}
	return (0);
}

// Parses our linked list of tokens, starting from left (head)
// Extracts the command and the arguments 
// Outputs a struct command with the command name and the arguments
struct s_command	*ft_parse(struct s_token *head)
{
	struct s_command	*cmd_sequence;
	struct s_token		*tkn;

	cmd_sequence = malloc(sizeof(struct s_command));
	if (!cmd_sequence)
		return (NULL);
	tkn = head;
	if (tkn->type == WORD)
	{
		cmd_sequence->cmd_name = ft_strdup(tkn->str);
		if (ft_allocate_args(tkn, cmd_sequence) == -1)
			return (NULL); // call error function ?
	}
	return (cmd_sequence);
}
