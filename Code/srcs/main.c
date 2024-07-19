/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:48:17 by francis           #+#    #+#             */
/*   Updated: 2024/07/19 16:09:02 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

void	ft_tokenizer(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
		i++;
}

int	main(void)
{
	char	*prompt;

	while (1)
	{
		prompt = readline("Minishell : ");
		if (!prompt)
			break ;
		if (*prompt)
		{
			add_history(prompt);
			ft_tokenizer(prompt);
		}
		free(prompt);
	}
	return (0);
}
