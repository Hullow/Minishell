/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:48:17 by francis           #+#    #+#             */
/*   Updated: 2024/09/10 18:06:01 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;

	(void)argc;
	(void)argv;
	while ((prompt = readline("Minishell : ")) != NULL)
	{
		if (*prompt) // verify if chain is not empty
		{
			add_history(prompt); // Move it later when here doc will be implemented, to avoid to add the here doc in the history
			(void)envp;
			ft_print_token_type(ft_parse_operators(ft_tokenize(prompt))); // tokenizes the prompt, parse tokens to find operator tokens, and prints the assigned type of each token (if any)
			execute_cmd(ft_assign_command_sequence(ft_tokenize(prompt)), envp);	// tokenizes the prompt, copies the tokens to a command struct to allow for execution (n.b.: only tokens of type WORD, no operators, etc.)
		}
		// if (i % 5 == 0) // clean history
		// 	rl_clear_history();

		free(prompt); // free the memory allocated by readline
	}
	return (0);
}
