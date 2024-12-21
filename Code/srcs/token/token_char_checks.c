/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_char_checks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:26:48 by fallan            #+#    #+#             */
/*   Updated: 2024/12/21 15:51:48 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// checks if character is a single or double quote
// returns 1 if character is single quote
// returns 2 if character is double quote
// returns 0 otherwise
int	ft_is_quote_character(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	else
		return (0);
}

// checks if character is a redirection operator character
// returns 1 if true
// return 0 otherwise
int	ft_is_operator_character(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

// checks if character is a blank (space or tab)
// returns 1 if true
// return 0 otherwise
int	ft_is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

// checks if character is a dollar sign
// returns 1 if true
// return 0 otherwise
int	ft_is_dollar_sign(char c)
{
	if (c == '$')
		return (1);
	else
		return (0);
}