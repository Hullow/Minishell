/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:53:29 by cmegret           #+#    #+#             */
/*   Updated: 2025/01/04 10:56:13 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Checks if a token is a redirection operator
 *
 * @param token Token to check
 * @return int 1 if token is redirection, 0 otherwise
 */
int	is_redirection(t_token *token)
{
	return (token->type == REDIR_INPUT || token->type == REDIR_OUTPUT
		|| token->type == REDIR_APPEND || token->type == REDIR_HEREDOC);
}

/**
 * @brief Checks for consecutive pipe operators
 *
 * @param current Current token being checked
 * @return int 2 if consecutive pipes found, 0 otherwise
 */
int	check_consecutive_pipes(t_token *current)
{
	if (current->next && current->next->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
		return (2);
	}
	return (0);
}

/**
 * @brief Validates the token before a pipe
 *
 * @param prev Previous token in the list
 * @return int 2 if invalid previous token, 0 if valid
 */
int	check_previous_token(t_token *prev)
{
	if (!prev || !prev->str || prev->str[0] == '\0' || is_redirection(prev))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (2);
	}
	return (0);
}

/**
 * @brief Validates the token after a pipe
 *
 * @param current Current pipe token
 * @return int 2 if invalid next token, 0 if valid
 */
int	check_next_token(t_token *current)
{
	if (!current->next || is_redirection(current->next))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (2);
	}
	return (0);
}

/**
 * @brief Main pipe validation function
 *
 * @param tokens Token list to validate
 * @param ret Initial return value
 * @return int 0 if valid, 2 if syntax error
 */
int	validate_pipes(t_token *tokens, int ret)
{
	t_token	*current;
	t_token	*prev;

	if (!tokens)
		return (0);
	current = tokens;
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
