/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:49:30 by fallan            #+#    #+#             */
/*   Updated: 2024/11/01 18:54:10 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// checks if a token is of a redirection type
// (REDIR_INPUT, REDIR_OUTPUT, REDIR_APPEND, REDIR_HEREDOC)
bool	ft_token_is_redir(int token_type)
{
	if (token_type == REDIR_INPUT || \
		token_type == REDIR_OUTPUT || \
		token_type == REDIR_APPEND || \
		token_type == REDIR_HEREDOC)
		return (1);
	else
		return (0);
}

// checks if token is of type WORD 
bool	ft_token_is_word(int token_type)
{
	if (token_type == WORD)
		return (1);
	else
		return (0);
}

// returns the number of arguments in our argument list
int	ft_count_args(t_cmd_args *arg_list)
{
	int	i;

	i = 0;
	if (!arg_list)
		return (0);
	while (arg_list)
	{
		i++;
		arg_list = arg_list->next;
	}
	return (i);
}

// frees our linked list of arguments
void	ft_free_arg_list(t_cmd_args	*arg_list)
{
	t_cmd_args	*temp = NULL;

	while (arg_list)
	{
		temp = arg_list;
		if (arg_list->arg_string)
			free(arg_list->arg_string);
		arg_list = arg_list->next;
		free(temp);
	}
}

// traverses the linked list of tokens and returns the last token
t_redir *ft_last_redir(t_redir *redir_list)
{
	if (!redir_list || !redir_list->next)
		return (redir_list);
	while (redir_list->next)
		redir_list = redir_list->next;
	return (redir_list);
}