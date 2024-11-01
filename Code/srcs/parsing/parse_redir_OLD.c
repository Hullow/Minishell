/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_OLD.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:23:55 by fallan            #+#    #+#             */
/*   Updated: 2024/11/01 18:46:26 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// OLD
s_redir				*ft_parse_redirections(t_token **tok);
s_redir				*ft_create_redir_node(t_token *tok, t_redir *redir_list);
s_redir				*ft_create_redir_list(t_token *tok);

int	ft_initialize_redir_node(t_redir **redir_node, t_redir **redir_list)
{
	if (!((*redir_list)->type)) // if we are starting the list
	{
		printf("ft_initialize_redir_node 1\n");
		printf("(*redir_list)->type): %d\n", (*redir_list)->type);
		printf("%p", *redir_list);
		// *redir_node = *redir_list;
		printf("ft_initialize_redir_node 1.1\n");
	}
	else // if redir_list already contains some data, malloc a new node
	{
		printf("ft_initialize_redir_node 2\n");
		*redir_node = malloc (sizeof(t_redir)); // or pointer-sized ?
		if (redir_node == NULL)
			return (-1); // malloc fail
		ft_last_redir(*redir_list)->next = *redir_node; // add node to end of redirection list
	}
	return (0);
}

// takes as input the token before the redirection symbol
// creates a new redirection node with the redir type and file or delimiter (str)
// returns 0 if success, -1 if malloc fails
int	ft_create_redir_node(t_token **tok, t_redir **redir_list)
{
	s_redir			**redir_node = NULL;
	t_token 	*operator_token;
	t_token 	*following_token;

	printf("ft_create_redir_node 1\n");
	if (ft_initialize_redir_node(redir_node, redir_list) == -1)
		return (-1);
	printf("ft_create_redir_node 2\n");
	operator_token = (*tok)->next;
	following_token = (*tok)->next->next;
	(*redir_node)->type = operator_token->type;
	ft_free_token(operator_token); // free the operator token
	printf("In ft_create_redir_node (initial):\n*************\ncurrent token: {%s}. next token: {%s}\n", (*tok)->str, (*tok)->next->str);
	if (following_token) // if there is a token after the operator
	{
		(*redir_node)->str = following_token->str; // systematically ? => likely yes
		(*tok)->next = following_token->next; // remove two tokens from the list
		ft_free_token(following_token); // free the token after the operator
	}
	else  // if the operator is the last token
	{
		(*redir_node)->str = NULL; // there is no potential file or delimiter after the redirection
		(*tok)->next = NULL; // remove the operator token from the list
	}
	printf("In ft_create_redir_node (after):\n*************\ncurrent token: {%s}. next token: {%s}\n", (*tok)->str, (*tok)->next->str);
	return (0);
}

int	ft_initialize_redir_list(t_redir **redir_list)
{
	redir_list = malloc (sizeof(t_redir)); // or pointer-sized ?
	if (redir_list == NULL)
		return (-1);
	redir_list->type = 0;
	redir_list->str = NULL;
	redir_list->next = NULL;
	return (0);
}

// traverses token list
// when a redir token is found, create a redirection node
// returns the last redir node assigned
t_redir *ft_parse_redirections(t_token **tok)
{
	s_redir			**redir_list;
	t_token **previous_tok = NULL;

	redir_list = ft_initialize_redir_list(redir_list);
	if (!redir_list)
		return (NULL); // how to detect this ?
	printf("In ft_parse_redirections:\n***********\n");
	while ((*tok)->next)
	{
		printf("Before processing: (*tok)->next->type is %d (str: {%s})\n", (*tok)->next->type, (*tok)->next->str);
		if (ft_is_redir((*tok)->next->type) == true)
		{
			if (!ft_create_redir_node(tok, redir_list))
				return (NULL); // if malloc fails
		}
		printf("After processing: (*tok)->next->type is %d (str: {%s})\n", (*tok)->next->type, (*tok)->next->str);
		previous_tok = tok;
		(*tok) = (*tok)->next;
	}
	// simplify ?
	if (ft_is_redir((*tok)->type) == true) // if last token of the list is redir
		if (!ft_create_redir_node(previous_tok, *redir_list))
			return (NULL); // if malloc fails
	return (redir_list);
}

// need a function to check that list has at least one redir