/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:37:18 by cmegret           #+#    #+#             */
/*   Updated: 2023/10/09 12:37:18 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * @brief Locate the first occurrence of a character in a string.
 *
 * @param s The string to search.
 * @param c The character to search for.
 *
 * @return A pointer to the located character in the string,
 * or NULL if the character is not found.
 */
char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}

/* #include <stdio.h>

int main() {
    const char *str = "Bonjour, monde";
    int ch = 'u';
    char *result = ft_strchr(str, ch);
    
    if (result != NULL) {
        printf("Le caractere '%c' trouve position : %ld\n", ch, result - str);
    } else {
        printf("Le caractere '%c' n'a pas ete trouve dans la chaine.\n", ch);
    }
    
    return 0;
} */