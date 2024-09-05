/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_blank.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 09:22:41 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/04 09:22:49 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

// checks if character is a blank (space or tab)
int	ft_is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	ft_tokenize_blank(struct s_token **tok)
{
	if ((*tok)->str)
		(*tok)->is_delimited = true;
	return (1);
}
