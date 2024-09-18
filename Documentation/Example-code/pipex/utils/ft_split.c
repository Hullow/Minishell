/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:25:29 by cmegret           #+#    #+#             */
/*   Updated: 2024/04/05 14:24:30 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*s)
	{
		if (trigger == 0 && *s != c)
		{
			trigger = 1;
			i++;
		}
		else if (*s == c)
			trigger = 0;
		s++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

/**
 * @brief Splits a string into an array of substrings
 * based on a delimiter character.
 * 
 * @param s The string to split.
 * @param c The delimiter character.
 * @return An array of substrings, or NULL if the allocation fails.
 */
char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	i;
	size_t	j;
	int		index;

	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (NULL);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

/* #include <stdio.h>

int main()
{
    const char *str = "Ceci est un exemple de fonction ft_split";
    char c = ' '; // Caractère de délimitation

    char **result = ft_split(str, c);

    if (result) {
        for (int i = 0; result[i] != NULL; i++) {
            printf("Mot %d : %s\n", i, result[i]);
            free(result[i]);
        }
        free(result);
    } else {
        printf("La fonction ft_split a renvoyé NULL.\n");
    }

    return 0;
} */