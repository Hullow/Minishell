/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:37:59 by francis           #+#    #+#             */
/*   Updated: 2024/12/21 16:55:25 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// creates and returns a new token
// initializes all values to NULL or false
t_token	*ft_create_token(int token_type)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->str = NULL;
	tok->type = token_type;
	tok->is_delimited = false;
	tok->is_operator = false;
	tok->to_expand = NULL;
	tok->is_single_quoted = false;
	tok->is_double_quoted = false;
	tok->is_between_quotes = false;
	tok->next = NULL;
	return (tok);
}

// function to create (malloc) a new token and add it to the linked list
// quotes: if previous token was quoted, mark token as quoted too
// else, mark as unquoted
t_token	*ft_add_token_to_list(t_token *tok, int token_type)
{
	t_token	*newtoken;

	if (tok)
	{
		newtoken = ft_create_token(token_type);
		if (!newtoken)
			return (NULL);
		if (tok->is_single_quoted)
		{
			newtoken->is_single_quoted = true;
			newtoken->is_between_quotes = true;
		}
		else if (tok->is_double_quoted)
		{
			newtoken->is_double_quoted = true;
			newtoken->is_between_quotes = true;
		}
		tok->is_delimited = true;
		tok->next = newtoken;
		tok = tok->next;
	}
	return (tok);
}
