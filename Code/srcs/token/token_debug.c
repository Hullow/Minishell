/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:01:55 by francis           #+#    #+#             */
/*   Updated: 2024/12/14 19:59:08 by fallan           ###   ########.fr       */
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

// prints each token's contents (tok->str)
void	ft_print_all_token_strings(t_token **head)
{
	t_token	*iterator;

	iterator = *head;
	while (iterator != 0)
	{
		printf("token: {%s}\n", iterator->str);
		iterator = iterator->next;
	}
}

// Traverses the linked list of tokens and prints each token's type, if any
void	ft_print_token_types(t_token *head)
{
	t_token		*iterator;
	const char	*token_type_strings[10] = {
		"UNDEFINED TOKEN", "WORD", "REDIR_INPUT", "REDIR_OUTPUT",
		"REDIR_APPEND", "REDIR_HEREDOC", "PIPE", "END_OF_INPUT"
	};

	iterator = head;
	while (iterator)
	{
		if (iterator->str && iterator->type)
			printf("string: {%s} – token type: %s (%d)\n", iterator->str,
				token_type_strings[iterator->type], iterator->type);
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
