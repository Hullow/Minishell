/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:28:03 by fallan            #+#    #+#             */
/*   Updated: 2024/11/01 18:54:10 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// creates a new redirection node
// if no redirection list existing, initialize the list
// otherwise, go to the end of the list and add a node there
// return the created node
t_redir *ft_new_redir_node(t_redir *redir_list)
{
	if (!redir_list) // if we already have redirections
	{
		redir_list = malloc (sizeof(t_redir));
		if (!redir_list)
			return (NULL);
	}
	else
	{
		redir_list = ft_last_redir(redir_list); // goes to the last redir
		redir_list->next = malloc (sizeof(t_redir));
		if (!redir_list)
			return (NULL);
		redir_list = redir_list->next;
	}
	redir_list->next = NULL;
	return (redir_list);
}

// adds a redirection node to our redirection list in our command struct
// if the redirection token (>, <, >>, <<) is followed by another token, 
// advance one token in the token list, 
// and add that token's string to our redirection node
int	ft_add_redir(t_token **tok, t_redir *redir_list)
{
	redir_list = ft_new_redir_node(redir_list);
	if (!redir_list)
		return (-1);
	redir_list->type = (*tok)->type;
	if ((*tok)->next)
	{
		*tok = (*tok)->next;
		redir_list->str = ft_strdup((*tok)->str);
	}
	else
		redir_list->str = NULL;
	return (0);
}
