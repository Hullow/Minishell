/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:35:11 by francis           #+#    #+#             */
/*   Updated: 2024/11/01 18:33:17 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// checks if previous character was part of an undelimited operator token
int	ft_previous_char_is_undelimited_operator(t_token *tok)
{
	if (tok && tok->is_operator && !tok->is_delimited)
		return (1);
	return (0);
}

// checks if character is a redirection operator character
int	ft_is_operator_character(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

// checks if character is a blank (space or tab)
int	ft_is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

// checks if previous character was part of a word
// and that that word was not delimited
int	ft_previous_char_part_of_word(t_token *tok)
{
	if (tok && tok->type == WORD && !tok->is_delimited)
		return (1);
	return (0);
}
