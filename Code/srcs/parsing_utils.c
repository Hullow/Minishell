/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:28:47 by cmegret           #+#    #+#             */
/*   Updated: 2024/08/15 14:30:27 by cmegret          ###   ########.fr       */
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
};