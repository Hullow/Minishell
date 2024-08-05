/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:15:27 by cmegret           #+#    #+#             */
/*   Updated: 2024/04/05 14:47:02 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
* @brief Concatenates two strings s1 and s2 into a new string.
 * 
 * @param s1 The first string to concatenate.
 * @param s2 The second string to concatenate.
 * 
 * @return The new string resulting from the concatenation of s1 and s2,
 * or NULL if the allocation fails.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	totalsize;
	char	*newstring;
	int		i;
	int		j;

	totalsize = ft_strlen(s1) + ft_strlen(s2);
	newstring = (char *)malloc(totalsize + 1 * sizeof(char));
	if (newstring == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		newstring[i] = s1[i];
		i++;
	}
	j = i;
	i = 0;
	while (s2[i] != '\0')
	{
		newstring[j] = s2[i];
		i++;
		j++;
	}
	newstring[j] = '\0';
	return (newstring);
}
