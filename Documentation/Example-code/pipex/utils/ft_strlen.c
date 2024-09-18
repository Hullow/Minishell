/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:37:09 by cmegret           #+#    #+#             */
/*   Updated: 2023/10/09 12:37:09 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * @brief Calculates the length of the given string.
 *
 * @param s The string to calculate the length of.
 *
 * @return The length of the string.
 */
size_t	ft_strlen(const char *s)
{
	unsigned int	size;

	size = 0;
	while (s[size])
		size++;
	return (size);
}
