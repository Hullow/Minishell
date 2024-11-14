/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_expension.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:19:58 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/14 11:21:33 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// Ajoutez cette fonction pour l'expansion de fichier
void ft_pathname_expansion(t_token **tokens)
{
	t_token *current = *tokens;
	while (current)
	{
		if (ft_is_pathname_expansion_needed(current->str))
		{
			// Implémentez la logique d'expansion de fichier ici
			char **expanded_paths = ft_expand_pathname(current->str);
			if (expanded_paths)
			{
				// Remplacez le token actuel par les chemins expansés
				ft_replace_token_with_expanded_paths(&current, expanded_paths);
			}
		}
		current = current->next;
	}
}

int ft_is_pathname_expansion_needed(char *value)
{
	return (ft_strchr(value, '*') != NULL || ft_strchr(value, '?') != NULL);
}

char **ft_expand_pathname(char *pattern)
{
	// Implémentez la logique pour obtenir les chemins correspondants au pattern
	// Utilisez opendir, readdir, et closedir pour parcourir les fichiers
	DIR *dir;
	struct dirent *entry;
	char **paths = NULL;
	int count = 0;

	dir = opendir(".");
	if (!dir)
		return NULL;

	while ((entry = readdir(dir)) != NULL)
	{
		if (ft_match_pattern(entry->d_name, pattern))
		{
			paths = realloc(paths, sizeof(char *) * (count + 2));
			paths[count] = ft_strdup(entry->d_name);
			count++;
		}
	}
	closedir(dir);

	if (paths)
		paths[count] = NULL;

	return paths;
}

int ft_match_pattern(const char *str, const char *pattern)
{
    while (*pattern)
    {
        if (*pattern == '*')
        {
            pattern++;
            if (!*pattern)
                return 1;
            while (*str)
            {
                if (ft_match_pattern(str, pattern))
                    return 1;
                str++;
            }
            return 0;
        }
        else if (*pattern == '?')
        {
            if (!*str)
                return 0;
        }
        else if (*str != *pattern)
        {
            return 0;
        }
        str++;
        pattern++;
    }
    return (*str == '\0');
}

void	ft_replace_token_with_expanded_paths(t_token **current, char **expanded_paths)
{
	t_token	*prev;
	t_token	*new_token;
	int		i;

	prev = *current;
	i = 0;
	// Remplace le contenu du token actuel par le premier chemin expansé
	free((*current)->str);
	(*current)->str = expanded_paths[i];
	i++;
	// Insère les nouveaux tokens après le token actuel
	while (expanded_paths[i])
	{
		new_token = ft_init_token();
		new_token->str = expanded_paths[i];
		new_token->next = (*current)->next;
		(*current)->next = new_token;
		*current = new_token;
		i++;
	}
	// Repositionne le pointeur current sur le dernier token inséré
	*current = prev;
}
