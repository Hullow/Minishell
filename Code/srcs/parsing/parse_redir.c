/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:23:55 by fallan            #+#    #+#             */
/*   Updated: 2024/10/25 20:49:36 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// traverses the linked list of tokens and returns the last token
s_redir *ft_last_redir(s_redir *redir_list)
{
	if (!redir_list || !redir_list->next)
		return (redir_list);
	while (redir_list->next)
		redir_list = redir_list->next;
	return (redir_list);
}

bool	ft_is_redir(int token_type)
{
	if (token_type == REDIR_INPUT || \
		token_type == REDIR_OUTPUT || \
		token_type == REDIR_APPEND || \
		token_type == REDIR_HEREDOC)
	return (1);
		else
	return (0);
}

// creates a new redirection node with the redir type and file or delimiter (str)
// returns the following token
s_redir *ft_create_redir_node(struct s_token *tok, s_redir *redir_list)
{
	s_redir	*redir_node;
	
	if (!redir_list->type) // if we are starting the list
		redir_node = redir_list;
	else // if redir list already has some type assigned, malloc a new node
	{
		redir_node = malloc (sizeof(s_redir)); // or pointer-sized ?
		if (redir_node == NULL)
			return (redir_node);
		ft_last_redir(redir_list)->next = redir_node;// add node to end of redirection list
	}
	redir_node->type = tok->type;
	if (tok->next)
		redir_node->str = tok->next->str; // systematically ? => likely yes
	return (redir_list);
}

// traverses token list
// when a redir token is found, create a redirection node
s_redir *ft_create_redir_list(struct s_token *tok)
{
	s_redir	*redir_list;

	redir_list = malloc (sizeof(s_redir)); // or pointer-sized ?
	if (redir_list == NULL)
		return (redir_list);
	redir_list->type = NULL;
	redir_list->str = NULL;
	redir_list->next = NULL;
	while (tok)
	{
		if (tok->type == REDIR_INPUT || \
		tok->type == REDIR_OUTPUT || \
		tok->type == REDIR_APPEND || \
		tok->type == REDIR_HEREDOC)
		{
			redir_list = ft_create_redir_node(tok, redir_list);
			if (tok->next) // if there is a potential file or delimiter after our redirection
				tok = tok->next;
			tok = tok->next;
		}
		else
			tok = tok->next;
	}
	return (redir_list);
}
