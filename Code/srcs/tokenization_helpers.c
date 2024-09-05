/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 09:24:36 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/04 09:27:20 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

void	ft_print_all_token_strings(struct s_token **head)
{
	struct s_token	*iterator;

	iterator = *head;
	while (iterator != 0)
	{
		printf("token: %s\n", iterator->str);
		iterator = iterator->next;
	}
}

struct s_token	*ft_create_new_token(struct s_token *tok)
{
	struct s_token	*newtoken;

	if (tok && tok->str)
	{
		newtoken = malloc(sizeof(struct s_token));
		if (!newtoken)
			return (0);
		newtoken->str = NULL;
		newtoken->type = 0;
		newtoken->is_operator = NULL;
		newtoken->next = NULL;
		newtoken->is_delimited = false;
		tok->is_delimited = true;
		tok->next = newtoken;
		tok = tok->next;
	}
	return (tok);
}

struct s_token	*ft_tokenize_end_of_input(struct s_token *tok)
{
	if (tok)
	{
		tok->is_delimited = 1;
	}
	else
	{
		tok = malloc (1 * sizeof(struct s_token));
		if (!tok)
			return (NULL);
		tok->str = ft_strdup("");
		tok->type = END_OF_INPUT;
		tok->is_delimited = true;
		tok->is_operator = false;
		tok->is_quoted = false;
	}
	return (tok);
}
