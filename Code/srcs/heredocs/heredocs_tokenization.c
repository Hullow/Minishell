/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_tokenization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:27:25 by fallan            #+#    #+#             */
/*   Updated: 2024/12/13 17:39:26 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// Adapted from ft_process_prompt
// Processes the prompt, applying tokenization rules in order
// For debugging:
	// if (*tok && (*tok)->str)
	// 	printf("tok->str: %s; tok->is_delimited: %d\n",
	//     (*tok)->str, (*tok)->is_delimited);
int	ft_process_heredoc_line(char *prompt, int i, t_token **tok)
{
	if (ft_is_blank(prompt[i]))
		return (ft_tokenize_blank(tok));
	else if (ft_previous_char_part_of_word(*tok))
		return (ft_append_char_to_word(tok, prompt[i]));
	else
		return (ft_new_word(tok, prompt[i]));
}

// Adapted from ft_tokenize
// Breaks the input (prompt) into tokens by calling each tokenization function
// Calls ft_process_prompt in a loop to tokenize the prompt
// Returns a linked list of tokens
void	ft_tokenize_heredoc_line(char *prompt, t_heredoc *heredoc_line)
{
	t_token	*tok;
	int		i;

	tok = ft_init_token();
	if (!tok)
		return ;
	i = 0;
	while (prompt[i])
		i += ft_process_heredoc_line(prompt, i, &tok);
	if (!prompt[i]) // probably unnecessary => HEREDOCS though ?
		tok = ft_tokenize_end_of_input(tok);
	heredoc_line->contents = tok;
	// if !prompt (empty prompt) => tok = NULL?
}
