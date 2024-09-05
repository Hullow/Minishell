/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:47:54 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/04 09:48:15 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

static int	handle_operator_token(char *prompt, int i, struct s_token **tok)
{
	if (ft_previous_char_is_undelimited_operator(*tok))
		return (ft_continue_operator_token(prompt, i, tok));
	else if (ft_is_operator_character(prompt[i]))
		return (ft_new_operator_token(prompt, i, tok));
	return (0);
}

static int	handle_blank_token(char *prompt, int i, struct s_token **tok)
{
	if (ft_is_blank(prompt[i]))
		return (ft_tokenize_blank(tok));
	return (0);
}

static int	handle_word_token(char *prompt, int i, struct s_token **tok)
{
	if (ft_previous_char_part_of_word(*tok))
		return (ft_append_char_to_word(tok, prompt[i]));
	else
		return (ft_new_word(tok, prompt[i]));
}

static int	handle_token(char *prompt, int i, struct s_token **tok)
{
	int	increment;

	increment = handle_operator_token(prompt, i, tok);
	if (increment)
		return (increment);
	increment = handle_blank_token(prompt, i, tok);
	if (increment)
		return (increment);
	return (handle_word_token(prompt, i, tok));
}

struct s_token	*ft_tokenize(char *prompt)
{
	struct s_token	*tok;
	struct s_token	*head;
	int				i;

	tok = initialize_token();
	if (!tok)
		return (NULL);
	head = tok;
	i = 0;
	while (prompt[i])
		i += handle_token(prompt, i, &tok);
	if (!prompt[i])
		tok = ft_tokenize_end_of_input(tok);
	ft_print_all_token_strings(&head);
	return (head);
}
