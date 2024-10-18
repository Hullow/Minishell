/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:27:19 by cmegret           #+#    #+#             */
/*   Updated: 2024/10/18 20:14:48 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// creates a redirection append ('>>') operator token
static int	ft_tokenize_redir_append(char *prompt, int i, struct s_token **tok)
{
	if (prompt[i] == '>' && prompt[i - 1] == '>' && (*tok)->is_quoted == false)
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
static int	ft_tokenize_here_doc(char *prompt, int i, struct s_token **tok)
{
	if (prompt[i] == '<' && prompt[i - 1] == '<' && (*tok)->is_quoted == false)
	{
		free((*tok)->str);
		(*tok)->str = ft_strdup("<<");
		(*tok)->type = REDIR_HEREDOC;
		(*tok)->is_delimited = true;
		return (1);
	}
	return (0);
}

// Function for two rules:
// ##### 2.2.2.2. Continued operator token and current character usable
// ##### 2.2.2.3. Continued operator token and current character not usable
int	ft_continue_operator_token(char *prompt, int i, struct s_token **tok)
{
	if (ft_strlen((*tok)->str) != 1)
		(*tok)->is_delimited = true;
	else if (ft_tokenize_redir_append(prompt, i, tok))
		return (1);
	else if (ft_tokenize_here_doc(prompt, i, tok))
		return (1);
	else
		(*tok)->is_delimited = true;
	return (0);
}

// checks if token starts with a '|', '>', or '<' character
// if a pipe character is found, delimit the token and assign the type PIPE
// otherwise, start a new, undelimited and uncategorized operator token
static void	ft_set_operator_token(char c, struct s_token **tok)
{
	if (c == '|')
	{
		(*tok)->str = ft_strdup("|");
		(*tok)->is_delimited = true;
		(*tok)->is_operator = true;
		(*tok)->type = PIPE;
		(*tok)->next = NULL;
		return ;
	}
	else if (c == '>')
		(*tok)->str = ft_strdup(">");
	else if (c == '<')
		(*tok)->str = ft_strdup("<");
	(*tok)->is_operator = true;
	(*tok)->is_delimited = false;
	(*tok)->next = NULL;
}

// Create a new operator token
int	ft_new_operator_token(char *prompt, int i, struct s_token **tok)
{
	(*tok) = ft_create_new_token(*tok);
	ft_set_operator_token(prompt[i], tok);
	return (1);
}
