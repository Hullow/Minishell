/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:19:58 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/18 12:08:45 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// frees the linked list of tokens
// and the strings therein
void	ft_free_token_list(t_token *token_list)
{
	t_token	*temp_tok;

	while (token_list)
	{
		temp_tok = token_list;
		token_list = token_list->next;
		if (temp_tok->str)
			free(temp_tok->str);
		free(temp_tok);
	}
}

// Function called with NULL for new_expand
// adds a t_expand to our linked list of expansion checks
// for each token, each '$' is marked as needing an expansion
// with t_expand = true or false
// no return value
void	ft_prepare_expansion(t_token **tok)
{
	t_expand	*head;
	t_expand	*new_expand;

	new_expand = NULL;
	if (!((*tok)->to_expand))
	{
		(*tok)->to_expand = malloc(sizeof(t_expand));
		(*tok)->to_expand->next = NULL;
		head = (*tok)->to_expand;
	}
	else
	{
		head = (*tok)->to_expand;
		while ((*tok)->to_expand->next)
			(*tok)->to_expand = (*tok)->to_expand->next;
		new_expand = malloc(sizeof(t_expand));
		new_expand->next = NULL;
		(*tok)->to_expand->next = new_expand;
		(*tok)->to_expand = (*tok)->to_expand->next;
	}
	if ((*tok)->is_single_quoted)
		(*tok)->to_expand->check = false;
	else
		(*tok)->to_expand->check = true;
	(*tok)->to_expand = head;
}

// Processes the prompt, applying tokenization rules in order
// For debugging:
	// if (*tok && (*tok)->str)
	// 	printf("tok->str: %s; tok->is_delimited: %d\n",
	//     (*tok)->str, (*tok)->is_delimited);
// Order of rules:
// 2.2.2.2. + 2.2.2.3.:
//  Continued operator token and current character usable + not usable
// 2.2.2.4. Quotes
// 2.2.2.6. New operator token
// #### 2.2.2.7. Space or tab
// 2.2.2.8. Previous character part of a word
// 2.2.2.10 New word
// N.b.:
// -2.2.2.5. Parameter expansion ($) is not handled here but after tokenisation
// -2.2.2.9. Comment '#': not implemented at all
int	ft_process_prompt(char *prompt, int i, t_token **tok)
{
	if (ft_is_dollar_sign(prompt[i]))
	{
		if ((*tok)->is_delimited)
			*tok = ft_add_token_to_list(*tok, WORD);
		ft_prepare_expansion((tok));
	}
	if (ft_previous_char_is_undelimited_operator(*tok))
		return (ft_continue_operator_token(prompt, i, tok));
	else if (ft_is_quote_character(prompt[i]))
		return (ft_handle_quote_tokenization(prompt[i],
				(*tok)->is_single_quoted, (*tok)->is_double_quoted, tok));
	else if (ft_is_operator_character(prompt[i])
		&& !(ft_token_has_open_quote(*tok)))
		return (ft_new_operator_token(prompt, i, tok));
	else if (ft_is_blank(prompt[i]) && !(ft_token_has_open_quote(*tok)))
		return (ft_tokenize_blank(tok));
	else if (ft_previous_char_part_of_word(*tok))
		return (ft_append_char_to_word(tok, prompt[i]));
	else
		return (ft_new_word(tok, prompt[i]));
}

// Breaks the input (prompt) into tokens by calling each tokenization function
// Calls ft_process_prompt in a loop to tokenize the prompt
// Returns a linked list of tokens
t_token	*ft_tokenize(char *prompt)
{
	t_token	*tok;
	t_token	*head;
	int		i;

	tok = ft_create_token(UNKNOWN_TYPE);
	if (!tok)
		return (NULL);
	head = tok;
	i = 0;
	while (prompt[i])
		i += ft_process_prompt(prompt, i, &tok);
	if (!prompt[i])
		tok = ft_tokenize_end_of_input(tok);
	ft_set_empty_token_strings(head);
	if (ft_check_open_quote(head))
		return (NULL);
	return (head);
}
