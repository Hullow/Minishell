/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:23:50 by fallan            #+#    #+#             */
/*   Updated: 2024/11/20 16:03:53 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	if (s1 == NULL && s2 == NULL)
		return (0);
	else if (s1 == NULL)
		return (-1);
	else if (s2 == NULL)
		return (1);
	while (n > 0 && *s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/* #include <string.h>
int	test(const char *s1, const char *s2, size_t n)
{
	char	*string1;
	char	*string2;
	int result;
	int benchmark;

	string1 = (char *) s1;
	string2 = (char *) s2;

	result = ft_strncmp(string1, string2, n);
	benchmark = strncmp(string1, string2, n);

	if (result == benchmark)
		printf("return value is the same as strncmp\n");
	else
		printf("ft_strncmp's return value %d\
		is not the same as strncmp: %d\n", result, benchmark);
	return (0);
}

int main(void)
{
	test("1234", "1235", 3);
	test("abcdefgh", "abcdwxyz", 4);
	return(0);
} */