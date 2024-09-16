/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:28:47 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/14 17:19:56 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

// Counts the number of arguments in our token 
int	ft_count_token_list_args(struct token *tok)
{
	int i;

	i = 0;
	while (tok) // count # of tokens
	{
		i++;
		tok = tok->next;
	}
	return (i);
}