/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:00:54 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/11 11:46:17 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// frees the token 

// frees our linked list of tokens, and when it exists, each token string
void	ft_free_token_list(t_token *tok)
{
	t_token	*temp;
	
	if (!tok)
		return ;
	while (tok)
	{
		temp = tok;
		tok = tok->next;
		if (temp->str)
			free(temp->str);
		free(temp);
	}
}
