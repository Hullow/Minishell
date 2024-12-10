/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:41:17 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/10 12:40:58 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Frees a dynamically allocated array of strings.
 * 
 * This function iterates over the array of strings and frees each string,
 * then frees the array itself.
 * 
 * @param array The array of strings to free.
 */
void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/**
 * @brief Extracts a word from a string and updates the index.
 * 
 * This function extracts a word from the given string starting at the current
 * index and updates the index to point to the character after the
 * extracted word.
 * 
 * @param str The input string.
 * @param index A pointer to the current index in the string.
 * @return char* The extracted word.
 */
char	*ft_extract_word(char *str, int *index)
{
	int		start;
	int		len;
	char	*word;

	start = *index;
	len = 0;
	while (str[*index] && str[*index] != '$' && !ft_isspace(str[*index]))
	{
		(*index)++;
		len++;
	}
	word = ft_substr(str, start, len);
	return (word);
}
