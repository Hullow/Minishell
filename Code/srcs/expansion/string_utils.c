/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:41:17 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/10 12:08:03 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// Fonction pour libérer un tableau de chaînes
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

// Fonction pour extraire un mot de la chaîne et mettre à jour l'index
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
