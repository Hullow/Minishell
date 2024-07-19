/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:13:16 by fallan            #+#    #+#             */
/*   Updated: 2024/07/19 14:59:41 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	lstsize;

	if (lst)
		lstsize = 1;
	else
		return (0);
	while (lst->next)
	{
		lst = lst->next;
		lstsize++;
	}
	return (lstsize);
}
