/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:19:58 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/14 15:47:14 by fallan           ###   ########.fr       */
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
	tok->is_operator = false;
	tok->is_delimited = false;
	tok->is_single_quoted = false;
	tok->is_double_quoted = false;
	return (tok);
}

// Processes the prompt, applying tokenization rules in order
// For debugging:
	// if (*tok && (*tok)->str)
	// 	printf("tok->str: %s; tok->is_delimited: %d\n",
	//     (*tok)->str, (*tok)->is_delimited);
// Order of rules:
// 2.2.2.2. + 2.2.2.2. Continued operator token and current character usable + not usable
// 2.2.2.4. Quotes
// 2.2.2.6. New operator token
// #### 2.2.2.7. Space or tab
// 2.2.2.8. Previous character part of a word
// 2.2.2.10 New word
// N.b.:
//	- 2.2.2.5. Parameter expansion ($) is not handled here but after tokenisation.
// 	- 2.2.2.9. Comment '#': not implemented at all
static int	ft_process_prompt(char *prompt, int i, t_token **tok)
{
	if (ft_previous_char_is_undelimited_operator(*tok))
		return (ft_continue_operator_token(prompt, i, tok));
	else if (ft_is_quote_character(prompt[i]))
		return (ft_mark_token_as_quoted(prompt, i, tok));
	// Missing expansion (rule 5 POSIX) ? => do tests first while looking at requirements
	else if (ft_is_operator_character(prompt[i]) && !(ft_is_quoted(*tok)))
		return (ft_new_operator_token(prompt, i, tok));
	else if (ft_is_blank(prompt[i]) && !(ft_is_quoted(*tok)))
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
	if (!prompt[i]) // probably unnecessary => HEREDOCS though ?
		tok = ft_tokenize_end_of_input(tok);
	return (head);
}
