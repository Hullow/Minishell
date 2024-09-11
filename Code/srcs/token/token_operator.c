/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:27:19 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/06 17:32:20 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

static int	ft_is_double_greater(char *prompt, int i, struct s_token **tok)
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

static int	ft_is_double_less(char *prompt, int i, struct s_token **tok)
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

int	ft_continue_operator_token(char *prompt, int i, struct s_token **tok)
{
	if (ft_strlen((*tok)->str) != 1)
		(*tok)->is_delimited = true;
	else if (ft_is_double_greater(prompt, i, tok))
		return (1);
	else if (ft_is_double_less(prompt, i, tok))
		return (1);
	else
		(*tok)->is_delimited = true;
	return (0);
}

static void	ft_set_operator_token(char c, struct s_token **tok)
{
	if (c == '>')
		(*tok)->str = ft_strdup(">");
	else if (c == '<')
		(*tok)->str = ft_strdup("<");
	else if (c == '|')
		(*tok)->str = ft_strdup("|");
	(*tok)->is_operator = true;
	(*tok)->is_delimited = false;
	(*tok)->next = NULL;
}

int	ft_new_operator_token(char *prompt, int i, struct s_token **tok)
{
	(*tok) = ft_create_new_token(*tok);
	ft_set_operator_token(prompt[i], tok);
	return (1);
}
