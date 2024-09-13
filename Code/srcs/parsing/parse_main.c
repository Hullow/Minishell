/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:35:29 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/11 22:23:35 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

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

static int	ft_allocate_multiple_args(struct s_token *tkn,
	struct s_command *cmd_sequence, int arg_count)
{
	int	i;

	cmd_sequence->args = malloc((arg_count + 1) * sizeof(char *));
	if (!cmd_sequence->args)
		return (-1); // call error function ?
	i = 0;
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

static int	ft_process_args(struct s_token *tkn, struct s_command *cmd_sequence)
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
		if (ft_allocate_multiple_args(tkn->next, cmd_sequence, arg_count) == -1)
			return (-1);
	}
	return (0);
}

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
		if (ft_process_args(tkn, cmd_sequence) == -1)
			return (NULL);
	}
	return (cmd_sequence);
}
