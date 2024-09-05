/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:35:11 by francis           #+#    #+#             */
/*   Updated: 2024/09/04 11:23:37 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

// function to create (malloc) a new token and add it to the linked list:
//
// if anything is in the token (tok->str not NULL):
	// delimits the token
	// creates a new token
	// sets the new token to undelimited
	// adds the new token to our token list
// nb: type 0 does not correspond to any typedef'd token type
struct token	*ft_create_new_token(struct token *tok)
{
	struct token	*newtoken;

	if (tok && tok->str)
	{
		newtoken = malloc(sizeof(struct token));
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

// Rule to tokenize the end of input:
//
// ##### 2.2.2.1. End of input
// IF
// - end of input is recognized
//
// AND	EITHER:
// - there is a current token
//
// => delimit the current token
//
// OR:
// - there is no current token
//
// => return the end-of-input indicator as the token `=> return {EOF} token ?`
struct token	*ft_tokenize_end_of_input(struct token *tok)
{
	if (tok)
	{
		tok->is_delimited = 1;
	}
	else
	{
		tok = malloc (1 * sizeof(struct token));
		if (!tok)
			return (NULL);
		tok->str = ft_strdup(""); // maybe not do this ?
		tok->type = END_OF_INPUT;
		tok->is_delimited = true;
		tok->is_operator = false;
		tok->is_quoted = false;
	}
	return (tok);
}

// Function for two rules:
//
// ##### 2.2.2.2. Continued operator token and current character usable
// IF
// - previous character used as part of an operator 
// - current character can be used 
//		with the previous characterS to form an operator
// - current character not quoted
//		=> use character as part of that (operator) token
// n.b.: only `>>` or `<<` in our case
//
// returns 1 if the current character was added to the previous (operator) token,
// returns 0 if the previous (operator) character was delimited
//
// ##### 2.2.2.3. Continued operator token and current character not usable
// - current character can NOT be used
//		with the previous characterS to form an operator
// - current character not quoted
// 		=> use character as part of that (operator) token
// 		=> delimit the operator containing the previous character
int	ft_continue_operator_token(char *prompt, int i, struct token **tok)
{
	if (ft_strlen((*tok)->str) != 1) // if token was of length > 1, the current character cannot be used with the previous characters to form an operator, because or only multi-character operators are '>>' and '<<'
		(*tok)->is_delimited = true; // therefore: apply rule 2.2.2.3. and delimit operator containing previous token
	else if (prompt[i] == '>' && prompt[i - 1] == '>' && (*tok)->is_quoted == false) // && tok->is_quoted == false)
	// there is only '>' in the operator token => we can form a '>>' with it
	{
		free((*tok)->str);
		(*tok)->str = ft_strdup(">>");
		(*tok)->type = REDIR_APPEND;
		(*tok)->is_delimited = true; // do this or not ?
		// e.g. `echo "hello" >>> 3` gives the error:
		// => bash: syntax error near unexpected token `>'
		return (1); // because we assigned the character to a token
	}
	else if (prompt[i] == '<' && prompt[i - 1] == '<' && (*tok)->is_quoted == false) // only '>' in the operator token, we can form a '>>' with it
	{
		free((*tok)->str);
		(*tok)->str = ft_strdup("<<");
		(*tok)->type = REDIR_HEREDOC; // do this or not ?
		(*tok)->is_delimited = true;
		return (1); // because we assigned the character to a token
	}
	else
		(*tok)->is_delimited = true; // Why do that ? Not clear. Maybe we shouldn't delimit
			// => need to create a new operator token ? no
	return (0); // we did not assign the character to a token
}

// Create a new operator token:
// 
// ##### 2.2.2.6. New operator token
// IF
// - current character is unquoted
// - current character can be used as the first character of a new operator
//
// => delimit the current token, if any<br>
// => use the current character as the beginning of the next (operator) token
int	ft_new_operator_token(char *prompt, int i, struct token **tok)
{
	(*tok) = ft_create_new_token(*tok);
	if (prompt[i] == '>')
		(*tok)->str = ft_strdup(">");
	else if (prompt[i] == '<')
		(*tok)->str = ft_strdup("<");
	else if (prompt[i] == '|')
		(*tok)->str = ft_strdup("|");
	(*tok)->is_operator = true;
	(*tok)->is_delimited = false;
	(*tok)->next = NULL;
	return (1);
}

// Rule for blanks (spaces or tabs)
//
// #### 2.2.2.7. Space or tab
// (N.b.: "A blank is a space or tab character" cf. [Bash reference manual - Definitions](https://www.gnu.org/software/bash/manual/bash.html#Definitions))
//
// IF
// - current character is an unquoted \<space\> or \<tab\>
//
// => delimit any token containing previous character<br>
// => discard current character
int	ft_tokenize_blank(struct token **tok)
{
	if ((*tok)->str)
		(*tok)->is_delimited = true;
	return (1);
}

// #### 2.2.2.8. Previous character part of a word
// IF
// - previous character was part of a word
//
// => append current character to that word
//
// N.b.: added => check if previous token delimited
int	ft_append_char_to_word(struct token **tok, char c)
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

// #### 2.2.2.10 New word
// (last rule)
// => use current character as the start of a new word
int	ft_new_word(struct token **tok, char c)
{
	char	character[2];

	character[0] = c;
	character[1] = '\0';
	(*tok) = ft_create_new_token(*tok);
	(*tok)->type = WORD;
	(*tok)->is_operator = false;
	(*tok)->str = ft_strdup(character);
	return (1);
}

// prints each token's contents (tok->str)
void	ft_print_all_token_strings(struct token **head)
{
	struct token	*iterator;

	iterator = *head;
	while (iterator != 0)
	{
		//printf("token: %s\n", iterator->str);
		iterator = iterator->next;
	}
}

// Breaks the input (prompt) into tokens by calling each tokenization function
struct token	*ft_tokenize(char *prompt)
{
	struct token	*tok;
	struct token	*head;
	int				i;

	tok = malloc(sizeof(struct token)); // nb: could use ft_create_token here
	if (!tok)
		return (NULL);
	tok->next = NULL;
	tok->str = NULL;
	tok->type = 0; // type undefined
	tok->is_operator = NULL;
	tok->is_delimited = false;
	head = tok;
	i = 0;

	// Applies basic tokenization rules in order from POSIX standard
	while (prompt[i])
	{
		// printf("ft_tokenize while loop: i == %d, prompt[i] : %c\n", i, prompt[i]);
		if (ft_previous_char_is_undelimited_operator(tok))
		{
			i += ft_continue_operator_token(prompt, i, &tok);
		}
		else if (ft_is_operator_character(prompt[i])) // && tok->is_quoted == false => handle quotes later
		{
			i += ft_new_operator_token(prompt, i, &tok);
		}
		else if (ft_is_blank(prompt[i])) 
		{
			i += ft_tokenize_blank(&tok);
		}
		else if (ft_previous_char_part_of_word(tok)) // n.b.: is_delimited was added
		{
			i += ft_append_char_to_word(&tok, prompt[i]);
		}
		else
		{
			i += ft_new_word(&tok, prompt[i]);
		}
	}
	if (!prompt[i]) // empty prompt, or '\0' => maybe EOF ?
	{
		tok = ft_tokenize_end_of_input(tok);
	}
	ft_print_all_token_strings(&head);
	return (head);
}
