/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:28:47 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/10 18:12:14 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

// Counts the number of arguments in our token 
int	ft_count_token_list_args(struct token *tok)
{
	int i;

	i = 0;
	while (tok) // count # of tokens
	{
		i++;
		tok = tok->next;
	}
	return (i);
}

// Prints the assigned type (if any) of each token in our linked list of tokens
void	ft_print_token_type(struct token *head)
{
	const char *token_type_strings[9] = {
	"UNDEFINED TOKEN",
    "WORD",
    "NEWLINE",
    "REDIR_INPUT",
    "REDIR_OUTPUT",
    "REDIR_APPEND",
    "REDIR_HEREDOC",
    "PIPE",
    "END_OF_INPUT"};

	while (head)
	{
		if (head->str && head->type)
			printf("string: %s | token type: %s\n", head->str, token_type_strings[head->type]);
		else
		{
			printf("type or string not found: ");
			if (head->type)
				printf("head-type: %s, head->str not found\n", token_type_strings[head->type]);
			if (head->str)
				printf("head-str: %s, head->type not found\n", head->str);
			else
				printf("nor head->str nor head-type found\n");
		}
		head = head->next;
	}
}