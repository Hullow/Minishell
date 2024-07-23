/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:48:17 by francis           #+#    #+#             */
/*   Updated: 2024/07/22 19:37:56 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

void	ft_tokenize(char *prompt);

int main() {
	char *prompt;
	
	while ((prompt = readline("Minishell : ")) != NULL)
	{
		if (*prompt) // verify if chain is not empty
		{
			add_history(prompt); // Move it later when here doc will be implemented, to avoid to add the here doc in the history
			ft_tokenize(prompt);
			printf("ft_strlen of prompt: %zu\n", ft_strlen(prompt));
		}
		// if (i % 5 == 0) // clean history 
		// 	rl_clear_history(); 

		free(prompt); // free the memory allocated by readline
	}
	return 0;
}
