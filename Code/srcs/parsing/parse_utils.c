/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:49:30 by fallan            #+#    #+#             */
/*   Updated: 2024/11/21 19:12:51 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// checks if a token is of a redirection type
// (REDIR_INPUT, REDIR_OUTPUT, REDIR_APPEND, REDIR_HEREDOC)
// returns 1 if yes, 0 otherwise
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

// checks if token is of type WORD 
bool	ft_token_is_pipe(int token_type)
{
	if (token_type == PIPE)
		return (1);
	else
		return (0);
}
