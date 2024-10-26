/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:21:26 by cmegret           #+#    #+#             */
/*   Updated: 2024/10/26 13:18:16 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// function to create (malloc) a new token and add it to the linked list
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

// Rule to tokenize the end of input
struct s_token	*ft_tokenize_end_of_input(struct s_token *tok)
{
	if (tok)
		tok->is_delimited = 1;
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

// Rule for tokenizing blanks (spaces or tabs)
int	ft_tokenize_blank(struct s_token **tok)
{
	(*tok)->is_delimited = true;
	return (1);
}

// Rule for tokenizing a new word
int	ft_new_word(struct s_token **tok, char c)
{
	char	character[2];

	character[0] = c;
	character[1] = '\0';
	(*tok) = ft_create_new_token(*tok);
	(*tok)->type = WORD;
	(*tok)->is_operator = false;
	(*tok)->str = ft_strdup(character);
	(*tok)->is_delimited = false;
	return (1);
}

// Rule for appending character to word
int	ft_append_char_to_word(struct s_token **tok, char c)
{
	char	*temp;
	char	character[2];

	temp = ft_strdup((*tok)->str);
	character[0] = c;
	character[1] = '\0';
	(*tok)->str = ft_strjoin(temp, character);
	free(temp);
	return (1);
}
