/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:56:09 by fallan            #+#    #+#             */
/*   Updated: 2024/12/12 16:14:07 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// marks the token as quoted:
// sets tok->is_single_quoted or tok->is_double_quoted to true
// returns 1
int	ft_mark_token_as_quoted(char *prompt, int i, t_token **tok)
{
	if (ft_is_quote_character(prompt[i] == 1))
		(*tok)->is_single_quoted = true;
	else if (ft_is_quote_character(prompt[i] == 2))
		(*tok)->is_double_quoted = true;
	return (1);
}
