/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanzi <ahanzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:28:03 by fallan            #+#    #+#             */
/*   Updated: 2024/12/23 17:14:41 by ahanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// traverses the redirection linked list and returns the last node
t_redir	*ft_last_redir(t_redir *redir_list)
{
	if (!redir_list || !(redir_list)->next)
		return (redir_list);
	while (redir_list->next)
		(redir_list) = (redir_list)->next;
	return (redir_list);
}

// Function to examine the token following the redirection
// - copies the string from our token to the redirection node,
// - assigns a type for the copied string based on its underlying token type,
// used later for error checking: e.g. two consecutive redirection tokens "> <"
// - checks the quoted status of the token to prepare heredoc processing:
//	if any part of the string of the token following the redirection operator
//  is quoted, the function sets the marker for heredocs to "not expand"
// - returns the token
//
// n.b.: redir_list->str_type is the type of the token that **follows**
// the actual redirection, not the type of redirection
t_token	**ft_assign_redir_str(t_token **tok, t_redir *redir_list)
{
	*tok = (*tok)->next;
	redir_list->str = ft_strdup((*tok)->str);
	if (!redir_list->str)
		return (NULL);
	redir_list->str_type = (*tok)->type;
	if ((*tok)->is_between_quotes)
		redir_list->expand_heredoc = false;
	else
		redir_list->expand_heredoc = true;
	return (tok);
}

// create a new redirection in the redirection list
// if no redirection list, starts one
// else, goes to the last redirection and adds a new node
// returns the first redirection (head)
t_redir	*ft_create_redir(t_command *cmd_list)
{
	t_redir	*redir;

	redir = cmd_list->redir_list;
	if (redir)
	{
		redir = ft_last_redir(redir);
		redir->next = malloc (sizeof(t_redir));
		redir = redir->next;
	}
	else
		redir = malloc (sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->str = NULL;
	redir->to_expand = NULL;
	redir->heredoc = NULL;
	redir->next = NULL;
	return (redir);
}

// if we have redirections, goes to last redirection
// mallocs a new redirection
// sets the type of the redirection
// if there is a token after the redirection,
// call ft_assign_redir_str to assign a string and string type to redirection,
// and advance one token (ft_assign_redir does this)
// N.b.: head_redir is initialized to NULL by the calling function
int	ft_add_redir(t_token **tok, t_command *cmd_list)
{
	t_redir	*new_redir;
	t_redir	*head_redir;

	head_redir = cmd_list->redir_list;
	new_redir = ft_create_redir(cmd_list);
	new_redir->type = (*tok)->type;
	if ((*tok)->next)
		tok = ft_assign_redir_str(tok, new_redir);
	if (!tok)
		return (-1);
	if ((*tok)->to_expand)
		new_redir->to_expand = (*tok)->to_expand;
	if (!head_redir)
		cmd_list->redir_list = new_redir;
	return (0);
}
