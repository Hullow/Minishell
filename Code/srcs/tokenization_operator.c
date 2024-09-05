/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_operator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 09:23:27 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/04 09:24:17 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

int	ft_is_operator_character(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	ft_previous_char_is_undelimited_operator(struct s_token *tok)
{
	if (tok->str && tok->is_operator == true && tok->is_delimited == false)
		return (1);
	else
		return (0);
}

int	ft_continue_operator_token(char *prompt, int i, struct s_token **tok)
{
	if (ft_strlen((*tok)->str) != 1)
		(*tok)->is_delimited = true;
	else if (prompt[i] == '>' && prompt[i - 1] == '>'
		&& (*tok)->is_quoted == false)
	{
		free((*tok)->str);
		(*tok)->str = ft_strdup(">>");
		(*tok)->type = REDIR_APPEND;
		(*tok)->is_delimited = true;
		return (1);
	}
	else if (prompt[i] == '<' && prompt[i - 1] == '<'
		&& (*tok)->is_quoted == false)
	{
		free((*tok)->str);
		(*tok)->str = ft_strdup("<<");
		(*tok)->type = REDIR_HEREDOC;
		(*tok)->is_delimited = true;
		return (1);
	}
	else
		(*tok)->is_delimited = true;
	return (0);
}

int	ft_new_operator_token(char *prompt, int i, struct s_token **tok)
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
