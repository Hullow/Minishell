/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:48:17 by francis           #+#    #+#             */
/*   Updated: 2024/08/15 14:03:13 by cmegret          ###   ########.fr       */
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
			// ft_parse(ft_tokenize(prompt));
			ft_tokenization_checker(ft_parse_operators(ft_tokenize(prompt)));
			execute_cmd(ft_parse(ft_tokenize(prompt)), envp);
		}
		// if (i % 5 == 0) // clean history 
		// 	rl_clear_history();

		free(prompt); // free the memory allocated by readline
	}
	return 0;
}
