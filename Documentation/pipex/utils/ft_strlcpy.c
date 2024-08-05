/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:06:36 by cmegret           #+#    #+#             */
/*   Updated: 2024/04/05 14:29:07 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * @brief Copies up to dstsize - 1 characters from the string src to dst, 
 * NUL-terminating the result if dstsize is not 0.
 * 
 * @param dst The destination string.
 * @param src The source string.
 * @param dstsize The size of the destination buffer.
 * 
 * @return The total length of the string it tried to create, 
 * which is the length of src.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (i < dstsize - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}

/* #include <stdio.h>

int main(void)
{
    char dest[15];
    const char src[] = "Hello, World!";

    printf("%zu\n", ft_strlcpy(dest, src, 4));
    printf("%s\n", dest);

    return (0);
} */