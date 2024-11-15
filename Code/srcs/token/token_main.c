/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:19:58 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/14 15:34:29 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// Initializes a new token
t_token	*ft_init_token(void)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->next = NULL;
	tok->str = NULL;
	tok->type = 0;
	tok->is_operator = NULL;
	tok->is_delimited = false;
	return (tok);
}

// Processes the prompt, applying tokenization rules in order
static int	ft_process_prompt(char *prompt, int i, t_token **tok)
{
	if (ft_previous_char_is_undelimited_operator(*tok))
		return (ft_continue_operator_token(prompt, i, tok));
	else if (ft_is_operator_character(prompt[i]))
		return (ft_new_operator_token(prompt, i, tok));
	else if (ft_is_blank(prompt[i]))
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

	tok = ft_init_token();
	if (!tok)
		return (NULL);
	head = tok;
	i = 0;
	while (prompt[i])
		i += ft_process_prompt(prompt, i, &tok);
	if (!prompt[i])
		tok = ft_tokenize_end_of_input(tok);
	return (head);
}
