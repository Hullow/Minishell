/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:53:45 by francis           #+#    #+#             */
/*   Updated: 2024/12/21 15:55:24 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// si '$' est seul, suivi de ' ' ou '\0', il est à prendre littéralement
//		=> on retourne 0 (pas d'expansion)
// et pour les $ à expandre en string vide, comme $"", on retourne 1 (expansion)
// pour le reste, on retourne 2+ (pour $a: 2; pour $ab: 3, etc.)
//
// n.b.: si il y a quelque chose dans les guillemets, par exemple si on a {echo $"USER"} => le $ est ignoré aussi, pas d'expansion comme $USER
int	ft_count_size_to_expand(char *prompt, int i)
{
	int	size_to_expand;
	
	if ((ft_is_blank(prompt[i + 1]) || !prompt[i + 1]))// ifs '$' is followed by ' ' or '\0'
		return (0);  // `echo $` => `$` => no expansion, literal value
	size_to_expand = 1;
	i++;
	// Examples:
	// 	- {echo $""} => `` (empty string); size_to_expand = 1 (vs {echo $ ""})
	//	- echo $"USER" => `USER` ; size_to_expand = 1
	// 	- echo $U"SER" => expand $U + join string "SER" (size_to_expand = 2)
	while (prompt[i])
	{
		if (!ft_isalnum(prompt[i]) && prompt[i] != '_' && prompt[i] != '?') // valid characters for a possible expansion
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
// - $ alone (followed by ' ' or '\0') is a word => no expansion, take it literally
// - $ at the start of a word marks the start of a parameter, so long as characters are valid
// n.b.: if the character immediately after $ is not valid (e.g. {"} or {'})
// => we have an empty parameter $ (but not a word), which we must expand to {} (empty)
//
// on est entre single quote = pas d'expansion, on prend tout littéral
// on est entre double quote => on commence à $ et on avance jusqu'à ce qu'on ait plus de caractères valides (size_to_expand)
// on est pas entre quote => same as double quote
// si $ est le dernier caractère du prompt, en clair si 
void	ft_prepare_expansion(char *prompt, int i, t_token **tok)
{
	t_expand	*head;

	head = ft_add_expansion_value(tok); // mallocs a new expansion to the expansion list of the token and returns the head of the expansion list
	while ((*tok)->to_expand->next)
		(*tok)->to_expand = (*tok)->to_expand->next;
	(*tok)->to_expand->size_to_expand = ft_count_size_to_expand(prompt, i); 
	if ((*tok)->is_single_quoted)
		(*tok)->to_expand->check = false; // echo '$U"SER"'
	else
		(*tok)->to_expand->check = true;
	if ((*tok)->to_expand->size_to_expand == 0) // echo hello world $
		(*tok)->to_expand->check = false;
	(*tok)->to_expand = head;
}
