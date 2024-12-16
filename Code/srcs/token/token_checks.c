/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/16 15:26:16 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../header/Minishell.h"

// checks if token has an open quote (single or double)
// returns 1 for single quote
// returns 2 for double quote
// returns 0 otherwise
int	ft_token_has_open_quote(t_token *tok)
{
	if (tok->is_single_quoted)
		return (1);
	else if (tok->is_double_quoted)
		return (2);
	else
		return (0);
}

// checks if previous character was part of an undelimited operator token
int	ft_previous_char_is_undelimited_operator(t_token *tok)
{
	if (tok && !ft_token_has_open_quote(tok)
		&& tok->is_operator && !tok->is_delimited)
	if (tok && !ft_token_has_open_quote(tok)
		&& tok->is_operator && !tok->is_delimited)
		return (1);
	return (0);
}

// checks if previous character was part of a word
// and that that word was not delimited
int	ft_previous_char_part_of_word(t_token *tok)
{
	if (tok && tok->type == WORD && !(tok->is_delimited))
		return (1);
	return (0);
}
