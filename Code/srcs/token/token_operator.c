/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:27:19 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/15 11:32:57 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// creates a redirection append ('>>') operator token
static int	ft_tokenize_redir_append(char *prompt, int i, t_token **tok)
{
	if (prompt[i] == '>' && prompt[i - 1] == '>' && ft_token_has_open_quote(*tok) == false)
	{
		free((*tok)->str);
		(*tok)->str = ft_strdup(">>");
		(*tok)->type = REDIR_APPEND;
		(*tok)->is_delimited = true;
		return (1);
	}
	return (0);
}

// creates a here document ('<<') operator token
static int	ft_tokenize_here_doc(char *prompt, int i, t_token **tok)
{
	if (prompt[i] == '<' && prompt[i - 1] == '<' && ft_token_has_open_quote(*tok) == false)
	{
		free((*tok)->str);
		(*tok)->str = ft_strdup("<<");
		(*tok)->type = REDIR_HEREDOC;
		(*tok)->is_delimited = true;
		return (1);
	}
	return (0);
}

// Function for two rules: 2.2.2.2. and 2.2.2.3. (see Shell-functioning.md)
// How it works:
// - If current token has more than one character in it (ft_strlen), it delimits
// 	it because it has already been checked to be an operator token previously
// - If we can tokenize an append or a heredoc, we do (n.b.: the presence of 
// quotes is checked by each function ft_tokenize*)
// - Else, we delimit the token (creating a REDIR_OUTPUT or REDIR_INPUT token)
// ##### 2.2.2.2. Continued operator token and current character usable
// IF
// - current character not quoted
// - previous character used as part of an operator
//  (n.b.: only >> or << in our case)
// => use character as part of that (operator) token
//
// ##### 2.2.2.3. Continued operator token and current character not usable
// IF
// - previous character used as part of an operator
// - current character cannot be used with the previous characters to form an operator
//  e.g. >> + > => no implementation of >>> in our case
// => delimit the operator containing the previous character
int	ft_continue_operator_token(char *prompt, int i, t_token **tok)
{
	if (ft_strlen((*tok)->str) > 1)
		(*tok)->is_delimited = true;
	else if (ft_tokenize_redir_append(prompt, i, tok))
		return (1);
	else if (ft_tokenize_here_doc(prompt, i, tok))
		return (1);
	else
	{
		(*tok)->is_delimited = true;
		if (!(*tok)->str)
		{
			printf("tokenization error: token string not found \
			(ft_continue_operator_token)\n");
			return (0); // careful w/ ret.value here, used to process the prompt
		}
		if (!(ft_strncmp((*tok)->str, ">", 2)))
			(*tok)->type = REDIR_OUTPUT;
		else if (!(ft_strncmp((*tok)->str, "<", 2)))
			(*tok)->type = REDIR_INPUT;
		else if (!(ft_strncmp((*tok)->str, "|", 2)))
			(*tok)->type = PIPE;
	}
	return (0);
}

// Function 1 for rule 2.2.2.6.
// Create a new operator token
// returns 1
//
// ##### 2.2.2.6. New operator token
// IF
// - current character is unquoted
// - current character can be used as the first character of a new operator
// => delimit the current token, if any
// => use the current character as the beginning of the next (operator) token
//
// Function 2 for rule 2.2.2.6. (see ft_new_operator_token)
// checks if token starts with a '|', '>', or '<' character
// if a pipe character is found, delimit the token and assign the type PIPE
// otherwise, start a new, undelimited and uncategorized operator token
int	ft_new_operator_token(char *prompt, int i, t_token **tok)
{
	(*tok) = ft_add_token_to_list(*tok, UNKNOWN_TYPE);
	if (prompt[i] == '|') // previously ft_set_operator_token(prompt[i], tok);
	{
		(*tok)->str = ft_strdup("|");
		(*tok)->is_delimited = true;
		(*tok)->type = PIPE;
	}
	else if (prompt[i] == '>')
		(*tok)->str = ft_strdup(">");
	else if (prompt[i] == '<')
		(*tok)->str = ft_strdup("<");
	(*tok)->is_operator = true;
	(*tok)->next = NULL;
	return (1);
}
