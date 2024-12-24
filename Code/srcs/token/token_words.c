/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:40:36 by francis           #+#    #+#             */
/*   Updated: 2024/12/24 14:09:29 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// Rule for tokenizing a new word
int	ft_new_word(t_token **tok, char c)
{
	char	character[2];

	character[0] = c;
	character[1] = '\0';
	if ((*tok)->is_delimited)
		*tok = ft_add_token_to_list(*tok, WORD);
	else if (!(*tok)->str)
		(*tok)->type = WORD;
	else
		printf("ft_new_word: error\n");
	(*tok)->str = ft_strdup(character);
	return (1);
}

// Rule for appending character to word
int	ft_append_char_to_word(t_token **tok, char c)
{
	char	*temp;
	char	character[2];

	character[0] = c;
	character[1] = '\0';
	if (!(*tok)->str)
		(*tok)->str = ft_strdup(character);
	else
	{
		temp = ft_strdup((*tok)->str);
		free((*tok)->str);
		(*tok)->str = ft_strjoin(temp, character);
		free(temp);
	}
	return (1);
}

// if a token has a NULL token string, mallocs an empty string instead
void	ft_set_empty_token_strings(t_token *tok)
{
	while (tok)
	{
		if (!(tok->str) && tok->is_delimited)
			tok->str = ft_strdup("");
		if (!(tok->str))
			return ;
		tok = tok->next;
	}
}

// Rule to tokenize the end of input
// If there is a token, we delimit it
// Else, we create a token with an empty string
// Returns the token
// If there is a token, we delimit it
// Else, we create a token with an empty string
// Returns the token
t_token	*ft_tokenize_end_of_input(t_token *tok)
{
	if (tok)
		tok->is_delimited = true;
	else
	{
		tok = ft_create_token(END_OF_INPUT);
		if (!tok)
			return (NULL);
		tok->str = ft_strdup("");
		tok->is_delimited = true;
	}
	return (tok);
}

// Rule for tokenizing blanks (spaces or tabs)
// Delimits the preceding token without creating a new one
// Returns 1 to advance by one character in the prompt
int	ft_tokenize_blank(t_token **tok)
{
	(*tok)->is_delimited = true;
	return (1);
}
