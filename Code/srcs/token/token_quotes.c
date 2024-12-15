/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:56:09 by fallan            #+#    #+#             */
/*   Updated: 2024/12/15 18:58:31 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// marks the token as quoted:
// if character is a single quote:
//		if not single quoted, mark as single quoted
//		else, mark as not single quoted (close quote)
// same for double quote
// returns 1
int	ft_handle_quote_tokenization(char c,
	bool single_quoted, bool double_quoted, t_token **tok)
{
	if ((*tok)->is_delimited)
		*tok = ft_add_token_to_list(*tok, WORD);
	(*tok)->quote_status = ft_token_has_open_quote(*tok); // first quote: set to false. second quote: set to true
	if (c == '\'')
	{
		if (!ft_token_has_open_quote(*tok))
			(*tok)->is_single_quoted = true;
		else if (single_quoted && !double_quoted)
			(*tok)->is_single_quoted = false;
		else
			ft_append_char_to_word(tok, '\'');
	}
	else if (c == '\"')
	{
		if (!ft_token_has_open_quote(*tok))
			(*tok)->is_double_quoted = true;
		else if (double_quoted && !single_quoted)
			(*tok)->is_double_quoted = false;
		else
			ft_append_char_to_word(tok, '\"');
	}
	return (1);
}
