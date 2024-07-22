/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:48:17 by francis           #+#    #+#             */
/*   Updated: 2024/07/19 16:55:21 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

int	is_operator(struct token *tok)
{
	if (tok == NULL)
		return (0);
	if (tok->type > 1)
		return (1);
	else
		return (0);
}

int	ft_is_end_of_input(char character)
{
	if (character == '\0')
		return (1);
	else if (character == EOF)
		return (1);
	else
		return (0);
}

int	ft_tokenize_end_of_input(char *prompt, struct token *tok)
{
	if (tok)
	{
		tok->is_delimited = 1;
		return (1);
	}
	else
	{
		tok = malloc (1 * sizeof(struct token));
		tok->str = malloc (sizeof(char));
		tok->str = {'\0'}; // ft_strdup instead ?
		tok->type = END_OF_INPUT;
		tok->is_delimited = 1;
		tok->is_operator = 0;
		tok->is_quoted = 0;
	}
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
int	ft_previous_char_operator(char *prompt, int i, struct token *tok)
{
	if (tok && tok->is_operator == true && tok->is_delimited == false)
	{
		if (ft_strlen(tok->str) != 1) // if token was of length > 1, the current character cannot be used with the previous characters to form an operator, because or only multi-character operators are '>>' and '<<'
			tok->is_delimited = 1; // therefore: apply rule 2.2.2.3. and delimit operator containing previous token
		else if (prompt[i] == '>' && prompt[i - 1] == '>'
			&& tok->is_quoted == false) // only '>' in the operator token, we can form a '>>' with it
		{
			free(tok->str);
			tok->str = ft_strdup(">>");
			tok->type = REDIR_APPEND; // or do this later, when token is delimited ?
			return (1);
		}
		else if (prompt[i] == '<' && prompt[i - 1] == '<' && tok->is_quoted == false) // only '>' in the operator token, we can form a '>>' with it
		{
			free(tok->str);
			tok->str = ft_strdup("<<");
			tok->type = REDIR_HEREDOC;  // or do this later, when token is delimited ?
			return (1);
		}
		else
			tok->is_delimited = 1;
			// => need to create a new operator token ? no
	}
	return (0);
}

// ##### 2.2.2.6. New operator token
// IF
// - current character is unquoted
// - current character can be used as the first character of a new operator
//
// => delimit the current token, if any<br>
// => use the current character as the beginning of the next (operator) token
struct token	*ft_new_operator_token(char *prompt, int i, struct token *tok)
{
	struct token	*newtoken;

	newtoken = NULL;
	if (tok->is_quoted == false && (prompt[i] == '>' || & prompt[i] == '<'))
	{
		tok->is_delimited = 1;
		newtoken = malloc(sizeof(struct token));
		tok->str = ft_strdup(prompt[i]);
		tok->is_delimited = 1;
		tok->is_operator = 1;
		tok->is_quoted = 0;
	}

}

ft_tokenizer(char *prompt)
{
	int	i;
	struct token tok;

	tok = NULL;
	head = NULL;

	// tok->type = 0;
	// tok->is_delimited = 0;
	// tok->str = NULL;
	
	while(prompt[i]) // Problem: not sure about the sequence of rule application: when to go back to rule 1 ?
	{
		if (ft_is_end_of_input(prompt[i]))
			ft_tokenize_end_of_input(prompt, i, tok);
		else if (i > 0)
			if !ft_previous_char_operator(prompt, i, tok);
				continue;

		}
		else if ()
		else if ()
		else if ()
		else if ()
	}
}

ft_tokenizer(char *prompt)
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
}

int main() {
	char *prompt;
	int i;
	
	i = 0;
	while ((prompt = readline("Minishell : ")) != NULL)
	{
		if (*prompt) // verify if chain is not empty
		{
			add_history(prompt); // Move it later when here doc will be implemented, to avoid to add the here doc in the history
			ft_tokenizer(prompt);
		}
		// if (i % 5 == 0) // clean history 
		// 	rl_clear_history(); 

		free(prompt); // free the memory allocated by readline
		i++;
	}
	return 0;
}
