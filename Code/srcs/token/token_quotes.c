/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:56:09 by fallan            #+#    #+#             */
/*   Updated: 2024/12/14 16:20:18 by fallan           ###   ########.fr       */
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
	if (prompt[i] == '\'')
	{
		if (!(*tok)->is_single_quoted)
			(*tok)->is_single_quoted = true;
		else
			(*tok)->is_single_quoted = false;
	}
	else if (prompt[i] == '\"')
	{
		if (!(*tok)->is_double_quoted)
			(*tok)->is_double_quoted = true;
		else
			(*tok)->is_double_quoted = false;
	}
	return (1);
}
