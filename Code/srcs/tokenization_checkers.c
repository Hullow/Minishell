/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization-checkers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:35:11 by francis           #+#    #+#             */
/*   Updated: 2024/08/15 14:28:42 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

// checks if previous character was part of an undelimited operator token
int	ft_previous_char_is_undelimited_operator(struct token *tok)
{
	if (tok->str && tok->is_operator == true && tok->is_delimited == false)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

// checks if character is a redirection operator character:
// either '>', '<', or '|'
int	ft_is_operator_character(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	else
		return (0);
}

// checks if character is a blank (space or tab)
int	ft_is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

// checks if previous character 
// 		was part of a word and that that word was not delimited
// rule #### 2.2.2.8. Previous character part of a word
// IF
// - previous character was part of a word
// added:
// - previous token is delimited
int	ft_previous_char_part_of_word(struct token *tok)
{
	if (tok->type == WORD && tok->is_delimited == false)
		return (1);
	else
		return (0);
}
