/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:01:55 by francis           #+#    #+#             */
/*   Updated: 2024/12/15 13:39:46 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// returns the number of tokens in our linked list
int	ft_count_tokens(t_token *tok)
{
	int	i;

	i = 0;
	if (!tok)
		return (0);
	while (tok)
	{
		i++;
		tok = tok->next;
	}
	return (i);
}

// traverses the linked list of tokens and returns the last token
struct	s_token	*ft_last_token(t_token *tok)
{
	if (!tok || !tok->next)
		return (tok);
	while (tok->next)
		tok = tok->next;
	return (tok);
}

// Traverses the linked list of tokens and prints each token's string, type, and quote status (if any) 
void	ft_print_token_types_and_quote_status(t_token *tok)
{
	t_token		*iterator;
	const char	*token_type_strings[10] = {
		"UNKNOWN TOKEN TYPE", "WORD", "REDIR_INPUT", "REDIR_OUTPUT",
		"REDIR_APPEND", "REDIR_HEREDOC", "PIPE", "END_OF_INPUT"
	};

	printf("***TOKENS***\n");
	iterator = tok;
	while (iterator)
	{
		if (iterator->str)
		{
			printf("string: {%s} – token type: %s (%d)", iterator->str,
				token_type_strings[iterator->type], iterator->type);
			if (iterator->is_between_quotes)
				printf(" – (quoted)\n");
			else
				printf(" – (unquoted)\n");
		}
		else
		{
			printf("type or string not found: ");
			if (iterator->type)
				printf("iterator-type: %s, iterator->str not found\n",
					token_type_strings[iterator->type]);
			if (iterator->str)
				printf("iter-str: %s, iter->type not found\n", iterator->str);
			else
				printf("nor iterator->str nor iterator-type found\n");
		}
		iterator = iterator->next;
	}
	printf("************\n");
}

void	ft_print_required_expansions(t_token *tok)
{
	t_expand	*expand;
	
	printf("Parameters to expand:");
	while (tok)
	{
		if (!(tok->str))
			return ;
		expand = tok->to_expand;
		printf("\nToken {%s}: ", tok->str);
		while (expand)
		{
			if (expand->check == true)
				printf("expand - ");
			else
				printf("don't - ");
			expand = expand->next;
		}
		printf("\n");
		tok = tok->next;
	}
}
