/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:48:17 by francis           #+#    #+#             */
/*   Updated: 2024/07/19 16:19:55 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	is_blank(char c)
{
	if (c == ' ' || c == '\t'
		|| c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

void	ft_tokenizer(char *prompt)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (prompt[i])
	{
		if (is_quote(prompt[i]))
			in_quote = !in_quote;
		if (is_blank(prompt[i]) && in_quote == 0)
		{
			i++;
			continue ;
		}
		i++;
	}
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
