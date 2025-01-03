/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:56:09 by fallan            #+#    #+#             */
/*   Updated: 2025/01/03 18:22:56 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

void	ft_handle_single_quote(t_token **tok, bool double_quoted)
{
	if (!ft_token_has_open_quote(*tok))
		(*tok)->is_single_quoted = true;
	else if (!double_quoted)
		(*tok)->is_single_quoted = false;
	else if ((*tok)->str)
		ft_append_char_to_word(tok, '\'');
	else
		ft_new_word(tok, '\'');
}

// marks the token as quoted:
// if character is a single quote:
//		if not single quoted, mark as single quoted
//		else, mark as not single quoted (close quote)
// same for double quote
// returns 1
//
// n.b.: is_between_quotes is true if any part of the heredoc is between quotes
// e.g the prompt `cat << 'EOF'AA`
// => no expansion even though only part of the delimiter token is quoted
int	ft_handle_quote_tokenization(char c,
	bool single_quoted, bool double_quoted, t_token **tok)
{
	if ((*tok)->is_delimited)
		*tok = ft_add_token_to_list(*tok, WORD);
	if (ft_token_has_open_quote(*tok))
		(*tok)->is_between_quotes = true;
	if (c == '\'')
		ft_handle_single_quote(tok, double_quoted);
	else if (c == '\"')
	{
		if (!ft_token_has_open_quote(*tok))
			(*tok)->is_double_quoted = true;
		else if (double_quoted && !single_quoted)
			(*tok)->is_double_quoted = false;
		else if ((*tok)->str)
			ft_append_char_to_word(tok, '\"');
		else
			ft_new_word(tok, '\"');
	}
	return (1);
}

// checks if our token list ends with open quotes
// if true, prints "open quote!", frees the token list, and returns 1
// else, returns 0
int	ft_check_open_quote(t_token *tok)
{
	t_token	*head;

	head = tok;
	while (tok->next)
		tok = tok->next;
	if (ft_token_has_open_quote(tok))
	{
		printf("open quote !\n");
		ft_free_token_list(head);
		return (1);
	}
	else
		return (0);
}
