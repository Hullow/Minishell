/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:48:17 by francis           #+#    #+#             */
/*   Updated: 2024/07/19 14:38:01 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

int	is_operator(struct token *tok)
{
	if (tok == NULL)
		return (0);
	if (tok->type > 1)
		return (1);
	else
		return (0);
}

int	ft_is_end_of_input(char character)
{
	if (character == '\0')
		return (1);
	else if (character == EOF)
		return (1);
	else
		return (0);
}

ft_tokenize_end_of_input(char *prompt, struct token *tok)
{
	if (tok)
		tok->is_delimited = 1;
	else
	{
		tok = malloc (1 * sizeof(struct token));
		tok->str = {'\0'};
		tok->type = END_OF_INPUT;
		tok->is_delimited = 1;
	}
}

ft_tokenizer(char *prompt)
{
	int	i;
	struct token tok;

	tok = NULL;
	// tok->type = 0;
	// tok->is_delimited = 0;
	// tok->str = NULL;
	while(prompt[i])
	{
		if (ft_is_end_of_input(prompt[i]))
			ft_tokenize_end_of_input(prompt, i, tok);
		else if (i > 0)
		{
			prompt[i - 1]

		}
		else if ()
		else if ()
		else if ()
		else if ()
	}
}

ft_tokenizer(char *prompt)
{
	int	i;
	int start;
	int end;

	while(prompt[i])
	{
		if (ft_is_end_of_input(prompt[i]))
			ft_tokenize_end_of_input(prompt, i, tok);
		// If the prompt[i] is a space, we skip it
		if (is_blank(prompt[i]))
			i++;
		
	}
}

int main() {
	char *prompt;
	int i;
	
	i = 0;
	while ((prompt = readline("Minishell : ")) != NULL)
	{
		if (*prompt) // verify if chain is not empty
		{
			add_history(prompt); // Move it later when here doc will be implemented, to avoid to add the here doc in the history
			ft_tokenizer(prompt);
		}
		// if (i % 5 == 0) // clean history 
		// 	rl_clear_history(); 

		free(prompt); // free the memory allocated by readline
		i++;
	}
	return 0;
}
