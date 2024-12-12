/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:35:11 by francis           #+#    #+#             */
/*   Updated: 2024/12/12 15:30:29 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// checks if token is between quotes : single quotes and/or double quotes
bool	ft_is_quoted(t_token *tok)
{
	if (tok->is_single_quoted || tok->is_double_quoted)
		return (true);
	else
		return (false);
}

// checks if previous character was part of an undelimited operator token
int	ft_previous_char_is_undelimited_operator(t_token *tok)
{
	if (tok && tok->is_operator && !tok->is_delimited)
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
