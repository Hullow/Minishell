/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_OLD.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:35:02 by francis           #+#    #+#             */
/*   Updated: 2024/11/22 19:43:34 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// returns the number of tokens in our linked list
int	ft_count_token_list_args(t_token *tok)
{
	int	i;

	i = 0;
	while (tok)
	{
		i++;
		tok = tok->next;
	}
	return (i);
}


int	ft_allocate_single_arg(t_token *tkn,
	t_command *cmd_sequence)
{
	cmd_sequence->args = malloc(2 * sizeof(char *));
	if (!cmd_sequence->args)
		return (-1); // call error function ?
	cmd_sequence->args[0] = ft_strdup(tkn->str);
	cmd_sequence->args[1] = NULL;
	cmd_sequence->next = NULL; // A CHANGER
	return (0);
}

int	ft_allocate_multiple_args(t_token *tkn,
	t_command *cmd_sequence, int arg_count)
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
	cmd_sequence->next = NULL; // A CHANGER
	return (0);
}

int	ft_process_args(t_token *tkn, t_command *cmd_sequence)
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