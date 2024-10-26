/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:00:54 by cmegret           #+#    #+#             */
/*   Updated: 2024/10/26 19:09:37 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// traverses the linked list of tokens and returns the last token
struct	s_token *ft_last_token(struct s_token *tok)
{
	if (!tok || !tok->next)
		return (tok);
	while (tok->next)
		tok = tok->next;
	return (tok);
}

// returns the number of tokens in our linked list
int	ft_count_tokens(struct s_token *tok)
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

// prints each token's contents (tok->str)
void	ft_print_all_token_strings(struct s_token **head)
{
	struct s_token	*iterator;

	iterator = *head;
	while (iterator != 0)
	{
		printf("token: %s\n", iterator->str);
		iterator = iterator->next;
	}
}

// Traverses the linked list of tokens and prints each token's type, if any
void	ft_print_token_types(struct s_token *head)
{
	struct s_token	*iterator;

	iterator = head;
	const char	*token_type_strings[10] = {
		"UNDEFINED TOKEN", "WORD", "REDIR_INPUT", "REDIR_OUTPUT",
		"REDIR_APPEND", "REDIR_HEREDOC", "PIPE", "END_OF_INPUT"
	};
	while (iterator)
	{
		if (iterator->str && iterator->type)
			printf("string: {%s} – token type: %s (%d)\n",
				iterator->str, token_type_strings[iterator->type], iterator->type);
		else
		{
			printf("type or string not found: ");
			if (iterator->type)
				printf("iterator-type: %s, iterator->str not found\n",
					token_type_strings[iterator->type]);
			if (iterator->str)
				printf("iterator-str: %s, iterator->type not found\n", iterator->str);
			else
				printf("nor iterator->str nor iterator-type found\n");
		}
		iterator = iterator->next;
	}
}

// frees the token and if it exists, the token string
void	ft_free_token(struct s_token *tok)
{
	if (!tok)
		return ;
	if (tok->str)
		free(tok->str);
	free(tok);
}