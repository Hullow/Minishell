/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:53:29 by cmegret           #+#    #+#             */
/*   Updated: 2025/01/03 19:17:37 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

int	is_redirection(t_token *token)
{
	return (token->type == REDIR_INPUT || token->type == REDIR_OUTPUT
		|| token->type == REDIR_APPEND || token->type == REDIR_HEREDOC);
}

int	check_consecutive_pipes(t_token *current)
{
	if (current->next && current->next->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
		return (2);
	}
	return (0);
}

int	check_previous_token(t_token *prev)
{
	if (!prev || is_redirection(prev))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (2);
	}
	return (0);
}

int	check_next_token(t_token *current)
{
	if (!current->next || is_redirection(current->next))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (2);
	}
	return (0);
}

int	validate_pipes(t_token *tokens, int ret)
{
	t_token	*current;
	t_token	*prev;

	if (!tokens || !(tokens->next))
		return (0);
	current = tokens->next;
	prev = NULL;
	while (current)
	{
		if (current->type == PIPE)
		{
			ret = check_consecutive_pipes(current);
			if (ret != 0)
				return (ret);
			ret = check_previous_token(prev);
			if (ret != 0)
				return (ret);
			ret = check_next_token(current);
			if (ret != 0)
				return (ret);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
