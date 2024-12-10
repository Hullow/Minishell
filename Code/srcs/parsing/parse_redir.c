/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:28:03 by fallan            #+#    #+#             */
/*   Updated: 2024/12/10 14:22:32 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// traverses the linked list of tokens and returns the last token
t_redir	*ft_last_redir(t_redir *redir_list)
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
t_redir	*ft_new_redir_node(t_redir *redir_list)
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
t_token	**ft_assign_redir_str(t_token **tok, t_redir *redir_list)
{
	*tok = (*tok)->next;
	redir_list->str = ft_strdup((*tok)->str);
	redir_list->str_type = (*tok)->type;
	// printf("ft_assign_redir_str\n");
	return (tok);
}

// adds a redirection node to our redirection list in our command struct
// if the redirection token (>, <, >>, <<) is followed by another token, 
// advance one token in the token list, 
// and add that token's string to our redirection node
// N.b.: head is initialized to NULL by the calling function

 // if we have redirections, goes to last redirection
 // mallocs a new redirection
 // sets the type of the redirection
 // if there is a token after the 
int	ft_add_redir(t_token **tok, t_command *cmd_list, t_redir *head_redir)
{
	if (cmd_list->redir_list)
	{
		head_redir = cmd_list->redir_list; // to save one line, maybe make a function that modifies address of redir_list to last redir and returns head_redir
		cmd_list->redir_list = ft_last_redir(cmd_list->redir_list); // goes to the last redir
		cmd_list->redir_list->next = malloc (sizeof(t_redir));
		if (!(cmd_list->redir_list->next))
			return (-1);
		cmd_list->redir_list = cmd_list->redir_list->next;
	}
	else
	{
		cmd_list->redir_list = malloc (sizeof(t_redir));
		head_redir = cmd_list->redir_list; // to save one line, maybe add head_redir to each t_redir ? Then you can malloc in a function call that also sets head_redir to whatever
	}
	if (!cmd_list->redir_list)
		return (-1);
	cmd_list->redir_list->type = (*tok)->type;
	cmd_list->redir_list->next = NULL;
	// > |
	if ((*tok)->next) // if there is a token after, assign it to redir_list->str
		tok = ft_assign_redir_str(tok, cmd_list->redir_list);
	else
		cmd_list->redir_list->str = NULL; // Need error handling
	cmd_list->redir_list = head_redir;
	return (0);
}
