/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/16 17:16:41 by francis          ###   ########.fr       */
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
