/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:56:09 by fallan            #+#    #+#             */
/*   Updated: 2024/12/14 18:11:22 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// marks the token as quoted:
// if character is a single quote:
//		if not single quoted, mark as single quoted
//		else, mark as not single quoted (close quote)
// same for double quote
// returns 1
int	ft_mark_token_as_quoted(char *prompt, int i, t_token **tok)
{
	bool	single_quoted;
	bool	double_quoted;
	

	single_quoted = (*tok)->is_single_quoted;
	double_quoted = (*tok)->is_double_quoted;

	if ((*tok)->is_delimited)
	{
		*tok = ft_create_new_token(*tok);
		(*tok)->type = WORD;
		(*tok)->is_operator = false;
	}
	if (prompt[i] == '\'')
	{
		if (!single_quoted && !double_quoted)
			(*tok)->is_single_quoted = true;
		else if (single_quoted && !double_quoted)
			(*tok)->is_single_quoted = false;
		else
			ft_append_char_to_word(tok, '\'');
	}
	else if (prompt[i] == '\"')
	{
		if (!double_quoted && !single_quoted)
			(*tok)->is_double_quoted = true;
		else if (double_quoted && !single_quoted)
			(*tok)->is_double_quoted = false;
		else
			ft_append_char_to_word(tok, '\"');
	}
	return (1);
}
