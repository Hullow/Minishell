/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:00:54 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/14 20:33:36 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// frees our linked list of tokens, and when it exists, each token string
void	ft_free_token_list(t_token *tok)
{
	t_token		*temp;
	t_expand	*temp_expand;

	if (!tok)
		return ;
	while (tok)
	{
		temp = tok;
		tok = tok->next;
		if (temp->str)
			free(temp->str);
		while (temp->to_expand)
		{
			temp_expand = temp->to_expand;
			temp->to_expand = temp->to_expand->next;
			free(temp_expand);
		}
		free(temp);
	}
}
