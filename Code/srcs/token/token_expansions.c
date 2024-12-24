/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:53:45 by francis           #+#    #+#             */
/*   Updated: 2024/12/24 15:27:20 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// si '$' est seul, suivi de ' ' ou '\0', il est à prendre littéralement
//		=> on retourne 0 (pas d'expansion)
// et pour les $ à expandre en string vide, comme $"", on retourne 1 (expansion)
// pour le reste, on retourne 2+ (pour $a: 2; pour $ab: 3, etc.)
//
// n.b.: si il y a quelque chose dans les guillemets,
// par exemple si on a {echo $"USER"} => le $ est ignoré aussi,
// pas d'expansion comme $USER
int	ft_count_size_to_expand(char *prompt, int i)
{
	int	size_to_expand;

	if ((ft_is_blank(prompt[i + 1]) || !prompt[i + 1]))
		return (0);
	size_to_expand = 1;
	i++;
	while (prompt[i])
	{
		if (!ft_isalnum(prompt[i])
			&& prompt[i] != '_' && prompt[i] != '?')
			break ;
		size_to_expand++;
		i++;
	}
	return (size_to_expand);
}

// mallocs a new expansion node to the expansion list of the token
// returns the head of the expansion list
t_expand	*ft_add_expansion_value(t_token **tok)
{
	t_expand	*head;
	t_expand	*new_expand;

	new_expand = NULL;
	if (!((*tok)->to_expand))
	{
		(*tok)->to_expand = malloc(sizeof(t_expand));
		(*tok)->to_expand->next = NULL;
		head = (*tok)->to_expand;
	}
	else
	{
		head = (*tok)->to_expand;
		while ((*tok)->to_expand->next)
			(*tok)->to_expand = (*tok)->to_expand->next;
		new_expand = malloc(sizeof(t_expand));
		new_expand->next = NULL;
		(*tok)->to_expand->next = new_expand;
		(*tok)->to_expand = (*tok)->to_expand->next;
	}
	return (head);
}

// Expansion preparation – Principles:
// - $ alone (followed by ' ' or '\0')
// is a word => no expansion, take it literally
// - $ at the start of a word marks the start of a parameter,
// so long as characters are valid
// n.b.: if the character immediately after $ is not valid (e.g. {"} or {'})
// => we have an empty parameter $ (but not a word),
// which we must expand to {} (empty)
//
// on est entre single quote = pas d'expansion, on prend tout littéral
// on est entre double quote => on commence à $ et on avance
// jusqu'à ce qu'on ait plus de caractères valides (size_to_expand)
// on est pas entre quote => same as double quote
// si $ est le dernier caractère du prompt, en clair si 
void	ft_prepare_expansion(char *prompt, int i, t_token **tok)
{
	t_expand	*head;

	head = ft_add_expansion_value(tok);
	while ((*tok)->to_expand->next)
		(*tok)->to_expand = (*tok)->to_expand->next;
	(*tok)->to_expand->size_to_expand
		= ft_count_size_to_expand(prompt, i);
	if ((*tok)->is_single_quoted)
		(*tok)->to_expand->check = false;
	else
		(*tok)->to_expand->check = true;
	if ((*tok)->to_expand->size_to_expand == 0)
		(*tok)->to_expand->check = false;
	(*tok)->to_expand = head;
}
