/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:28:03 by fallan            #+#    #+#             */
/*   Updated: 2024/11/21 19:12:26 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// traverses the linked list of tokens and returns the last token
t_redir *ft_last_redir(t_redir *redir_list)
{
	if (!redir_list || !redir_list->next)
		return (redir_list);
	while (redir_list->next)
		redir_list = redir_list->next;
	return (redir_list);
}

// creates a new redirection node
// if no redirection list existing, initialize the list
// otherwise, go to the end of the list and add a node there
// return the created node
t_redir *ft_new_redir_node(t_redir *redir_list)
{
	if (!redir_list) // if we have no redirections
	{
		redir_list = malloc (sizeof(t_redir));
		if (!redir_list)
			return (NULL);
	}
	else
	{
		redir_list = ft_last_redir(redir_list); // goes to the last redir
		printf("last redir is of type {%s} to/from/delimiter {%s}\n", ft_return_redir_type(redir_list->type), redir_list->str);
		redir_list->next = malloc (sizeof(t_redir));
		if (!(redir_list->next))
			return (NULL);
		redir_list = redir_list->next;
	}
	redir_list->next = NULL;
	return (redir_list);
}

// copies the string from our token to the redirection node
// advances by one token in the token linked list
// returns the token
t_token	*ft_assign_redir_str(t_token **tok, t_redir *redir_list)
{
	*tok = (*tok)->next;
	redir_list->str = ft_strdup((*tok)->str);
	return (*tok);
}

// adds a redirection node to our redirection list in our command struct
// if the redirection token (>, <, >>, <<) is followed by another token, 
// advance one token in the token list, 
// and add that token's string to our redirection node
int	ft_add_redir(t_token **tok, t_command *cmd_sequence)
{
	t_redir	*head;

	if (cmd_sequence->redir_list) // if we have redirections
	{
		head = cmd_sequence->redir_list; // to save one line, maybe make a function that modifies address of redir_list to last redir and returns head
		cmd_sequence->redir_list = ft_last_redir(cmd_sequence->redir_list); // goes to the last redir
		cmd_sequence->redir_list->next = malloc (sizeof(t_redir));
		if (!(cmd_sequence->redir_list->next))
			return (-1);
		cmd_sequence->redir_list = cmd_sequence->redir_list->next;
	}
	else
	{
		// printf("initial redir\n");
		cmd_sequence->redir_list = malloc (sizeof(t_redir));
		head = cmd_sequence->redir_list; // to save one line, maybe add head to each t_redir ? Then you can malloc in a function call that also sets head to whatever
	}
	if (!cmd_sequence->redir_list)
		return (-1);
	cmd_sequence->redir_list->type = (*tok)->type; // to save one line, maybe make function ft_set_type_and_next_to_NULL
	// printf("redir type: %s\n", ft_return_redir_type(cmd_sequence->redir_list->type));
	cmd_sequence->redir_list->next = NULL;
	if ((*tok)->next && !ft_token_is_redir((*tok)->next->type)) // if there is a token after, assign it to redir_list->str
	{
		*tok = ft_assign_redir_str(tok, cmd_sequence->redir_list);
		// printf("assigned string: {%s}\n", cmd_sequence->redir_list->str);
	}
	else
	{
		// printf("no string assigned\n");
		cmd_sequence->redir_list->str = NULL;
	}
	cmd_sequence->redir_list = head;
	return (0);
}
