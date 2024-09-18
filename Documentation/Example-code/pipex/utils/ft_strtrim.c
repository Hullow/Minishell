/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:26:28 by cmegret           #+#    #+#             */
/*   Updated: 2024/04/05 14:29:18 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * @brief Allocates and returns a copy of the string given as argument
 * without whitespaces at the beginning and the end of the string.
 *
 * @param s The string to trim.
 * @param set The set of characters to trim.
 *
 * @return The trimmed string, or NULL if the allocation fails.
 */

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*new_str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	new_str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, &s1[start], end - start + 1);
	return (new_str);
}
