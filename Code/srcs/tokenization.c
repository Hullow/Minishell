/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:35:11 by francis           #+#    #+#             */
/*   Updated: 2024/07/23 13:00:47 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

int	ft_token_is_operator(struct token *tok)
{
	if (tok == NULL)
		return (0);
	if (tok->type > 1)
		return (1);
	else
		return (0);
}


int	ft_is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	ft_is_end_of_input(char character)
{
	if (character == '\n')
		return (1);
	else if (character == EOF)
		return (1);
	else
		return (0);
}

struct token	*ft_tokenize_end_of_input(struct token *tok)
{
	if (tok)
	{
		tok->is_delimited = 1;
		printf("ft_tokenize_end_of_input: token found\n");
	}
	else
	{
		printf("ft_tokenize_end_of_input: token not found\n");
		tok = malloc (1 * sizeof(struct token));
		if (!tok)
			return (NULL);
		tok->str = ft_strdup("");
		if (tok)
			printf("ft_tokenize_end_of_input: tok exists\n");
		tok->type = END_OF_INPUT;
		tok->is_delimited = 1;
		tok->is_operator = 0;
		tok->is_quoted = 0;
	}
	return (tok);
}

int	ft_previous_char_is_undelimited_operator(struct token *tok)
{
	if (tok->str && tok->is_operator == true && tok->is_delimited == false)
		return (1);
	else
		return (0);
}

// Function for rules:
// ##### 2.2.2.2. Continued operator token and current character usable
// ##### 2.2.2.3. Continued operator token and current character not usable
// IF
// - previous character used as part of an operator 
// - current character can be used with 
// the previous characterS to form an operator
// - current character not quoted
//=> use character as part of that (operator) token
// n.b.: only `>>` or `<<` in our case
//
// returns 1 if the current character was added to the previous (operator) token,
// returns 0 if the previous (operator) character was delimited
int	ft_continue_operator_token(char *prompt, int i, struct token *tok)
{
	if (ft_strlen(tok->str) != 1) // if token was of length > 1, the current character cannot be used with the previous characters to form an operator, because or only multi-character operators are '>>' and '<<'
		tok->is_delimited = true; // therefore: apply rule 2.2.2.3. and delimit operator containing previous token
	else if (prompt[i] == '>' && prompt[i - 1] == '>') // && tok->is_quoted == false)
	// there is only '>' in the operator token => we can form a '>>' with it
	{
		free(tok->str);
		tok->str = ft_strdup(">>");
		tok->type = REDIR_APPEND;
		tok->is_delimited = true; // do this or not ?
		// e.g. `echo "hello" >>> 3` gives the error:
		// => bash: syntax error near unexpected token `>'
		return (1); // because we assigned the character to a token
	}
	else if (prompt[i] == '<' && prompt[i - 1] == '<' && tok->is_quoted == false) // only '>' in the operator token, we can form a '>>' with it
	{
		free(tok->str);
		tok->str = ft_strdup("<<");
		tok->type = REDIR_HEREDOC; // do this or not ?
		tok->is_delimited = true;
		return (1); // because we assigned the character to a token
	}
	else
		tok->is_delimited = 1;
			// => need to create a new operator token ? no
	return (0); // we did not assign the character to a token
}

// ##### 2.2.2.6. New operator token
// IF
// - current character is unquoted
// - current character can be used as the first character of a new operator
//
// => delimit the current token, if any<br>
// => use the current character as the beginning of the next (operator) token
int	ft_new_operator_token(char *prompt, int i, struct token *tok)
{
	struct token	*newtoken;

	newtoken = malloc(sizeof(struct token));
	if (!newtoken)
		return (0);
	if (prompt[i] == '>')
		newtoken->str = ft_strdup(">");
	else if (prompt[i] == '<')
		newtoken->str = ft_strdup("<");
	newtoken->is_operator = true;
	newtoken->is_delimited = true;
	newtoken->next = NULL;
	if (tok->str)
	{
		tok->is_delimited = true;
		tok->next = newtoken;
		tok = tok->next;
	}
	else
		tok = newtoken;
	return (1);
}

int	ft_tokenize_blank(struct token *tok)
{
	if (tok->str)
		tok->is_delimited = true;
	return (1);
}

int	ft_append_char_to_word(struct token *tok, char c)
{
	char *temp;
	char character[2];

	temp = ft_strdup(tok->str);
	printf("ft_append_char_to_word: tok->str : {%s} – temp: {%s}\n", tok->str, temp);
	character[0] = c;
	character[1] = '\0';
	tok->str = ft_strjoin(temp, character);
	free(temp);
	return (1);
}

int	ft_new_word(struct token **tok, char c)
{
	char character[2];

	character[0] = c;
	character[1] = '\0';
	printf("ft_new_word: character: %c\n", c);
	(*tok)->type = WORD;
	(*tok)->str = ft_strdup(character);
	printf("ft_new_word: (*tok)->str: %s\n", (*tok)->str);
	(*tok)->is_delimited = false;
	(*tok)->is_operator = false;
	(*tok)->next = NULL;
	return (1);
}

/* From fdf:

if (node)
{
	node->next = ft_lstnew(ft_fill_pt(split[i], i, j, dimensions));
	node = node->next;
}
else
{
	node = ft_lstnew(ft_fill_pt(split[i], i, j, dimensions));
	head = node;
}
*/

void	ft_print_all_token_strings(struct token **head)
{
	struct token *iterator = *head;

	while (iterator != 0)
	{
		printf("token: %s\n", iterator->str);
		iterator = iterator->next;
	}
}

// Breaks the input (prompt) into tokens
void	ft_tokenize(char *prompt)
{
	struct token 	*tok;
	struct token 	*head;
	int				i;

	tok = malloc(sizeof(struct token *));
	if (!tok)
		return ; // return (NULL);
	tok->str = NULL;
	tok->is_delimited = false;
	tok->is_operator = NULL;
	tok->type = 0;
	tok->next = NULL;
	head = tok;
	i = 0;

	// To do:
	// - linked list of tokens
	// - harmonize ifs and thens
	
	while (prompt[i]) // Problem: not sure about the sequence of rule application: when to go back to rule 1 ?
	{
		if (ft_previous_char_is_undelimited_operator(tok))
		{
			i += ft_continue_operator_token(prompt, i, tok);
			printf("ft_previous_char_is_undelimited_operator: i = %d\n", i);
		}
		else if (prompt[i] == '>' || prompt[i] == '<') // && tok->is_quoted == false => handle quotes later
		{
			i+= ft_new_operator_token(prompt, i, tok);
			printf("ft_new_operator_token: i = %d\n", i);
		}
		else if (ft_is_blank(prompt[i]))
		{
			i += ft_tokenize_blank(tok);
			printf("ft_tokenize_blank: i = %d\n", i);
		}
		else if (tok->type == WORD)
		{
			printf("ft_append_char_to_word: tok->str: %s\n", tok->str);
			i += ft_append_char_to_word(tok, prompt[i]);
			printf("ft_append_char_to_word: i = %d\n", i);
		}
		else
		{
			tok->str = ft_strdup("blabla");
			printf("ft_new_word: tok->str: %s\n", tok->str);
			i += ft_new_word(&tok, prompt[i]);
			printf("ft_new_word: i = %d\n", i);
			printf("ft_new_word: tok->str: %s\n", tok->str);
		}
		// printf("i is: %d\n", i);
		// how to verify if current character is unquoted ?
			// => initialize a token every time, but set the tok->string to NULL
			// => if quotes appear, 
			// linked list of tokens
			// have a "quote" struct that counts how many quotes we are in ?
	}
	if (!prompt[i]) // instead of ft_is_end_of_input
	{
		printf("end of input found\n");
		tok = ft_tokenize_end_of_input(tok);
	}
	if (tok)
		printf("ft_tokenizer: tok created, tok->str: {%s}\n", tok->str);
	else
		printf("ft_tokenizer: tok not found\n");
	ft_print_all_token_strings(&head);
}


/* ft_tokenizer(char *prompt)
{
	int	i;
	int start;
	int end;

	while(prompt[i])
	{
		if (ft_is_end_of_input(prompt[i]))
			ft_tokenize_end_of_input(prompt, i, tok);
		// If the prompt[i] is a space, we skip it
		if (is_blank(prompt[i]))
			i++;
		
	}
} */
