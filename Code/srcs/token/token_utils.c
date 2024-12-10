/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:00:54 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/10 19:03:37 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// frees the token and if it exists, the token string
void	ft_free_token(t_token *tok)
{
	if (!tok)
		return ;
	if (tok->str)
		free(tok->str);
	free(tok);
}
